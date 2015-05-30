#pragma once

#include "ofMain.h"

#include "VectorField.h"
#include "FieldParticle.h"
#include "Ball.h"

#include "CupTower.h"

class ofApp : public ofBaseApp{
public:
    void setup();
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
    
    void makeFieldParticles();
    
    //general
    float deltaTime, prevFrameTime;
    
    
    //the field
    VectorField field;
    
    vector<FieldParticle *> fieldParticles;
    
    //the balls
    vector<Ball *> balls;
    float ballRepulsionRange;
    float ballRepulsionMaxForce;
    
    vector<CupTower *> towers;
    
    
    //debug values
    bool showField, showDebugInfo;
    
    
};
