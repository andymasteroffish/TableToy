//
//  TowerPopper.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//


#ifndef __emptyExample__TowerPopper__
#define __emptyExample__TowerPopper__

#include "ofMain.h"
#include "Tower.h"

class TowerPopper : public Tower{
public:
    
    void customSetup();
    void setRelativeRangeAndStrength(float rangePrc, float strengthPrc);
    
    void customUpdate();
    
    
    void customDraw(float alphaPrc);
    
    
    void addOutwardCircle(float strength, float thisRange);
    
    float pullStrength;
    float pushStrength;
    
    float curRange;
    float pullRange, pushRange;
    
    float rangeMod;
    float strengthMod;
    
    float pullTime;
    float pushTime;
    float timer;
    
    float targetRingRange, curRingRange;
    
    
};

#endif /* defined(__emptyExample__TowerPopper__) */
