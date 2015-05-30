//
//  Ball.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Ball.h"


void Ball::setup(){
    friction = 0.99;
    
    vel.set(0,0);
}

void Ball::addRepulsionForce(Ball * other, float radius, float maxForce){
    ofVec2f diff = pos - other->pos;
    
    if (diff.length() < radius){
        float prc = 1 - (diff.length() / radius);
        diff.normalize();
        vel += diff * prc * maxForce;
    }
}

void Ball::update(VectorField * field){
    
    vel += field->getForceFromPos(pos);
    
    vel *= friction;
    
    pos += vel;
    
    
    
    //simple bounce
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
    
}

void Ball::draw(){
    ofCircle(pos.x, pos.y, 5);
}