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
#include "CupInfo.h"

#include "ofxOpenCv.h"
#include "ofxFidMain.h"

class CupTrackerCam{
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    ofVideoGrabber 		vidGrabber;
    ofxCvGrayscaleImage grayImage;
    //ofxCvGrayscaleImage grayBg;
    //ofxCvGrayscaleImage	grayDiff;
    ofxCvColorImage		colorImg;
    
    ofxFiducialTracker	fidfinder;
    
    int 				threshold;
    //bool				bLearnBakground;
    //bool				backgroundSubOn;
    
};

#endif /* defined(__DrinkRink__CupTrackerCam__) */
