//
//  Ball.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__Ball__
#define __emptyExample__Ball__

#include "ofMain.h"
#include "VectorField.h"

class Ball{
public:
    
    ofVec2f pos, vel;
    
    float friction;
    
    void setup();
    void addRepulsionForce(Ball * other, float radius, float maxForce);
    void update(VectorField * field);
    void draw();
    
};

#endif /* defined(__emptyExample__Ball__) */
