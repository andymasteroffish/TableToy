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

enum ParticleType{ PARTICLE_SPORT, PARTICLE_GOAL_LEFT, PARTICLE_GOAL_RIGHT };

class FieldParticle{
public:
    
    FieldParticle(float x, float y, ofColor _col);
    void setup(float x, float y, ofColor _col);
    void update(float deltaTime, VectorField * field);
    void draw(float alphaPrc);
    void setAlpha();
    
    void setType(ParticleType type);
    
    
    ofVec2f pos, vel;
    float fric;
    
    ofColor col;
    float velToStartFading;
    
    float timer, killTime;
    float killVel;
    bool killFlag;
    
    float noiseSeed;
    
    //trying out different effects
    bool showDot;
    bool fillDot;
    float dotSize;
    
    bool useNoiseWiggle;
    float noiseWiggleRange, noiseWigglePower;
    float noiseWiggleRate;
    
    bool useTrails;
    int numTrailPositions;
    float trailStartWidth, trailEndWidth;
    vector<ofVec2f> trailPos;
    
    bool usePic;
    ofImage * pic;
    float picScale;
    
    
    
    
    
};

#endif /* defined(__emptyExample__FieldParticle__) */