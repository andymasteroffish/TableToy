#pragma once

#include "ofMain.h"

#include "VectorField.h"

#include "Scene.h"
#include "SportsScene.h"
#include "StreamScene.h"

#include "CupTracker.h"

#include "ofxControlPanel.h"





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
    
    
    //general
    float deltaTime, prevFrameTime;
    
    //reading form the cam
    CupTracker cupTracker;
    
    //scene
#define NUM_SCENES 2
    Scene * scenes[NUM_SCENES];
    Scene * curScene;
    Scene * fadingScene;
    int curSceneID;
    
    //debug values
    bool showField, showDebugInfo, showCupDebug;
    
    
    //control panel
    bool showPanel;
    ofxControlPanel	panel;
    
    
};
