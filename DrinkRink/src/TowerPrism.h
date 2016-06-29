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

class TowerPrism : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void customDraw(float alphaPrc);
        
};