//
//  TowerPopper.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerPopper.h"

void TowerPopper::customSetup(){
    
    pullRange = 300;
    pushRange = 200;
    
    pullStrength  = -4;
    pushStrength = 40;
    
    pullTime = 5;
    pushTime = 0.4;
    
    curRange = pullRange;
    
    curRingRange = pullRange;
    targetRingRange = curRingRange;
    
    
    
    debugColor.setHex(0xDEDE33);
    particleType = PARTICLE_SPORT;
    
}

void TowerPopper::setRelativeRangeAndStrength(float rangePrc, float strengthPrc){
    
    rangeMod = rangePrc;
    strengthMod = strengthPrc;
    
}

void TowerPopper::customUpdate(){
    
    timer += deltaTime;
    
    float curStrength = pullStrength * strengthMod;
    curRange = pullRange * rangeMod;
    
    if (timer > pullTime){
        curStrength = pushStrength * strengthMod;
        curRange = pushRange * rangeMod;
        
        if (timer > pullTime+pushTime){
            timer = 0;
        }
    }
    
    if (curRange != range){
        range = curRange;
        calculateFieldRange();
    }
    
    addOutwardCircle(curStrength, fieldRange);
    
    //keep a small outward forc eint hec enter at all times
    addOutwardCircle(curStrength, 2);
    
    //xeno the ring
    float xeno = 0.9;
    
    if (timer < pullTime){
        float prc = 1.0 - (timer / pullTime);
        targetRingRange = pullRange * rangeMod * prc;
    }else{
        targetRingRange = pullRange * rangeMod * 1.2;
    }
    
    curRingRange = xeno * curRingRange + (1-xeno) * targetRingRange;
}


void TowerPopper::addOutwardCircle(float strength, float thisRange){
    Bounds bounds = field->getFieldBounds(fieldPos, thisRange);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(fieldPos.x, fieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < thisRange){
                float prct = 1.0f - (distance / thisRange);
                
                ofVec2f dif;
                dif.x = (x - fieldPos.x);
                dif.y = (y - fieldPos.y);
                dif.normalize();
                
                field->field[x][y].vel += dif * strength * prct;
                field->field[x][y].addPotentialParticleType(particleType, particleTypeWeight);
            }
        }
    }
}

void TowerPopper::customDraw(float alphaPrc){
    drawSportsTower(alphaPrc);
    
    ofSetColor(debugColor.r, debugColor.g, debugColor.b, 120*alphaPrc);
    
    float noiseSpeed = 4;
    float noiseRange = 15;
    
    ofNoFill();
    ofSetLineWidth(5);
    ofCircle(pos.x, pos.y, curRingRange + ofNoise(ofGetElapsedTimef()+noiseSpeed, uniqueID) * noiseRange);
    ofCircle(pos.x, pos.y, curRingRange + ofNoise(ofGetElapsedTimef()+noiseSpeed, 100, uniqueID) * noiseRange);
    
//    ofSetLineWidth(10);
//    float prc = timer/timeForPulse;
//    float prcCurved = powf(prc, 2);
//    ofSetColor( 185, 129, 204, 180.0 * alphaPrc * (1-prcCurved));
//    ofNoFill();
//    
//    float dist = range*prc;
//    ofCircle(pos.x, pos.y, dist);
//    float otherDist = range*prc + sin(ofGetElapsedTimef()*20) * 20;
//    ofCircle(pos.x, pos.y, otherDist);
    
    //put it back
    ofSetLineWidth(1);
    
}



