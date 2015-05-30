//
//  CupTower.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "CupTower.h"


void CupTower::setup(float startX, float startY, VectorField * _field){
    
    pos.set(startX, startY);
    field = _field;
    
    hasBeenRemoved = false;
    
    isDebugSelected = false;
    
    range = 100;
    radius = 30;
}

void CupTower::update(){
    
    //testing
    float testStrength = 4;
    field->addOutwardCircle(pos.x, pos.y, range, testStrength);
    
    
    customUpdate();
}

void CupTower::draw(){
    ofSetColor(40,90,220, 100);
    //ofCircle(pos.x, pos.y, range);
    
    ofSetColor(0, 230, 80, 220);
    ofCircle(pos.x, pos.y, radius);
    
    customDraw();
}

void CupTower::onMouseDown(int x, int y, int button){
    if ( ofDistSquared(x,y, pos.x, pos.y) < radius*radius){
        isDebugSelected = true;
        distFromMouseWhenSelected.x = pos.x - x;
        distFromMouseWhenSelected.y = pos.y - y;
    }
}
void CupTower::onMouseDrag(int x, int y, int button){
    if (isDebugSelected){
        pos.x = x + distFromMouseWhenSelected.x;
        pos.y = y + distFromMouseWhenSelected.y;
    }
}
void CupTower::onMouseRelease(int x, int y, int button){
    isDebugSelected = false;
}