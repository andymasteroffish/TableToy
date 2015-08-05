//
//  Tower.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Tower.h"


void Tower::setup(CupInfo thisCup, VectorField * _field){
    
    angle = ofRandom(TWO_PI);
    
    uniqueID = thisCup.uniqueID;
    startTime = thisCup.startTime;
    
    pos.set(thisCup.pos.x, thisCup.pos.y);
    field = _field;
    
    hasBeenRemoved = false;
    hasBeenCheckedThisFrame = true;
    
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
    
    towerSize = 40;    //how big the physical cup is
    
    
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

void Tower::draw(float alphaPrc){
    
    customDraw();
    //show a debug image
    ofFill();
    ofSetColor(debugColor.r, debugColor.g, debugColor.b, debugColor.a * alphaPrc);
    ofCircle(pos.x, pos.y, towerSize);
    ofSetColor(0);
    ofSetLineWidth(1);
    ofLine(pos.x, pos.y, pos.x+cos(angle)*towerSize*0.8, pos.y+sin(angle)*towerSize*0.8);
}