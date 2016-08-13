//
//  TowerFlow.h
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#ifndef __emptyExample__CupFlow__
#define __emptyExample__CupFlow__

#include "ofMain.h"
#include "Tower.h"

class TowerFlow : public Tower{
public:
    
    void customSetup();
    void setRelativeRangeAndStrength(float rangePrc, float strengthPrc);
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    void addFlowCircle(float strength, float thisAngle, float spread);
    
    float baseRange;
    float strengthMod;
    
    ofVec2f ballPos;
    ofVec2f ballVel;
    float ballTimer;
    float ballTime;
    
};

#endif /* defined(__emptyExample__CupFlow__) */
