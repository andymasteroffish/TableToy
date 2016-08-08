//
//  TDFoe.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFoe.h"


void TDFoe::setup(FoeType _type, TDAnimationMinder * _anims, vector<ofVec2f> * _path, float delay, ofxControlPanel * panel){
    
    randVal = ofRandom(0,1000);
    
    type = _type;
    anims = _anims;
    
    path = _path;
    
    delayTimer = delay;
    
    //animation
    animTimer = 0;
    curFrame = 0;
    frameTime = 0.15;
    
    hitAnimationTimer = 0;
    hitAnimationTime = 0.3;
    hitBlinkSpeed = 0.15;
    
    //game shit
    freezeTimer = 0;
    freezeSpeedReduction = 0.25;    //THIS IS BEING OVERWRITTEN EVERY FRAME BY CONTROL PANEL
    
    string typeXMLNames[5] = {"DUMB", "STRONG", "FAST", "WAVE", "IGNORE"};
    
    startingHealth = panel->getValueF(typeXMLNames[type]+"_FOE_HP");
    speed = panel->getValueF(typeXMLNames[type]+"_FOE_SPEED");
    hitCircleSize = panel->getValueF("FOE_HIT_CIRCLE");
    
    waveDist = panel->getValueF("WAVE_FOE_WAVE_DIST");
    wavePeriod = panel->getValueF("WAVE_FOE_WAVE_PERIOD");
    ignoreFoeSpeedIncrease = panel->getValueF("IGNORE_FOE_SPEED_INCREASE");
    
    health = startingHealth;
    
    minDistFromNodeToAdvance = speed / 20;
    
    if (type == FOE_STRONG){
        hitCircleSize *= 1.4;
    }
    
    
    //walking to the first node
    nextNodeID = 0;
    findNextNode(true);
    
    displayAngle = curAngle;
    
    //some flags
    reachedTheEnd = false;
    doingSpawnAnim = false;
    killMe = false;
    ignoringPath = false;
}

void TDFoe::setPos(ofVec2f _pos, int _nextNode){
    
    nextNodeID = _nextNode - 1;
    
    basePos = _pos;
    pos = basePos;
    
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
    if (!reachedTheEnd && !doingSpawnAnim){
        
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
    
    float dispAngleHigh = displayAngle + TWO_PI;
    float dispAngleLow = displayAngle - TWO_PI;
    if ( abs(dispAngleHigh-curAngle) < abs(dispAngleLow-curAngle) && abs(dispAngleHigh-curAngle) < abs(displayAngle-curAngle)){
        displayAngle = dispAngleHigh;
    }
    else if ( abs(dispAngleLow-curAngle) < abs(dispAngleHigh-curAngle) && abs(dispAngleLow-curAngle) < abs(displayAngle-curAngle)){
        displayAngle = dispAngleLow;
    }
    
    displayAngle = angleXeno * displayAngle + (1-angleXeno) * curAngle;
    
    
    //animation
    animTimer += deltaTime;
    if (animTimer >= frameTime){
        animTimer -= frameTime;
        curFrame++;
        if (curFrame >= anims->walkCycleLength[type]){
            curFrame = 0;
        }
        
        if (doingSpawnAnim){
            curSpawnFrame++;
            if (curSpawnFrame >= anims->dumbFoeSpawnCycleLength){
                doingSpawnAnim = false;
            }
        }
    }
    
    hitAnimationTimer -= deltaTime;
    
}

void TDFoe::draw(float alphaPrc){
    if (delayTimer > 0){
        return;
    }
    
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate( ofRadToDeg(displayAngle) );
    
    //sprite
    ofSetColor(255, 255*alphaPrc);
    if (freezeTimer > 0){
        //tint blue when frozen
        ofSetColor(100,100,255, 255*alphaPrc);
    }
    
    if (hitAnimationTimer > 0){
        if (fmod(ofGetElapsedTimef(), hitBlinkSpeed) < hitBlinkSpeed/2){
            ofSetColor(235,100,100, 255*alphaPrc);
        }
    }
    
    //cout<<"type :"<<type<<"   frame:"<<curFrame<<endl;
    ofImage * thisPic = &anims->walkCycles[type][curFrame];
    if (type == FOE_IGNORE && ignoringPath){
        thisPic = &anims->ignoreFoeAltWalkCycle[curFrame% anims->ignoreFoeAltWalkCycleLength];
    }
    if (doingSpawnAnim){
        thisPic = &anims->dumbFoeSpawnCycle[curSpawnFrame];
    }
    thisPic->draw(-thisPic->getWidth()/2, -thisPic->getHeight()/2);
    
    //hit circle
//    ofSetColor(200, 0, 0, 100*alphaPrc);
//    ofCircle(0, 0, hitCircleSize);
    
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
    if (delayTimer > 0){
        return;
    }
    
    health -= dmg;
    if (health <= 0){
        killMe = true;
    }
    
    //for the ignore type, the first time they take damage, they shoot towards the goal
    if (health < startingHealth && type == FOE_IGNORE){
        speed *= ignoreFoeSpeedIncrease;
        if (nextNodeID < path->size()-2){
            nextNodeID = path->size()-2;
            ignoringPath = true;
            findNextNode(false);
        }
    }
    
    hitAnimationTimer = hitAnimationTime;
}

void TDFoe::freeze(float time){
    freezeTimer = time;
}

void TDFoe::setSpawnAnimation(){
    doingSpawnAnim = true;
    curSpawnFrame = 0;
}