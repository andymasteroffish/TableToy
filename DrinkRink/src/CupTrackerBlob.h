//
//  CupTrackerBlob.h
//  DrinkRink
//
//  Created by Andy Wallace on 9/16/15.
//
//

#ifndef __DrinkRink__CupTrackerBlob__
#define __DrinkRink__CupTrackerBlob__


#include "ofMain.h"
#include "CupTracker.h"

#include "ofxOpenCv.h"
#include "ofxMacamPs3Eye.h"


//comment this out to use live feed
//#define USE_VIDEO
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//comment this out to use PS3 eyes
//#define USE_WEBCAM
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class CupTrackerBlob : public CupTracker{
public:
    
    void setupCustom();
    void updateFromPanel(ofxControlPanel * panel);
    void update();
    void draw();
    void drawFiducials(int x, int y);
    
    void keyPressed(int key);
    
    void checkBlobs();
    
    
#ifdef USE_VIDEO
    vector<ofVideoPlayer*>       vidGrabber;
#elif defined(USE_WEBCAM)
    vector<ofVideoGrabber*>       vidGrabber;
#else
    vector<ofxMacamPs3Eye*> vidGrabber;
    vector<ofxMacamPs3EyeDeviceInfo*> deviceList = ofxMacamPs3Eye::getDeviceInfoList();
#endif
    ofFbo fbo;
    ofPixels pix;
    
    int imgWidth, imgHeight;
    
    ofxCvColorImage		fullImg, colorImg;
    ofxCvGrayscaleImage grayImage;
    
    
    int  threshold;
    ofPoint warpPoints[4];          //the points from the source image to use. These can be adjusted.
    ofPoint warpEndPoints[4];       //the points into the end image. These will always be the corners of our end image.
    
    ofVec2f cupOffset;
    int framesBeforeKillingCup;
    
    float maxCompactness;               //make this lower to have it require more circular blobs
    ofxCvContourFinder 	contourFinder;  //for finding the blobs
    
    int nextID;
    
    
    //debug stuff
    float timeForDoubleKeyPress;
    float lastKeyPressTime; //for double presses
    
    
};


#endif /* defined(__DrinkRink__CupTrackerBlob__) */
