#pragma once

#include "ofMain.h"
#include "ofxControlPanel.h"

#include "VectorField.h"

#include "Scene.h"
#include "SportsScene.h"
#include "StreamScene.h"
#include "FlyersScene.h"

#include "CupTracker.h"
#include "CupTrackerDebug.h"
#include "CupTrackerCam.h"


class ofApp : public ofBaseApp{
public:
    
    void setup();
    
    void scrollModes();
    
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setPreset(int idNum);
    
    
    //general
    float deltaTime, prevFrameTime;
    
    //reading form the cam
    bool usingDebugCupTracker;
    CupTracker * cupTracker;
    
    //scene
#define NUM_SCENES 3
#define SCENE_SPORTS 0
#define SCENE_STREAM 1
#define SCENE_FLYERS 2
    Scene * scenes[NUM_SCENES];
    Scene * curScene;
    Scene * fadingScene;
    int curSceneID;
    
    //debug values
    bool showField, showDebugInfo, showCupDebug;
    
    
    //control panel
    bool showPanel;
    ofxControlPanel	panel;
    int curPanel;
    
    
};
