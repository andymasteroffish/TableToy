//
//  TDBullet.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDBullet.h"


void TDBullet::setup(ofVec2f _pos, float _angle, float startDist, bool _isFire, ofImage * _pic, ofxControlPanel * panel){
    
    pos.set(_pos);
    
    pic = _pic;
    angle = _angle;
    
    isFire = _isFire;
    
    float speed = 500;
    
    //shoot tower bullets
    if (!isFire){
        speed = panel->getValueF("SHOOT_TOWER_BULLET_SPEED");
        dmg = panel->getValueF("SHOOT_TOWER_DAMAGE");
        size = 10;
        
        col.set(0,0,0);
    }
    //fireball bullet
    else{
    
        speed = panel->getValueF("BOMB_TOWER_BULLET_SPEED");
        dmg = 0;
        size = 20;
        col.set(250,20,10);
    }
    
    
    pos.x += cos(angle) * startDist;
    pos.y += sin(angle) * startDist;
    
    vel.x = speed * cos(angle);
    vel.y = speed * sin(angle);
    
}

void TDBullet::update(float deltaTime){
    
    pos += vel * deltaTime;
    
}

void TDBullet::draw(float alphaPrc){
    
    ofSetColor(255, 255 * alphaPrc);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate( ofRadToDeg(angle) );
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    ofPopMatrix();
    
//    ofSetColor(col.r, col.g, col.b, 255 * alphaPrc);
//    ofCircle(pos.x, pos.y, size);
    
}