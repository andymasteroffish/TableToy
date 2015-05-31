//
//  CupFlow.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "CupFlow.h"


void CupFlow::customSetup(){
    range = 150;
    debugColor.set(138,130,21, 220);
}

void CupFlow::customUpdate(){
    float strength = 1.5;
    float spread = 1.5;// abs(cos(ofGetElapsedTimef())) * 4;
    field->addFlowCircle(pos.x, pos.y, range, strength, -angle, spread);
}