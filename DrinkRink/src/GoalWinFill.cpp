//
//  GoalWinFill.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 8/27/15.
//
//

#include "GoalWinFill.h"


void GoalWinFill::setup(){
    isActive = false;
    
    numRings = 7;
    timeBeforeRings = 8;
    timeBetweenRings = 0.2;
    
    growthRate = 600;
    
    sat = 255;
    bri = 255;
}

void GoalWinFill::start(Goal winningGoal){
    isActive = true;
    timer = 0;
    
    baseHue = winningGoal.baseCol.getHue();
    pos = winningGoal.pos;
}

void GoalWinFill::update(float deltaTime){
    
    if (isActive){
        timer += deltaTime;
    }
    
}

void GoalWinFill::draw(float alphaPrc){
    if (!isActive){
        return;
    }
    
    
    
    ofFill();
    
    for (float i=0; i<numRings; i++){
        float thisTimer = timer - timeBeforeRings - timeBetweenRings * (float)i;
        if (thisTimer > 0){
            float thisSize = growthRate * thisTimer;
            
            float thisHue = baseHue + sin( i + ofGetElapsedTimef() ) * 20;
            
            if (thisHue > 255)  thisHue -= 256;
            if (thisHue < 0)    thisHue += 256;
            
            ofColor thisCol;
            thisCol.setHsb(thisHue, sat, bri);
            
            ofSetColor(thisCol, 255*alphaPrc);
            ofCircle(pos.x, pos.y, thisSize);
        }
    }
}