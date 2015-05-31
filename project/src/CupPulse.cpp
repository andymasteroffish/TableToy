//
//  PulseCup.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "CupPulse.h"


void CupPulse::customSetup(){
    range = 200;
    debugColor.set(222,35,222, 220);
    
    strength = 0.75;
    pulseWidth = 15;
    
    timer = 0;
    timeBetweenPulses = 2;
    timeForPulse = 1;
    
    
}

void CupPulse::customUpdate(){
    
    timer += deltaTime;
    
    if (timer > timeBetweenPulses + timeForPulse){
        timer = 0;
    }
    
    if (timer < timeForPulse) {
        
        float prc = timer/timeForPulse;
        
        float pulseDist = range*prc;
        field->addPulseCircle(pos.x, pos.y, range, strength, pulseDist, pulseWidth);
    }
}