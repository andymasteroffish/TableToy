//
//  TowerPulse.h
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#ifndef __emptyExample__PulseCup__
#define __emptyExample__PulseCup__

#include "ofMain.h"
#include "Tower.h"

class TowerPulse : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    void addPulseCircle(float strength, float externalPulseDist, float externalPulseSize);
    
    float timer;
    float timeBetweenPulses;
    float timeForPulse;
    
    float strength;
    float pulseWidth;
    
    
    
};

#endif /* defined(__emptyExample__PulseCup__) */
