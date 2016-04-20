//
//  TowerPulse.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "TowerPulse.h"


void TowerPulse::customSetup(){
    range = 400;
    
    strength = 1.5;//0.8;
    pulseWidth = 20;
    
    timer = 0;
    timeBetweenPulses = 2;
    timeForPulse = 1;
    
    pulseStrengthCurve = 0.5;
    
    debugColor.setHex(0xdf20c6);
    particleType = PARTICLE_SPORT;
}

void TowerPulse::customUpdate(){
    
    timer += deltaTime;
    
    if (timer > timeBetweenPulses + timeForPulse){
        timer = 0;
    }
    
    if (timer < timeForPulse) {
        
        float prc = timer/timeForPulse;
        
        float pulseDist = range*prc;
        addPulseCircle(strength, pulseDist, pulseWidth);
        //field->addPulseCircle(pos.x, pos.y, range, strength, pulseDist, pulseWidth);
    }
}


void TowerPulse::customDraw(float alphaPrc){
    float prc = timer/timeForPulse;
    float prcCurved = powf(prc, 2);
    ofSetColor( 185, 129, 204, 255.0 * alphaPrc * (1-prcCurved));
    ofNoFill();
    
    float dist = range*prc;
    ofCircle(pos.x, pos.y, dist);
    float otherDist = range*prc + sin(ofGetElapsedTimef()*20) * 20;
    ofCircle(pos.x, pos.y, otherDist);
}


void TowerPulse::addPulseCircle(float strength, float externalPulseDist, float externalPulseSize){
    Bounds bounds = field->getFieldBounds(fieldPos, fieldRange);
    
    float fieldPulseDistPrc = externalPulseDist / (float)field->gameWidth;
    float fieldPulseDist = (float) (fieldPulseDistPrc * field->fieldWidth);
    
    float fieldPulseSizePrc = externalPulseSize / (float)field->gameWidth;
    float fieldPulseSize = (float) (fieldPulseSizePrc * field->fieldWidth);
    
    float maxFieldDist = fieldPulseDist + fieldPulseSize;
    float minFieldDist = fieldPulseDist - fieldPulseSize;
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance =  (float)sqrt( (fieldPos.x-x) * (fieldPos.x-x) + (fieldPos.y-y) * (fieldPos.y-y) );
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < maxFieldDist && distance > minFieldDist){
                float prct = 1;//1.0f - (distance / fieldRange);
                prct = powf(prct, pulseStrengthCurve);
                
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