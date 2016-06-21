//
//  TowerTD.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerTD.h"

void TowerTD::customSetup(){
    towerType = "td_shooter";
    
    debugColor.setHex(0xabb1a9);
    
    timeBetweenShots = 1;
    shotTimer = timeBetweenShots;
    spawnShot = false;
}

void TowerTD::customUpdate(){
    shotTimer -= deltaTime;
    if (shotTimer < 0){
        spawnShot = true;
        shotTimer = timeBetweenShots;
    }
}

void TowerTD::customDraw(float alphaPrc){
   
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    ofRotate( ofRadToDeg(angle) );
    
//    ofSetColor(0);
//    ofLine(0, 0, towerSize*1.3, 0);
    
    ofSetColor(255, 255 * alphaPrc);
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    
    ofPopMatrix();
}
