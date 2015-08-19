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
    void customUpdate();
    
    void addFlowCircle(float strength, float thisAngle, float spread);
    
};

#endif /* defined(__emptyExample__CupFlow__) */
