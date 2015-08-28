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
    Ball(bool spawnOnTop, int _gameWidth, int _gameHeight, ofColor _col);
    
    void setup(bool spawnOnTop, int _gameWidth, int _gameHeight, ofColor _col);
    void addRepulsionForce(Ball * other, float radius, float maxForce);
    void update(VectorField * field);
    void draw(float alphaPrc);
    
    ofVec2f pos, vel;
    
    int drawSize;
    
    float friction;
    
    bool justSpawned;
    
    int gameWidth, gameHeight;
    
    ofColor col;
    
    ofVec2f rollVal;
    
};

#endif /* defined(__emptyExample__Ball__) */
