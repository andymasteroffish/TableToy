//
//  Ball.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Ball.h"

Ball::Ball(){
    setup(false);
}

Ball::Ball(bool spawnOnTop){
    setup(spawnOnTop);
}

void Ball::setup(bool spawnOnTop){
    
    friction = 0.995;
    
    float startVel = 1;
    float startPadding = 10;
    float startingXOffset = ofRandom(-10,10);
    
    if (spawnOnTop){
        pos.set(ofGetWidth()/2+startingXOffset, -startPadding);
        vel.set(0,startVel);
    }else{
        pos.set(ofGetWidth()/2+startingXOffset, ofGetHeight() + startPadding);
        vel.set(0,-startVel);
    }
    
    justSpawned = true;
}

void Ball::addRepulsionForce(Ball * other, float radius, float maxForce){
    if (justSpawned){
        return;
    }
    
    ofVec2f diff = pos - other->pos;
    
    if (diff.length() < radius){
        float prc = 1 - (diff.length() / radius);
        diff.normalize();
        
        vel += diff * prc * maxForce;
        other->vel -= diff * prc * maxForce;
    }
}

void Ball::update(VectorField * field){
    
    if (!justSpawned){
        vel += field->getForceFromPos(pos);
    }
    
    vel *= friction;
    
    pos += vel;
    
    
    
    //simple bounce
    if (!justSpawned){
        if (pos.x < 0){
            pos.x = 0;
            vel.x = MAX(vel.x, -vel.x);
        }
        if (pos.x > ofGetWidth()){
            pos.x = ofGetWidth();
            vel.x = MIN(vel.x, -vel.x);
        }
        if (pos.y < 0){
            pos.y = 0;
            vel.y = MAX(vel.y, -vel.y);
        }
        if (pos.y > ofGetHeight()){
            pos.y = ofGetHeight();
            vel.y = MIN(vel.y, -vel.y);
        }
    }else{
        if (pos.x > 1 && pos.x < ofGetWidth()-1 && pos.y > 1 && pos.y < ofGetHeight()-1){
            justSpawned = false;
        }
    }
    
}

void Ball::draw(){
    ofCircle(pos.x, pos.y, 15);
}