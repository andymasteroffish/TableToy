//
//  CupRock.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "CupRock.h"

void CupRock::customUpdate(){
    float leftSideStrength = 3;
    float rightSideStrength = 4.5;
    
    
    field->addOutwardSemiCircle(pos.x, pos.y, range, rightSideStrength, false);
    field->addOutwardSemiCircle(pos.x, pos.y, range, leftSideStrength, true);
}