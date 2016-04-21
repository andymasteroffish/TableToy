//
//  TowerRock.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#ifndef __emptyExample__CupRock__
#define __emptyExample__CupRock__

#include "ofMain.h"
#include "Tower.h"

class TowerRock : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    void addOutwardSemiCircle(float strength, bool onLeft);
    
};

#endif /* defined(__emptyExample__CupRock__) */
