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

class CupTrackerCam : public CupTracker{
public:
    
    void setupCustom();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void checkFiducial(list<ofxFiducial>::iterator fiducial);
    
    ofVideoGrabber 		vidGrabber;
    ofxCvGrayscaleImage grayImage;
    ofxCvColorImage		colorImg;
    
    ofxFiducialTracker	fidfinder;
    
    int 				threshold;
    
    int framesBeforeKillingCup;
    
};

#endif /* defined(__DrinkRink__CupTrackerCam__) */
