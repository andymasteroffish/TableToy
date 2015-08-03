//
//  FieldParticle.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#ifndef __emptyExample__FieldParticle__
#define __emptyExample__FieldParticle__

#include "ofMain.h"
#include "VectorField.h"

class FieldParticle{
public:
    
    FieldParticle(float x, float y, ofColor _col);
    void setup(float x, float y, ofColor _col);
    void update(float deltaTime, VectorField * field);
    void draw(float alphaPrc);
    void setAlpha();
    
    
    ofVec2f pos, vel;
    float fric;
    
    ofColor col;
    float velToStartFading;
    
    float timer, killTime;
    float killVel;
    bool killFlag;
    
    //trying out different effects
    bool showDot;
    float dotSize;
    
    bool useNoiseWiggle;
    float noiseWiggleRange, noiseWigglePower;
    float noiseSeed;
    
    bool useTrails;
    int numTrailPositions;
    float trailStartWidth, trailEndWidth;
    vector<ofVec2f> trailPos;
    
    
    
    
    
};

#endif /* defined(__emptyExample__FieldParticle__) */
