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
    void updateFromPanel(ofxControlPanel * panel);
    void update();
    void draw();
    void drawFiducials(int x, int y);
    
    void keyPressed(int key);
    
    void checkFiducial(list<ofxFiducial>::iterator fiducial);
    

#ifdef USE_VIDEO
    ofVideoPlayer       vidGrabber;
#else
    ofVideoGrabber 		vidGrabber;
#endif
    
    ofxCvColorImage		fullImg, colorImg;
    ofxCvGrayscaleImage grayImage;
    
    ofxFiducialTracker	fidfinder;
    
    
    int  threshold;
    ofPoint warpPoints[4];          //the points from the source image to use. These can be adjusted.
    ofPoint warpEndPoints[4];       //the points into the end image. These will always be the corners of our end image.
    
    int framesBeforeKillingCup;
    
    
    //debug stuff
    float timeForDoubleKeyPress;
    float lastKeyPressTime; //for double presses
    
    
};

#endif /* defined(__DrinkRink__CupTrackerCam__) */
