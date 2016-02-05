//
//  CupTrackerCam.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 8/18/15.
//
//

#include "CupTrackerCam.h"

//--------------------------------------------------------------
void CupTrackerCam::setupCustom(){
    
    imgWidth = 1280 ;
    imgHeight = 480 ;
    
    

#ifdef USE_VIDEO
    ofVideoPlayer * thisGrabber = new ofVideoPlayer();
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->loadMovie("vid/ar_split.mp4");
    //vidGrabber[0]->loadMovie("vid/ps3.mov");
    //vidGrabber[0]->loadMovie("vid/spinners_no_border.mov");
    //vidGrabber[0]->loadMovie("vid/mostly_still.mov");
    vidGrabber[0]->play();
    
#elif defined(USE_WEBCAM)
    ofVideoGrabber * thisGrabber = new ofVideoGrabber();
    //thisGrabber->setDeviceID(1);
    
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->initGrabber(imgWidth/2,imgHeight);
#else
    for (int i = 0; i < deviceList.size(); i++) {
        ofxMacamPs3Eye * camera = new ofxMacamPs3Eye();
        camera->setDeviceID(deviceList[i]->id);
        camera->initGrabber(imgWidth/2, imgHeight);
        vidGrabber.push_back(camera);
    }
#endif
    
    
    fbo.allocate(imgWidth, imgHeight, GL_RGB);
    pix.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    
    fullImg.allocate(imgWidth, imgHeight);
    colorImg.allocate(imgWidth, imgHeight);
    grayImage.allocate(imgWidth, imgHeight);
    
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
    
    
    threshold = 69;//80;
    
    framesBeforeKillingCup = 40;
    
    //detect finger is off by default
//    fidfinder.detectFinger		= true;
//    fidfinder.maxFingerSize		= 25;
//    fidfinder.minFingerSize		= 5;
//    fidfinder.fingerSensitivity	= 0.05f; //from 0 to 2.0f
    
    ARKit.setup(imgWidth, imgHeight);
    ARKit.setThreshold(threshold);
    
    
    timeForDoubleKeyPress = 0.2;
    lastKeyPressTime = -1000;
    
    cupOffset.set(0,0);
    
    isDebug = false;
}

//--------------------------------------------------------------
void CupTrackerCam::updateFromPanel(ofxControlPanel * panel){
    threshold = panel->getValueI("CAM_THRESHOLD");
    //ARKit.setThreshold(threshold);    //WHY WOULD WE SET THIS THRESHOLD AGAIN WHEN WE ARE ALREADY THRESHOLDING OUR IMAGE??? MAKES NO SENSE, EVEN THOUGH THE EXAMPLE PROJECT DOES JUST THIS. I'M COMMENTING THIS OUT AND JUST LETTING IT KEEP THE STARTING THRESHOLD VALUE.
    ARKit.activateAutoThreshold(panel->getValueB("CMA_AUTO_THRESHOLD"));
    cupOffset.x = panel->getValueF("CAM_X_OFFSET");
    cupOffset.y = panel->getValueF("CAM_Y_OFFSET");
    for (int i=0; i<4; i++){
        warpPoints[i].x = panel->getValueF("CAM_WARP_X_"+ofToString(i)) * fullImg.width;
        warpPoints[i].y = panel->getValueF("CAM_WARP_Y_"+ofToString(i)) * fullImg.height;
    }
}

//--------------------------------------------------------------
void CupTrackerCam::update(){
    
    ofSetColor(255);
    
    for (int i = 0; i < vidGrabber.size(); i++) {
        vidGrabber[i]->update();
    }
    
    if (vidGrabber[0]->isFrameNew()){
        
        fbo.begin();
        vidGrabber[0]->draw(0, 0); //this should only be half of the imgWidth
        if (vidGrabber.size() > 1){
            vidGrabber[1]->draw(imgWidth/2, 0);
        }
        fbo.end();
        
        fbo.readToPixels(pix);
        
        //trying to fux with the pixels before we build the color image out of them
//        unsigned char * pixels = pix.getPixels();
//        //cout<<"pixels "<<pix.size()<<endl;
//        for (int i=0; i<pix.size(); i+=3){
//            int r = (int)pixels[i];
//            int g = (int)pixels[i+1];
//            int b = (int)pixels[i+2];
//            
//            pixels[i] = (char)b;
//            pixels[i+1] = (char)b;
//            //pixels[i+2] = b;
//            
//        }
//        fullImg.setFromPixels(pixels, imgWidth, imgHeight);
        
        fullImg.setFromPixels(pix);
        
        //for (int i=0; i<1; i++)    fullImg.dilate();
        
        colorImg.warpIntoMe(fullImg, warpPoints, warpEndPoints);
        grayImage = colorImg;
        
        grayImage.threshold(threshold);
        //grayImage.dilate(); //maybe this helps???
        
        ARKit.update(grayImage.getPixels());
        
        //fidfinder.findFiducials(grayImage);
        
        
        //update our info
        for (int i=0; i<ARKit.getNumDetectedMarkers(); i++){
            checkARTag(i);
        }
//        for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++){
//            checkFiducial(fiducial);
//        }
        
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
void CupTrackerCam::draw(){
    
    ofSetColor(255, 200);
    
    fbo.draw(0,0);
    //fullImg.draw(20,20);
    
    ofVec2f drawStart(100,0);
    
    colorImg.draw(drawStart.x,drawStart.y);
    grayImage.draw(drawStart.x,drawStart.y+5+fullImg.getHeight());
    
    //drawFiducials(drawStart.x, drawStart.y);
    drawARTags(drawStart.x, drawStart.y);
}

////--------------------------------------------------------------
//void CupTrackerCam::drawFiducials(int x, int y){
//    //use this method for the FiducialTracker
//    //to get fiducial info you can use the fiducial getter methods
//    for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
//        fiducial->draw( x, y );//draw fiducial
//        fiducial->drawCorners( x, y );//draw corners
//    }
//}

//--------------------------------------------------------------
void CupTrackerCam::drawARTags(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (int i=0; i<ARKit.getNumDetectedMarkers(); i++){
        
        ofPoint thisPos = ARKit.getDetectedMarkerCenter(i);
        
        vector<ofPoint> corners;
        ARKit.getDetectedMarkerCorners(i, corners);
        
        int dir = ARKit.getDetectedMarkerDirection(i);
        
        int cornerToUse = 2-dir;
        if (cornerToUse < 0)    cornerToUse+=4;
        ofLine(thisPos.x, thisPos.y, corners[cornerToUse].x, corners[cornerToUse].y);
        
        float angle = atan2(thisPos.y-corners[cornerToUse].y, thisPos.x-corners[cornerToUse].x);
        
        ofPushMatrix();
        
        ofTranslate(thisPos.x, thisPos.y);
        ofRotate(angle*RAD_TO_DEG);
        
        ofNoFill();
        ofSetColor( ofColor::orange );
        float circleSize = 30;
        float lineDist = circleSize + 5;
        ofCircle(0, 0, 30);
        ofLine(-lineDist, 0, lineDist, 0);
        ofLine(0, -lineDist, 0, lineDist);
        
        ofPopMatrix();
        
        ofFill();
        ofSetColor(0,100);
        ofRect(thisPos.x-20, thisPos.y-60, 60, 25);
        ofSetColor( ofColor::yellow );
        ofDrawBitmapString(ofToString(ARKit.getMarkerID(i)), thisPos.x-15, thisPos.y-38);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void CupTrackerCam::keyPressed(int key){
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
//void CupTrackerCam::checkFiducial(list<ofxFiducial>::iterator fiducial){
//    
//    //adjust the image to fit the screen
//    float xAdjust = (float)gameWidth / (float)grayImage.width;
//    float yAdjust = (float)gameHeight / (float)grayImage.height;
//    
//    //does a cup with this ID exist in the list?
//    for (int i=0; i<activeCups.size(); i++){
//        if (activeCups[i].uniqueID == fiducial->fidId){
//            //if we found it update it
//            activeCups[i].pos.set( fiducial->current.xpos*xAdjust + cupOffset.x , fiducial->current.ypos*yAdjust + cupOffset.y);
//            activeCups[i].angle = fiducial->current.angle;
//            //and don't let it die
//            activeCups[i].framesWithoutUpdate = 0;
//            return;
//        }
//    }
//    
//    //if there was nothing, we need to make a new cup
//    CupInfo thisCupInfo;
//    
//    thisCupInfo.uniqueID = fiducial->fidId;
//    thisCupInfo.pos.set( fiducial->current.xpos*xAdjust + cupOffset.x , fiducial->current.ypos*yAdjust + cupOffset.y );
//    thisCupInfo.angle = fiducial->current.angle;
//    thisCupInfo.framesWithoutUpdate = 0;
//    thisCupInfo.startTime = ofGetElapsedTimef();
//    
//    
//    activeCups.push_back(thisCupInfo);
//    
//}


//--------------------------------------------------------------
void CupTrackerCam::checkARTag(int idNum){
    
    //get some info about this bad boy
    int tagID = ARKit.getMarkerID(idNum);
    ofPoint tagPos = ARKit.getDetectedMarkerCenter(idNum);
    
    //adjust the image to fit the screen
    float xAdjust = (float)gameWidth / (float)grayImage.width;
    float yAdjust = (float)gameHeight / (float)grayImage.height;
    
    float gameWorldX = tagPos.x * xAdjust + cupOffset.x;
    float gameWorldY = tagPos.y * yAdjust + cupOffset.y;
    
    //cout<<"putitng "<<idNum<<" at "<<gameWorldX<<" , "<<gameWorldY<<endl;
    
    //getting the angle is a bit of a chore
    vector<ofPoint> corners;
    ARKit.getDetectedMarkerCorners(idNum, corners);
    int dir = ARKit.getDetectedMarkerDirection(idNum);
    
    int cornerToUse = 2-dir;
    if (cornerToUse < 0)    cornerToUse+=4;
    float tagAngle = atan2(tagPos.y-corners[cornerToUse].y, tagPos.x-corners[cornerToUse].x);

    //does a cup with this ID exist in the list? If so, update the info
    for (int i=0; i<activeCups.size(); i++){
        if (activeCups[i].uniqueID == tagID){
            //if we found it update it
            activeCups[i].pos.set( gameWorldX, gameWorldY );
            activeCups[i].angle = tagAngle;
            //and don't let it die
            activeCups[i].framesWithoutUpdate = 0;
            return;
        }
    }
    
    //if there was nothing, we need to make a new cup
    CupInfo thisCupInfo;
    
    thisCupInfo.uniqueID = tagID;
    thisCupInfo.pos.set( gameWorldX, gameWorldY );
    thisCupInfo.angle = tagAngle;
    thisCupInfo.framesWithoutUpdate = 0;
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    activeCups.push_back(thisCupInfo);
    
}



