//
//  TDBullet.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDBullet.h"


void TDBullet::setup(ofVec2f _pos, float angle){
    
    pos.set(_pos);
    
    dmg = 1;
    
    size = 10;
    
    float speed = 500;
    vel.x = speed * cos(angle);
    vel.y = speed * sin(angle);
    
}

void TDBullet::update(float deltaTime){
    
    pos += vel * deltaTime;
    
}

void TDBullet::draw(){
    
    ofSetColor(0);
    ofCircle(pos.x, pos.y, size);
    
}