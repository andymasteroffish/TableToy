//
//  TowerTD.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerTD.h"

void TowerTD::customSetup(){
    towerType = "tower_defense";
    
    debugColor.setHex(0xabb1a9);
    
    timeBetweenShots = 1;
    
    spawnShot = false;
    
    modTimeOffset = uniqueID * 0.11;
}

void TowerTD::setupTowerDefense(TD_TOWER_TYPE type, ofImage * _pic){
    tdType = type;
    pic = _pic;
    
    if (tdType == TD_SHOOTER){
        timeBetweenShots = 1;
    }
    if (tdType == TD_ICE){
        timeBetweenShots = 5;
    }
    if (tdType == TD_FIRE){
        timeBetweenShots = 3;
    }
    
    modTimeLastFrame = fmod(ofGetElapsedTimef()+modTimeOffset, timeBetweenShots);
}

void TowerTD::customUpdate(){
    
    float modTime = fmod(ofGetElapsedTimef()+modTimeOffset, timeBetweenShots);
    if (modTime < modTimeLastFrame){
        spawnShot = true;
    }
    modTimeLastFrame = modTime;
    
}

void TowerTD::customDraw(float alphaPrc){
   
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    ofRotate( ofRadToDeg(angle) );
    
    ofSetColor(255, 255 * alphaPrc);
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    
    ofPopMatrix();
}
