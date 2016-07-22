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
    
    //animaitons
    shotAnimationTime = 0.2;
    shotAnimationCurve = 0.75;
    shootScale = 1.2;
    
    shotAnimationTimer = shotAnimationTime;
    
}

void TowerTD::setupTowerDefense(TD_TOWER_TYPE type, ofImage * _pic){
    tdType = type;
    pic = _pic;
    
    //MOST OF THESE VALUES ARE BING OVERWRITTEN EVERY FRAME BY CONTROL PANEL RIGHT NOW
    
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
        shotAnimationTimer = 0;
    }
    modTimeLastFrame = modTime;
    
    curScale = 1;
    if (shotAnimationTimer < shotAnimationTime){
        shotAnimationTimer += deltaTime;
        float prc = shotAnimationTimer/shotAnimationTime;
        prc = powf(prc, shotAnimationCurve);
        curScale = shootScale * (1-prc) + 1 * prc;
    }
    
}

void TowerTD::customDraw(float alphaPrc){
   
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    ofRotate( ofRadToDeg(angle) );
    ofScale(curScale, curScale);
    
    ofSetColor(255, 255 * alphaPrc);
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    
    ofPopMatrix();
}
