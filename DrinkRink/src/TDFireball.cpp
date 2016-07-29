//
//  TDFireball.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFireball.h"



void TDFireball::setup(ofVec2f _pos, ofImage * _pic, ofxControlPanel * panel){
    pos = _pos;
    pic = _pic;
    
    //startSize = 250;
    //dmg = 3;
    startSize = panel->getValueF("BOMB_TOWER_BOMB_SIZE");
    dmg = panel->getValueF("BOMB_TOWER_DAMAGE");
    
    killTime = 0.5;
    timer = killTime;
    
    angleDeg = ofRandom(360);
    
    col.set(240, 40, 20);
}

void TDFireball::update(float deltaTime){
    angleDeg += deltaTime * 100;
    
    timer -= deltaTime;
    
}

void TDFireball::draw(float alphaPrc){
    
    float prc = CLAMP(timer / killTime, 0, 1);
    prc = powf(prc, 1.5);   //curve it
    
    float size = startSize * prc;
    
//    ofSetColor(col.r, col.g, col.b, 180 * alphaPrc);
//    ofFill();
//    ofCircle(pos.x, pos.y, size);
    
    float colorPrc = abs(sin(ofGetElapsedTimef() * 10));
    ofColor redTint(255,100,100);
    ofColor thisCol;
    thisCol.r = colorPrc * ofColor::white.r + (1.0-colorPrc) * redTint.r;
    thisCol.g = colorPrc * ofColor::white.g + (1.0-colorPrc) * redTint.g;
    thisCol.b = colorPrc * ofColor::white.b + (1.0-colorPrc) * redTint.b;
    thisCol.a = 255 * alphaPrc;
    
    ofSetColor(thisCol);//, 255*alphaPrc);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(angleDeg);
    float curScale = size/(pic->getWidth()/2 - 60);
    ofScale(curScale, curScale);
    pic->draw(-pic->getWidth()/2,-pic->getHeight()/2);
    ofPopMatrix();
}