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
    
    Ball();
    Ball(bool spawnOnTop, int _gameWidth, int _gameHeight);
    
    void setup(bool spawnOnTop, int _gameWidth, int _gameHeight);
    void addRepulsionForce(Ball * other, float radius, float maxForce);
    void update(VectorField * field);
    void draw();
    
    ofVec2f pos, vel;
    
    float friction;
    
    bool justSpawned;
    
    int gameWidth, gameHeight;
    
    
};

#endif /* defined(__emptyExample__Ball__) */
