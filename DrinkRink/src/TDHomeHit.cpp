//
//  TDHomeHit.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDHomeHit.h"


void TDHomeHit::setup(ofVec2f _pos){
    
    pos = _pos;
    
    growthPerSec = 1400;
    killDist = 1300;
    
    fadeDist = killDist * 0.75;
    
    curSize = 10;
    killMe = false;
    
}

void TDHomeHit::update(float deltaTime){
    curSize += growthPerSec * deltaTime;
    
    if (curSize > killDist){
        killMe = true;
    }
}

void TDHomeHit::draw(float alphaPrc){
    
    ofColor colors[2];
    colors[0].set(250, 20, 20, 100 * alphaPrc);
    colors[1].set(250, 20, 20, 200 * alphaPrc);
    
    for (int i=0; i<2; i++){
        if (curSize > fadeDist){
            float prc = (curSize-fadeDist)/(killDist-fadeDist);
            colors[i].a *= (1-prc);
        }
    }
    
    ofSetLineWidth(50);
    
    ofNoFill();
    ofSetColor(colors[0]);
    ofCircle(pos.x, pos.y, curSize - 30);
    ofSetColor(colors[0]);
    ofCircle(pos.x, pos.y, curSize + 30);
    
    ofSetColor(colors[1]);
    ofCircle(pos.x, pos.y, curSize);
    
//    ofNoFill();
//    for (int i=0; i<3; i++){
//        float offset = (i-1) * 10;
//        ofSetColor(colors[i]);
//        ofCircle(pos.x, pos.y, curSize + offset);
//    }
    
    //set it back
    ofSetLineWidth(1);
    
}