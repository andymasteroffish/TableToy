//
//  TowerRepeller.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerRepeller.h"

void TowerRepeller::customSetup(){
    
    range = 200;
    repelStrength = 6;
    
    debugColor.setHex(0x49df20);
    particleType = PARTICLE_SPORT;
    
}

void TowerRepeller::customUpdate(){
    
    addOutwardCircle(repelStrength);
}


void TowerRepeller::addOutwardCircle(float strength){
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
                
                field->field[x][y].vel += dif * strength * prct;
                field->field[x][y].addPotentialParticleType(particleType, particleTypeWeight);
            }
        }
    }
}

void TowerRepeller::customDraw(float alphaPrc){
    drawSportsTower(alphaPrc);
}



