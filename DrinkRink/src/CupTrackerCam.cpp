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
    
#ifdef USE_VIDEO
    vidGrabber.loadMovie("vid/spinners_no_border.mov");
    vidGrabber.play();
#else
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
#endif
    
    colorImg.allocate(vidGrabber.width ,vidGrabber.height);
    grayImage.allocate(vidGrabber.width ,vidGrabber.height);
    
    threshold = 80;
    
    framesBeforeKillingCup = 10;
    
    //detect finger is off by default
    fidfinder.detectFinger		= true;
    fidfinder.maxFingerSize		= 25;
    fidfinder.minFingerSize		= 5;
    fidfinder.fingerSensitivity	= 0.05f; //from 0 to 2.0f
    
    
    timeForDoubleKeyPress = 0.2;
    lastKeyPressTime = -1000;
}

//--------------------------------------------------------------
void CupTrackerCam::update(){
    ofBackground(100,100,100);
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.width ,vidGrabber.height);
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
    
    //vidGrabber.draw(20,20);
    
    ofVec2f drawStart(100,0);
    
    colorImg.draw(drawStart.x,drawStart.y);
    grayImage.draw(drawStart.x,drawStart.y+5+vidGrabber.height);
    
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
        fiducial->draw( drawStart.x, drawStart.y );//draw fiducial
        fiducial->drawCorners( drawStart.x, drawStart.y );//draw corners
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
                cout<<"love to press"<<endl;
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
    //this will need to be done way better
    float xAdjust = ofGetWidth()/vidGrabber.width;
    float yAdjust = ofGetHeight()/vidGrabber.height;
    
    //does a cup with this ID exist in the list?
    for (int i=0; i<activeCups.size(); i++){
        if (activeCups[i].uniqueID == fiducial->fidId){
            //if we found it update it
            activeCups[i].pos.set( fiducial->current.xpos*xAdjust, fiducial->current.ypos*yAdjust );
            activeCups[i].angle = fiducial->current.angle;
            //and don't let it die
            activeCups[i].framesWithoutUpdate = 0;
            return;
        }
    }
    
    //if there was nothing, we need to make a new cup
    CupInfo thisCupInfo;
    
    thisCupInfo.uniqueID = fiducial->fidId;
    thisCupInfo.pos.set( fiducial->current.xpos*xAdjust, fiducial->current.ypos*yAdjust );
    thisCupInfo.angle = fiducial->current.angle;
    thisCupInfo.framesWithoutUpdate = 0;
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    
    activeCups.push_back(thisCupInfo);
    
}




