//
//  TDFireball.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFireball.h"



void TDFireball::setup(ofVec2f _pos){
    pos = _pos;
    
    startSize = 250;
    dmg = 3;
    
    killTime = 0.5;
    timer = killTime;
    
    col.set(240, 40, 20);
}

void TDFireball::update(float deltaTime){
    
    timer -= deltaTime;
    
}

void TDFireball::draw(float alphaPrc){
    
    float prc = CLAMP(timer / killTime, 0, 1);
    prc = powf(prc, 1.5);   //curve it
    
    float size = startSize * prc;
    
    ofSetColor(col.r, col.g, col.b, 180 * alphaPrc);
    ofFill();
    ofCircle(pos.x, pos.y, size);
}