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
#include "CamSettings.h"

#include "ofxOpenCv.h"
//#include "ofxFidMain.h"
#include "ofxMacamPs3Eye.h"

#include "ofxARToolkitPlus.h"



class CupTrackerCam : public CupTracker{
public:
    
    void setupCustom();
    void updateFromPanel(ofxControlPanel * panel);
    void update();
    void draw();
    void drawARTags(int x, int y);
    
    void keyPressed(int key);
    
    void checkARTag(int idNum);
    
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
    
    //fucking around with seperate threshold areas because god isn't real
    bool                useThreshMap;
    ofPixels            grayImagePixels;
    ofxCvGrayscaleImage grayImageThresh;
    int                 thresholdSections[24];
    
    //standard images
    ofxCvColorImage		fullImg, colorImg;
    ofxCvGrayscaleImage grayImageNoThresh;
    ofxCvGrayscaleImage grayBGImage;
    ofxCvGrayscaleImage grayImageDemo;      //this one is just so we can see what's hapenning. We can remove it if it is slowing things down
    
    //ofxFiducialTracker	fidfinder;
    ofxARToolkitPlus ARKit;
    
    int  threshold;
//    ofPoint warpPoints[4];          //the points from the source image to use. These can be adjusted.
//    ofPoint warpEndPoints[4];       //the points into the end image. These will always be the corners of our end image.
    
    ofVec2f cupOffset;
    int framesBeforeKillingCup;
    
    bool takeBGImage;
    bool takeBGImageOnStart;
    
    //flipping the camera images and adjusting the order
    bool cam0onLeft;
    bool flipHorz;
    bool flipVert;
    ofVec2f camPosAdjust[2];
    
    //modifying the positions returned by the AR Tracker
    float cupLeftX, cupRightX;
    float cupTopY, cupBottomY;
    //ofVec2f cupAdjust;
    
    float cupAdjustLeftX, cupAdjustRightX;
    float cupAdjustLeftYtop, cupAdjustRightYtop;
    float cupAdjustLeftYbot, cupAdjustRightYbot;
    
    float camLeftRotateVal, camRightRotateVal;
    
    bool invertGreyImage;
    
    //ofVec2f cupAdjustLeftSide, cupAdjustRightSide;
    
    //trying out cycling the threhsold values of areas that have no cups
    bool doingThresholdCycling;
    float thresholdCyclingPaddingDist;
    
    float thresholdCyclingMinVal, thresholdCyclingMaxVal;
    float thresholdCyclingSpeed;
    
    bool zoneHasCup[24];
    ofRectangle threshZoneBorders[24];
    
    //adding in blobs because fuck it
    ofxCvContourFinder 	contourFinder;
    
    //debug stuff
    float timeForDoubleKeyPress;
    float lastKeyPressTime; //for double presses
   
    
    
};

#endif /* defined(__DrinkRink__CupTrackerCam__) */
