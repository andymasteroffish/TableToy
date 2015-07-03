//
//  Tower.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Tower.h"


void Tower::setup(float startX, float startY, int _uniqueID, float _startTime, VectorField * _field){
    
    angle = ofRandom(TWO_PI);
    
    uniqueID = _uniqueID;
    startTime = _startTime;
    
    pos.set(startX, startY);
    field = _field;
    
    hasBeenRemoved = false;
    hasBeenCheckedThisFrame = true;
    
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
    
    towerSize = 30;    //how big the physical cup is
    
    
    customSetup();
    
    calculateFieldRange();
}

void Tower::setFromCupInfo(CupInfo thisInfo){
    pos.set(thisInfo.pos);
    angle = thisInfo.angle;
    
}

void Tower::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    customUpdate();
}

//call this any time you change the range
void Tower::calculateFieldRange(){
    float radiusPrct = range / (float)field->externalWidth;
    fieldRange = (float)(radiusPrct * field->fieldWidth);
}

void Tower::draw(){
    
    customDraw();
    
    //show a debug image
    ofSetColor(debugColor);
    ofCircle(pos.x, pos.y, towerSize);
    ofSetColor(0);
    ofLine(pos.x, pos.y, pos.x+cos(angle)*towerSize*0.8, pos.y+sin(angle)*towerSize*0.8);
}