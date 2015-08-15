//
//  TowerFlow/cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "TowerFlow.h"


void TowerFlow::customSetup(){
    range = 150;
    debugColor.setHex(0xdfa320);
}

void TowerFlow::customUpdate(){
    float strength = 1.5;
    float spread = 1.5;// abs(cos(ofGetElapsedTimef())) * 4;
    addFlowCircle(strength, -angle, spread);
}


void TowerFlow::addFlowCircle(float strength, float thisAngle, float spread){
    Bounds bounds = field->getFieldBounds(fieldPos, fieldRange);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance =  (float)sqrt( (fieldPos.x-x) * (fieldPos.x-x) +
                                          (fieldPos.y-y) * (fieldPos.y-y));
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < fieldRange){
                
                //get the relative positions
                float relX = fieldPos.x - x;
                float relY = fieldPos.y - y;
                
                float angleToCenter = atan2( relY, relX );
                float distToCenter = sqrt( relX*relX + relY*relY );
                
                
                //adjust the position (for calculations) based on the angle offset
                relX = cos(angleToCenter + thisAngle) * distToCenter;
                relY = sin(angleToCenter + thisAngle) * distToCenter;
                
                if ( relY < powf((relX/fieldRange),2.0f) * fieldRange + spread ){
                    if ( relY > -powf((relX/fieldRange),2.0f) * fieldRange - spread ){
                        float strengthPrct = 1.0f - (distance / fieldRange);
                        
                        ofVec2f forceToAdd;
                        
                        forceToAdd.x += cos(angleToCenter) * strength * strengthPrct;
                        forceToAdd.y += sin(angleToCenter) * strength * strengthPrct;
                        
                        if (relX < 0){
                            forceToAdd *= -1;
                        }
                        
                        field->field[x][y] += forceToAdd;
                    }
                }
                
            }
            
            
        }
    }
}