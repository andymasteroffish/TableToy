//
//  CupTrackerCam.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/18/15.
//
//

#ifndef __DrinkRink__CupTrackerCam__
#define __DrinkRink__CupTrackerCam__

#include "ofMain.h"
#include "CupTracker.h"

#include "ofxOpenCv.h"
#include "ofxFidMain.h"


//uncomment this to use live feed
#define USE_VIDEO
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class CupTrackerCam : public CupTracker{
public:
    
    void setupCustom();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void checkFiducial(list<ofxFiducial>::iterator fiducial);
    

#ifdef USE_VIDEO
    ofVideoPlayer       vidGrabber;
#else
    ofVideoGrabber 		vidGrabber;
#endif
    
    ofxCvGrayscaleImage grayImage;
    ofxCvColorImage		colorImg;
    
    ofxFiducialTracker	fidfinder;
    
    int 				threshold;
    
    int framesBeforeKillingCup;
    
    
    //debug stuff
    float timeForDoubleKeyPress;
    float lastKeyPressTime; //for double presses
    
    
};

#endif /* defined(__DrinkRink__CupTrackerCam__) */
