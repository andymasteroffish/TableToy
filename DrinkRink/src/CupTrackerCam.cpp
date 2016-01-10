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
    
    imgWidth = 1280;
    imgHeight = 480;
    
    

#ifdef USE_VIDEO
    ofVideoPlayer * thisGrabber = new ofVideoPlayer();
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->loadMovie("vid/spinners_no_border.mov");
    //vidGrabber[0]->loadMovie("vid/mostly_still.mov");
    vidGrabber[0]->play();
    
    imgWidth = vidGrabber[0]->width;
    imgHeight = vidGrabber[0]->height;
#elif defined(USE_WEBCAM)
    ofVideoGrabber * thisGrabber = new ofVideoGrabber();
    //thisGrabber->setDeviceID(1);
    
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
    
    
//    cout<<"camera devices:"<<endl;
//    vector<ofVideoDevice> pluggedIn = vidGrabber.listDevices();
//    for (int i=0; i<pluggedIn.size(); i++){
//        cout<<i<<":"<<pluggedIn[i].deviceName<<endl;
//    }
    
    
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
    
    //detect finger is off by default
    fidfinder.detectFinger		= true;
    fidfinder.maxFingerSize		= 25;
    fidfinder.minFingerSize		= 5;
    fidfinder.fingerSensitivity	= 0.05f; //from 0 to 2.0f
    
    
    timeForDoubleKeyPress = 0.2;
    lastKeyPressTime = -1000;
    
    cupOffset.set(0,0);
    
    isDebug = false;
}

//--------------------------------------------------------------
void CupTrackerCam::updateFromPanel(ofxControlPanel * panel){
    threshold = panel->getValueI("CAM_THRESHOLD");
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
        fidfinder.findFiducials(grayImage);
        
        
        //update our info
        for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
            
            checkFiducial(fiducial);
        }
        
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
    
    drawFiducials(drawStart.x, drawStart.y);
    
}

//--------------------------------------------------------------
void CupTrackerCam::drawFiducials(int x, int y){
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
        fiducial->draw( x, y );//draw fiducial
        fiducial->drawCorners( x, y );//draw corners
    }
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
void CupTrackerCam::checkFiducial(list<ofxFiducial>::iterator fiducial){
    
    //adjust the image to fit the screen
    float xAdjust = (float)gameWidth / (float)imgWidth;
    float yAdjust = (float)gameHeight / (float)imgHeight;
    
    //does a cup with this ID exist in the list?
    for (int i=0; i<activeCups.size(); i++){
        if (activeCups[i].uniqueID == fiducial->fidId){
            //if we found it update it
            activeCups[i].pos.set( fiducial->current.xpos*xAdjust + cupOffset.x , fiducial->current.ypos*yAdjust + cupOffset.y);
            activeCups[i].angle = fiducial->current.angle;
            //and don't let it die
            activeCups[i].framesWithoutUpdate = 0;
            return;
        }
    }
    
    //if there was nothing, we need to make a new cup
    CupInfo thisCupInfo;
    
    thisCupInfo.uniqueID = fiducial->fidId;
    thisCupInfo.pos.set( fiducial->current.xpos*xAdjust + cupOffset.x , fiducial->current.ypos*yAdjust + cupOffset.y );
    thisCupInfo.angle = fiducial->current.angle;
    thisCupInfo.framesWithoutUpdate = 0;
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    
    activeCups.push_back(thisCupInfo);
    
}




