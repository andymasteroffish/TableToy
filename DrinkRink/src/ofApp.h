#pragma once

#include "ofMain.h"
#include "ofxControlPanel.h"

#include "CamSettings.h"

#include "VectorField.h"

#include "Scene.h"
#include "CalibrationScene.h"
#include "SportsScene.h"
#include "StreamScene.h"
#include "FlyersScene.h"
#include "TowerDefenseScene.h"
#include "TitleCardScene.h"
#include "BeamScene.h"
#include "DeepPathScene.hpp"
#include "StreamBlobScene.hpp"
#include "EyeScene.hpp"
#include "PaintScene.hpp"

#include "CupTracker.h"
#include "CupTrackerDebug.h"
#include "CupTrackerCam.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void loadSceneTimes();
    void setupPanel();
    
    void scrollScenes();
    void randomizeSceneOrder();
    void setScene(int sceneID);
    
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
    
    
    //general
    float deltaTime, prevFrameTime;
    int gameWidth, gameHeight;      //the size in pixels of the board. The image may be scaled up or down, but this is the size used for calculations
    
    float displayScale;
    ofVec2f displayAdjust;
    
    //reading from the cam
    bool usingDebugCupTracker;
    CupTracker * cupTracker;
    
    //scene
#define NUM_SCENES          10
#define SCENE_CALIBRATION   0
#define SCENE_TITLE_CARD    1
#define SCENE_SPORTS        2
#define SCENE_STREAM        3
#define SCENE_TOWER_DEFENSE 4
#define SCENE_BEAM          5
#define SCENE_DEEP_PATH     6
#define SCENE_STREAM_BLOB   7
#define SCENE_EYE           8
#define SCENE_PAINT         9
//#define SCENE_FLYERS        3
    Scene * scenes[NUM_SCENES];
    Scene * curScene;
    Scene * fadingScene;
    int curSceneID;
    
    vector<int> sceneOrder;
    
    
    //drawing into an FBO to fuck with the two sides of teh screen
    ofFbo fbo;
    ofVec2f rightScreenOffset, leftScreenOffset;
    float rightScreenRotate, leftScreenRotate;
    
    //debug values
    bool showField, showDebugInfo, showCupDebug;
    
    
    //control panel
    bool showPanel;
    ofxControlPanel	panel;
    int curPanel;
    
    
};
