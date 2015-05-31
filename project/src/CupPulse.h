//
//  PulseCup.h
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#ifndef __emptyExample__PulseCup__
#define __emptyExample__PulseCup__

#include "ofMain.h"
#include "Cup.h"

class CupPulse : public Cup{
public:
    
    void customSetup();
    void customUpdate();
    
    float timer;
    float timeBetweenPulses;
    float timeForPulse;
    
    float strength;
    float pulseWidth;
    
};

#endif /* defined(__emptyExample__PulseCup__) */
