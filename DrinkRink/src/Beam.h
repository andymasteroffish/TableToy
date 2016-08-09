//
//  Beam.h
//  DrinkRink
//
//  Created by Anthony on 6/28/16.
//
//

#pragma once
#include "ofMain.h"

class Beam {
public:
    ofVec2f pos;
    float beamWidth = 20;
    float beamLength = 3000;
    
    void customSetup();
    void customDraw();
    void customUpdate();
    void calculateBeam();
    
};