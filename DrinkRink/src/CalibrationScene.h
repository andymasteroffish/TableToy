//
//  CalibrationScene.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/24/15.
//
//

#ifndef __DrinkRink__CalibrationScene__
#define __DrinkRink__CalibrationScene__

#include "ofMain.h"
#include "Scene.h"
#include "CupTrackerCam.h"

#include "CamSettings.h"

#include "Tower.h"
#include "TowerCalibration.h"

class CalibrationScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    
    void drawCustom();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    
    void addTower(CupInfo thisCup);
    void checkPanelValuesCustom(ofxControlPanel * panel);
    
    bool usingDebug;    //don't do anything if we're not using the camera
    
    CupTrackerCam * tracker;
    
    ofxControlPanel * controlPanel;
    
    ofVec2f drawOffset;
    float drawScale;
    float maxDisplayHeight;
    
    //dragging shit
//    int curPointDragging;
//    ofVec2f draggingOffset;
    
    bool showThresholdGrid;
    
};

#endif /* defined(__DrinkRink__CalibrationScene__) */
