//
//  TDBulletHit.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDBulletHit.h"




void TDBulletHit::setup(ofVec2f _pos, ofImage * _pic){
    pos = _pos;
    pic = _pic;
    
    killTime = 0.1;
    angleDeg = ofRandom(360);
    
    timer = 0;
    killMe = false;
    
}

void TDBulletHit::update(float deltaTime){
    timer += deltaTime;
    if (timer > killTime){
        killMe = true;
    }
    
}

void TDBulletHit::draw(float alphaPrc){
    
    ofSetColor(255, 255*alphaPrc);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(angleDeg);
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    ofPopMatrix();
    
}