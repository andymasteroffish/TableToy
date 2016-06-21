//
//  TDBullet.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDBullet.h"


void TDBullet::setup(ofVec2f _pos, float angle, bool _isFire){
    
    pos.set(_pos);
    
    isFire = _isFire;
    
    dmg = 1;
    float speed = 500;
    size = 10;
    col.set(0,0,0);
    
    if (isFire){
        dmg = 0;
        speed = 300;
        size = 20;
        col.set(250,20,10);
    }
    
    vel.x = speed * cos(angle);
    vel.y = speed * sin(angle);
    
}

void TDBullet::update(float deltaTime){
    
    pos += vel * deltaTime;
    
}

void TDBullet::draw(float alphaPrc){
    
    ofSetColor(col.r, col.g, col.b, 255 * alphaPrc);
    ofCircle(pos.x, pos.y, size);
    
}