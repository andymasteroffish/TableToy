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
    
    ofVec2f pos, vel;
    float fric;
    
    ofColor col;
    float velToStartFading;
    
    float timer, killTime;
    float killVel;
    bool killFlag;
    
    FieldParticle(float x, float y);
    void setup(float x, float y);
    void update(float deltaTime, VectorField * field);
    void draw(float alphaPrc);
    void setAlpha();
    
};

#endif /* defined(__emptyExample__FieldParticle__) */
