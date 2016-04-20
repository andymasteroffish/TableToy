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

#include "CupTracker.h"
#include "CupTrackerDebug.h"
#include "CupTrackerCam.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    
    void scrollScenes();
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
    
    void setPreset(int idNum);
    
    
    //general
    float deltaTime, prevFrameTime;
    int gameWidth, gameHeight;      //the size in pixels of the board. The image may be scaled up or down, but this is the size used for calculations
    
    float displayScale;
    ofVec2f displayAdjust;
    
    //reading from the cam
    bool usingDebugCupTracker;
    CupTracker * cupTracker;
    
    //scene
#define NUM_SCENES          4
#define SCENE_CALIBRATION   0
#define SCENE_SPORTS        1
#define SCENE_STREAM        2
#define SCENE_FLYERS        3
    Scene * scenes[NUM_SCENES];
    Scene * curScene;
    Scene * fadingScene;
    int curSceneID;
    
    //drawing into an FBO to fuck with the two sides of teh screen
    ofFbo fbo;
    ofVec2f rightScreenOffset;
    float rightScreenRotate;
    
    //debug values
    bool showField, showDebugInfo, showCupDebug;
    
    
    //control panel
    bool showPanel;
    ofxControlPanel	panel;
    int curPanel;
    
    
};
