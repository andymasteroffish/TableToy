//
//  TDFoe.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFoe.h"


void TDFoe::setup(FoeType _type, ofImage * _pic, vector<ofVec2f> * _path, float delay, ofxControlPanel * panel){
    
    type = _type;
    pic = _pic;
    
    path = _path;
    
    delayTimer = delay;
    
    freezeTimer = 0;
    freezeSpeedReduction = 0.25;    //THIS IS BEING OVERWRITTEN EVERY FRAME BY CONTROL PANEL
    
    string typeXMLNames[5] = {"DUMB", "STRONG", "FAST", "WAVE", "IGNORE"};
    
    startingHealth = panel->getValueF(typeXMLNames[type]+"_FOE_HP");
    speed = panel->getValueF(typeXMLNames[type]+"_FOE_SPEED");
    hitCircleSize = panel->getValueF("FOE_HIT_CIRCLE");
    
    waveDist = panel->getValueF("WAVE_FOE_WAVE_DIST");
    wavePeriod = panel->getValueF("WAVE_FOE_WAVE_PERIOD");
    ignoreFoeSpeedIncrease = panel->getValueF("IGNORE_FOE_SPEED_INCREASE");
    
    randVal = ofRandom(0,1000);
    
    //standard values
//    startingHealth = 3;
//    speed = 200;
//    hitCircleSize = 40;
    
//    setStatsFromType();
    
    minDistFromNodeToAdvance = speed / 20;
    
    health = startingHealth;
    
    nextNodeID = 0;
    findNextNode(true);
    
    displayAngle = curAngle;
    
    reachedTheEnd = false;
    killMe = false;
}

void TDFoe::setPos(ofVec2f _pos, int _nextNode){
    
    nextNodeID = _nextNode - 1;
    
    basePos = _pos;
    
    findNextNode(false);
}

void TDFoe::update(float deltaTime){
    
    freezeTimer -= deltaTime;
    
    //check if we are not still waiting to start
    delayTimer -= deltaTime;
    if (delayTimer > 0){
        return;
    }
    
    //move along
    if (!reachedTheEnd){
        
        float freezeAdjust = freezeTimer > 0 ? freezeSpeedReduction : 1;
        
        basePos += velocity * deltaTime * freezeAdjust;
        
        if (type != FOE_WAVE){
            pos = basePos;
        }
        //the wave foe moves along a sin wave
        else{
            
            float adjustAngle = (ofGetElapsedTimef()+randVal) * wavePeriod;// 2;
            float dist = waveDist; //100;
            pos.x = basePos.x + cos(adjustAngle) * dist;
            pos.y = basePos.y + sin(adjustAngle) * dist;
        }
        
        if (ofDistSquared(basePos.x, basePos.y, path->at(nextNodeID).x, path->at(nextNodeID).y) < minDistFromNodeToAdvance*minDistFromNodeToAdvance){
            findNextNode(true);
        }
    }
    
    //xeno the display angle to catch up with the actual angle
    float angleXeno = 0.8;
    
    float angleAdjust = 0;
    while (curAngle + angleAdjust < displayAngle - TWO_PI){
        angleAdjust += TWO_PI;
    }
    while (curAngle - angleAdjust > displayAngle + TWO_PI){
        angleAdjust -= TWO_PI;
    }
    
    float targetAngleNorm = curAngle + angleAdjust;
    float targetAngleHigh = curAngle + TWO_PI + angleAdjust;
    float targetAngleLow = curAngle - TWO_PI + angleAdjust;
    float targetAngle = targetAngleNorm;
    
    if ( abs(displayAngle-targetAngleLow)<abs(displayAngle-targetAngle) && abs(displayAngle-targetAngleLow)<abs(displayAngle-targetAngleHigh)){
        targetAngle = targetAngleLow;
    }
    if ( abs(displayAngle-targetAngleHigh)<abs(displayAngle-targetAngle) && abs(displayAngle-targetAngleHigh)<abs(displayAngle-targetAngleLow)){
        targetAngle = targetAngleHigh;
    }
    
    displayAngle = angleXeno * displayAngle + (1-angleXeno) * targetAngle;
    
    
    
}

void TDFoe::draw(float alphaPrc){
    if (delayTimer > 0){
        return;
    }
    
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate( ofRadToDeg(displayAngle) );
    
    //hit circle
//    ofSetColor(200, 0, 0, 100*alphaPrc);
//    ofCircle(0, 0, hitCircleSize);
    
    //sprite
    ofSetColor(255, 255*alphaPrc);
    if (freezeTimer > 0){
        //tint blue when frozen
        ofSetColor(100,100,255, 255*alphaPrc);
    }
    pic->draw(-pic->getWidth()/2, -pic->getHeight()/2);
    
    ofPopMatrix();
    
}

void TDFoe::findNextNode(bool snapPos){
    //snap it to the current node
    if (snapPos){
        basePos = path->at(nextNodeID);
    }
    
    //advance the node
    nextNodeID++;
    
    //check if we reached the end
    if (nextNodeID >= path->size()){
        reachedTheEnd = true;
        return;
    }
    
    //set the angle and velocity
    curAngle = atan2(path->at(nextNodeID).y-basePos.y, path->at(nextNodeID).x-basePos.x);
    velocity.x = cos(curAngle) * speed;
    velocity.y = sin(curAngle) * speed;
}

void TDFoe::takeDamage(float dmg){
    health -= dmg;
    if (health <= 0){
        killMe = true;
    }
    
    //for the ignore type, the first time they take damage, they shoot towards the goal
    if (health == startingHealth-1 && type == FOE_IGNORE){
        speed *= ignoreFoeSpeedIncrease;// 1.5;
        if (nextNodeID < path->size()-2){
            nextNodeID = path->size()-2;
            findNextNode(false);
        }
    }
}

void TDFoe::freeze(float time){
    freezeTimer = time;
}

//void TDFoe::setStatsFromType(){
//    if (type == FOE_DUMB){
//        //do nothing
//    }
//    if (type == FOE_STRONG){
//        startingHealth *= 2;
//        speed *= 0.5;
//    }
//    if (type == FOE_FAST){
//        speed *= 2;
//    }
//    if (type == FOE_WAVE){
//        speed *= 0.75;
//        startingHealth += 1;
//    }
//}