#pragma once

#include "ofMain.h"

#include "VectorField.h"

#include "Scene.h"
#include "SportsScene.h"

#include "CupTracker.h"




enum ModeType { MODE_BALL, MODE_STREAM, NUM_MODES };

class ofApp : public ofBaseApp{
public:
    
    void setup();
    
    void reset();
    
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
    Scene * curScene;
    
    //debug values
    bool showField, showDebugInfo, showCupDebug;
    
    
};
