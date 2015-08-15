//
//  TowerRock.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerRock.h"

void TowerRock::customSetup(){
    range = 90;
    
    debugColor.setHex(0xabb1a9);
}

void TowerRock::customUpdate(){
    float leftSideStrength = 3;
    float rightSideStrength = 3.5;
    
    addOutwardSemiCircle(rightSideStrength, false);
    addOutwardSemiCircle(leftSideStrength, true);
}

void TowerRock::addOutwardSemiCircle(float strength, bool onLeft){
    Bounds bounds = field->getFieldBounds(fieldPos, fieldRange);
    
    if (onLeft){
        bounds.bottomRight.x = fieldPos.x;
    }else{
        bounds.topLeft.x = fieldPos.x;
    }
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(fieldPos.x, fieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < fieldRange){
                float prct = 1.0f - (distance / fieldRange);
                
                ofVec2f dif;
                dif.x = (x - fieldPos.x);
                dif.y = (y - fieldPos.y);
                dif.normalize();
                
                field->field[x][y] += dif * strength * prct;
            }
        }
    }
}