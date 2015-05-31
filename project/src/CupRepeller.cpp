//
//  CupRepeller.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "CupRepeller.h"

void CupRepeller::customSetup(){
    range = 100;
    debugColor.set(0, 230, 80, 220);
}

void CupRepeller::customUpdate(){
    float testStrength = 4;
    
    addOutwardCircle(testStrength);
}

void CupRepeller::addOutwardCircle(float strength){
    Bounds bounds = field->getFieldBounds(fieldPos, fieldRange);
    
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

