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
    
    targetAngle = thisCup.angle;
    curAngle = targetAngle;
    
    uniqueID = thisCup.uniqueID;
    startTime = thisCup.startTime;
    
    pos.set(thisCup.pos.x, thisCup.pos.y);
    targetPos = pos;
    
    field = _field;
    
    towerType = "none";
    
    hasBeenRemoved = false;
    hasBeenCheckedThisFrame = true;
    
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
    
    towerSize = 80;    //how big the physical cup is
    
    angleXeno = 0.75;
    posXeno = 0.75;
    
    randVal = ofRandom(9999);
    
    particleType = PARTICLE_NO_TYPE;
    particleTypeWeight = 1;
    
    customSetup();
    
    startingRange = range;
    
    calculateFieldRange();
}

//This is called whenever the CupTracker senses that the cup moved. It updates the Tower's game world position based on the cups new physical location
void Tower::setFromCupInfo(CupInfo thisInfo){
    targetPos.set(thisInfo.pos);
    targetAngle = thisInfo.angle;
}

//Update is called every frame.
//Use the overrid function customUpdate() to do any every-frame calculations in your Tower class
void Tower::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    elapsedTime = ofGetElapsedTimef() - startTime;
    
    pos = posXeno * pos + (1-posXeno) * targetPos;
    
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    //adjust the angle
    float curAngleHigh = curAngle + TWO_PI;
    float curAngleLow = curAngle - TWO_PI;
    if ( abs(curAngleHigh-targetAngle) < abs(curAngleLow-targetAngle) && abs(curAngleHigh-targetAngle) < abs(curAngle-targetAngle)){
        curAngle = curAngleHigh;
    }
    else if ( abs(curAngleLow-targetAngle) < abs(curAngleHigh-targetAngle) && abs(curAngleLow-targetAngle) < abs(curAngle-targetAngle)){
        curAngle = curAngleLow;
    }
    
    curAngle = angleXeno * curAngle + (1-angleXeno) * targetAngle;
    
    if(isnan(curAngle)) curAngle = targetAngle;
    

    
    //update
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
        ofLine(pos.x, pos.y, pos.x+cos(curAngle)*towerSize*0.8, pos.y+sin(curAngle)*towerSize*0.8);
    }
}


void Tower::drawSportsTower(float alphaPrc, bool strongerBounce){
    
    ofSetColor(debugColor.r, debugColor.g, debugColor.b, 200 * alphaPrc);
    
    int numCircles = 20;
    float angleStep = TWO_PI/numCircles;
    
    float growTime = 0.4;
    float bounceTime = 0.07;
    
    float targetSize = 30;
    float bigSize = targetSize * 1.5;
    float circleSize = ofMap(elapsedTime, 0, growTime, 0, targetSize, true);
    
    if (elapsedTime > growTime && elapsedTime <= growTime+bounceTime){
        circleSize = ofMap(elapsedTime, growTime, growTime+bounceTime, targetSize, bigSize, true);
    }
    if (elapsedTime > growTime+bounceTime && elapsedTime <= growTime+bounceTime*2){
        circleSize = ofMap(elapsedTime, growTime+bounceTime, growTime+bounceTime*2, bigSize, targetSize, true);
    }
    
    
    float drawRange = towerSize*0.8;
    
    
    
    ofFill();
    
    for (int i=0; i<numCircles; i++){
        
        float thisRange = drawRange + ofNoise(i+ofGetElapsedTimef()) * 15;
        
        if (strongerBounce){
            thisRange += ofMap(ofNoise(i+ofGetElapsedTimef()*3), 0, 1, -10, 25);
        }
        
        float xPos = pos.x + cos(angleStep*i) * thisRange;
        float yPos = pos.y + sin(angleStep*i) * thisRange;
        
        ofCircle(xPos, yPos, circleSize);
        
    }
    
    
}


