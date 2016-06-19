//
//  Tower.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Tower.h"

//The basic Tower setup is called every time a new cup is identified (including when a cup that was previously removed is placed back down)
//customSetup() is called near the end of this funciton. You can define an override function for customSetup to do any additional setup your Tower requires
void Tower::setup(CupInfo thisCup, VectorField * _field){
    
    angle = ofRandom(TWO_PI);
    
    uniqueID = thisCup.uniqueID;
    startTime = thisCup.startTime;
    
    pos.set(thisCup.pos.x, thisCup.pos.y);
    field = _field;
    
    towerType = "none";
    
    hasBeenRemoved = false;
    hasBeenCheckedThisFrame = true;
    
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
    
    towerSize = 80;    //how big the physical cup is
    
    randVal = ofRandom(9999);
    
    particleType = PARTICLE_NO_TYPE;
    particleTypeWeight = 1;
    
    customSetup();
    
    startingRange = range;
    
    calculateFieldRange();
}

//This is called whenever the CupTracker senses that the cup moved. It updates the Tower's game world position based on the cups new physical location
void Tower::setFromCupInfo(CupInfo thisInfo){
    pos.set(thisInfo.pos);
    angle = thisInfo.angle;
}

//Update is called every frame.
//Use the overrid function customUpdate() to do any every-frame calculations in your Tower class
void Tower::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    customUpdate();
}

//Call this any time you change the range
//Do not edit field range manually
void Tower::calculateFieldRange(){
    float radiusPrct = range / (float)field->gameWidth;
    fieldRange = (float)(radiusPrct * field->fieldWidth);
}

//Use the override function customDraw() to draw things for your Tower
//This defalt function will draw a debug image if that is turned on
//the customDraw also passes an alphaPrc value, which is a value form 1 to 0 used to fade between scenes. You may want your draw to multiply alpha values by it so that your Tower fades out gracefully.
void Tower::draw(float alphaPrc, bool showCupDebug){
    
    customDraw(alphaPrc);
    
    if (showCupDebug){
        //show a debug image
        ofFill();
        ofSetColor(debugColor.r, debugColor.g, debugColor.b, debugColor.a * alphaPrc);
        ofCircle(pos.x, pos.y, towerSize);
        ofSetColor(0);
        ofSetLineWidth(1);
        ofLine(pos.x, pos.y, pos.x+cos(angle)*towerSize*0.8, pos.y+sin(angle)*towerSize*0.8);
    }
}