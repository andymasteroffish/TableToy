//
//  CupTrackerBlob.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 9/16/15.
//
//

#include "CupTrackerBlob.h"


//--------------------------------------------------------------
void CupTrackerBlob::setupCustom(){
    
    imgWidth = 1280;
    imgHeight = 480;
    
    
#ifdef USE_VIDEO
    ofVideoPlayer * thisGrabber = new ofVideoPlayer();
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->loadMovie("vid/spinners_no_border.mov");
    vidGrabber[0]->play();
    
    imgWidth = vidGrabber[0]->width;
    imgHeight = vidGrabber[0]->height;
#elif defined(USE_WEBCAM)
    ofVideoGrabber * thisGrabber = new ofVideoGrabber();
    
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->initGrabber(640,480);
#else
    for (int i = 0; i < deviceList.size(); i++) {
        ofxMacamPs3Eye * camera = new ofxMacamPs3Eye();
        camera->setDeviceID(deviceList[i]->id);
        camera->initGrabber(640, 480);
        vidGrabber.push_back(camera);
    }
#endif
    
    
    fbo.allocate(imgWidth, imgHeight, GL_RGB);
    pix.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    fullImg.allocate(imgWidth, imgHeight);
    colorImg.allocate(imgWidth , imgHeight);
    grayImage.allocate(imgWidth , imgHeight);
    
    //start the warp points to include the whole camera(s) image(s)
    warpPoints[0].set(0, 0);
    warpPoints[1].set(imgWidth, 0);
    warpPoints[2].set(imgWidth, imgHeight);
    warpPoints[3].set(0, imgHeight);
    
    //warp end points don't change
    warpEndPoints[0].set(0,0);
    warpEndPoints[1].set(colorImg.width,0);
    warpEndPoints[2].set(colorImg.width, colorImg.height);
    warpEndPoints[3].set(0,colorImg.height);
    
    
    threshold = 80;
    
    framesBeforeKillingCup = 10;
    
    
    timeForDoubleKeyPress = 0.2;
    lastKeyPressTime = -1000;
    
    cupOffset.set(0,0);
    
    isDebug = false;
    
    nextID = 0;
}

//--------------------------------------------------------------
void CupTrackerBlob::updateFromPanel(ofxControlPanel * panel){
    threshold = panel->getValueI("CAM_THRESHOLD");
    cupOffset.x = panel->getValueF("CAM_X_OFFSET");
    cupOffset.y = panel->getValueF("CAM_Y_OFFSET");
    for (int i=0; i<4; i++){
        warpPoints[i].x = panel->getValueF("CAM_WARP_X_"+ofToString(i)) * fullImg.width;
        warpPoints[i].y = panel->getValueF("CAM_WARP_Y_"+ofToString(i)) * fullImg.height;
    }
    maxCompactness = panel->getValueF("CAM_MAX_COMPACT");
}

//--------------------------------------------------------------
void CupTrackerBlob::update(){
    ofBackground(100,100,100);
    for (int i = 0; i < vidGrabber.size(); i++) {
        vidGrabber[i]->update();
    }
    
    
    
    if (vidGrabber[0]->isFrameNew()){
        
        fbo.begin();
        vidGrabber[0]->draw(0, 0);
        if (vidGrabber.size() > 1){
            vidGrabber[1]->draw(640, 0);
        }
        fbo.end();
        
        fbo.readToPixels(pix);
        fullImg.setFromPixels(pix);
        
        colorImg.warpIntoMe(fullImg, warpPoints, warpEndPoints);
        grayImage = colorImg;
        
        grayImage.threshold(threshold);
        
        grayImage.invert();
        
        grayImage.dilate_3x3(); //I did this in doodle defense. I guess it helps?
        
        checkBlobs();
        
        //go through and check for cups that have been removed
        for (int i=activeCups.size()-1; i>=0 ; i--){
            activeCups[i].framesWithoutUpdate++;
            if (activeCups[i].framesWithoutUpdate > framesBeforeKillingCup){
                activeCups.erase( activeCups.begin()+i );
            }
        }
        
    }
}

//--------------------------------------------------------------
void CupTrackerBlob::draw(){
    
    ofSetColor(255, 200);
    
    fbo.draw(0,0);
    //fullImg.draw(20,20);
    
    ofVec2f drawStart(100,0);
    
    colorImg.draw(drawStart.x,drawStart.y);
    grayImage.draw(drawStart.x,drawStart.y+5+fullImg.getHeight());
    
    drawFiducials(drawStart.x, drawStart.y);
    
}

//--------------------------------------------------------------
void CupTrackerBlob::drawFiducials(int x, int y){
    contourFinder.draw(x, y);
    
    ofSetColor(255,0,0,200);
    for (int i=0; i<activeCups.size(); i++){
        ofCircle(activeCups[i].camPos.x+x, activeCups[i].camPos.y+y, 10);
    }
    
    cout<<"cups: "<<activeCups.size()<<endl;
}

//--------------------------------------------------------------
void CupTrackerBlob::keyPressed(int key){
    if( key == '-' ) {
        threshold = MAX( 0, threshold-1 );
    } else if( key == '+' || key == '=' ) {
        threshold = MIN( 255, threshold+1 );
    }
    
    
#ifdef USE_VIDEO
    if (key == 'v'){
        bool isDouble = ofGetElapsedTimef() - lastKeyPressTime < timeForDoubleKeyPress;
        lastKeyPressTime = ofGetElapsedTimef();
        if (isDouble){
            vidGrabber[0]->setFrame(0);
            vidGrabber[0]->play();
        }else{
            if (vidGrabber[0]->isPlaying()){
                vidGrabber[0]->stop();
            }else{
                vidGrabber[0]->play();
            }
        }
    }
#endif
}



//--------------------------------------------------------------
void CupTrackerBlob::checkBlobs(){
    //adjust the image to fit the screen
    float xAdjust = (float)gameWidth / (float)imgWidth;
    float yAdjust = (float)gameHeight / (float)imgHeight;
    
    int minArea=20;
    int maxArea=(imgWidth*imgHeight)/2;
    int maxNumberOfBlobs=25;
    contourFinder.findContours(grayImage, minArea, maxArea, maxNumberOfBlobs, false);
    
    cout<<"mother fucker i have "<<contourFinder.nBlobs<<endl;
    
    //float maxCompactness = 1.2;//1.5; //make this lower to have it require more circular blobs
    
//    //if there is a blob inside of another blob, then it was not a full circle and should not be considerred
//    vector <int> skip;
//    float minDist=5;
//    
//    //JUST USE the holes boolean in the blog. JESUS
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        for (int k=0; k<i; k++){
//            if (ofDist(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y,
//                       contourFinder.blobs[k].centroid.x,contourFinder.blobs[k].centroid.y)<minDist){
//                skip.push_back(i);
//                skip.push_back(k);
//            }
//        }
//    }
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        
        //check if this was one of the blobs with holes. Skip it if it was
        bool skipMe=false;
//        for (int k=0; k<skip.size(); k++){
//            if (i==skip[k]) skipMe=true;
//        }
        
        //find the radius
        float size=sqrt( contourFinder.blobs[i].area/PI )/2;    //diviing by 2 because the image is twice the size of the field
        
        //make sure the blob is at least pretty close to being a circle
        //check compacntess of the blob. a value of 1 would be a perfect circle. Higher values are less compact
        float compactness = (float)((contourFinder.blobs[i].length*contourFinder.blobs[i].length/contourFinder.blobs[i].area)/FOUR_PI);
        if (compactness>maxCompactness) skipMe=true;
        
        //if it passed all those tests, try to make a tower for the blob
        if (!skipMe){
            //check if there is already a tower in this spot
            bool towerHere=false;
            
            for (int k=0; k<activeCups.size(); k++){
                if ( ofDist(activeCups[k].pos.x,activeCups[k].pos.y, contourFinder.blobs[i].centroid.x*xAdjust,contourFinder.blobs[i].centroid.y*yAdjust) < size*xAdjust){
                    //there is a tower here
                    towerHere=true;
                    //towers[k]->found=true;
                    
                    //was the tower built up? adjust its size and center position
                    //the image is twice the size of the field, so we need to cut the values in half before scalling them up to game size
                    activeCups[k].pos.set(contourFinder.blobs[i].centroid.x*xAdjust, contourFinder.blobs[i].centroid.y*yAdjust);
                    activeCups[k].camPos.set(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
                    activeCups[k].framesWithoutUpdate = 0;
                }
            }
            
            //if there is no cup currently in this spot, create one
            if (!towerHere){
                CupInfo thisCupInfo;
                
                thisCupInfo.uniqueID = nextID++;
                thisCupInfo.pos.set( contourFinder.blobs[i].centroid.x*xAdjust + cupOffset.x , contourFinder.blobs[i].centroid.y*yAdjust + cupOffset.y );
                thisCupInfo.camPos.set(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
                thisCupInfo.angle = 0;
                thisCupInfo.framesWithoutUpdate = 0;
                thisCupInfo.startTime = ofGetElapsedTimef();
                
                
                activeCups.push_back(thisCupInfo);
            }
        }
    }
}