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
    
    imgWidth = 600;
    imgHeight = 200;
    
#ifdef USE_VIDEO
    //vidGrabber.loadMovie("vid/spinners_with_border.mov");
    vidGrabber.loadMovie("vid/spinners_no_border.mov");
    vidGrabber.play();
#else
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
#endif
    
    vidGrabber.videoSettings();
    
    fullImg.allocate(vidGrabber.width, vidGrabber.height);
    colorImg.allocate(imgWidth , imgHeight);
    grayImage.allocate(imgWidth , imgHeight);
    
    //start the warp points to include the whole camera image
    warpPoints[0].set(0, 0);
    warpPoints[1].set(vidGrabber.width, 0);
    warpPoints[2].set(vidGrabber.width, vidGrabber.height);
    warpPoints[3].set(0, vidGrabber.height);
    
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
    ofBackground(100,100,100);
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        fullImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.width, vidGrabber.height);
        colorImg.warpIntoMe(fullImg, warpPoints, warpEndPoints);
        //colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.width ,vidGrabber.height);
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
    
    vidGrabber.draw(20,20);
    
    ofVec2f drawStart(100,0);
    
    colorImg.draw(drawStart.x,drawStart.y);
    grayImage.draw(drawStart.x,drawStart.y+5+vidGrabber.height);
    
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
            vidGrabber.setFrame(0);
            vidGrabber.play();
        }else{
            if (vidGrabber.isPlaying()){
                vidGrabber.stop();
            }else{
                vidGrabber.play();
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




