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
    bool isSource = false;
    float startWidth = 100;
    float endWidth = 0;
    float startX = 0;
    float startY = 0;
    float bLength = 3000;
    float endX = 0;
    float endY = 0;
    float rotation = 0;
    
    void customSetup();
    void customDraw();
    void customUpdate();
    void calculateBeam();
    
};