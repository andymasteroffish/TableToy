//
//  CupFlow.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "CupFlow.h"


void CupFlow::customSetup(){
    range = 200;
}

void CupFlow::customUpdate(){
    field->addFlowCircle(pos.x, pos.y, range, 4, angle + ofGetElapsedTimef()*0.75);
}