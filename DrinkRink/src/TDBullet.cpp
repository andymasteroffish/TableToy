//
//  TDBullet.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDBullet.h"


void TDBullet::setup(ofVec2f _pos, float angle, float startDist, bool _isFire, ofxControlPanel * panel){
    
    pos.set(_pos);
    
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
    
    ofSetColor(col.r, col.g, col.b, 255 * alphaPrc);
    ofCircle(pos.x, pos.y, size);
    
}