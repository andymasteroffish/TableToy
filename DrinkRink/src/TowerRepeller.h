//
//  CupRepeller.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

//This is basically a test. Very simple implimentation just pushing away from center

#ifndef __emptyExample__CupRepeller__
#define __emptyExample__CupRepeller__

#include "ofMain.h"
#include "Tower.h"

class TowerRepeller : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void addOutwardCircle(float strength);
    
    float repelStrength;
    
};

#endif /* defined(__emptyExample__CupRepeller__) */
