//
//  TowerPrism.h
//  DrinkRink
//
//  Created by Anthony on 6/28/16.
//
//

#pragma once

#include "ofMain.h"
#include "Tower.h"
#include "Beam.h"

class TowerPrism : public Tower{
public:
    
    int lightCount = 0;
    bool isSource, isLit;
    Beam beam;
    
    void customSetup();
    void customUpdate();
    void customDraw(float alphaPrc);
    
        
};