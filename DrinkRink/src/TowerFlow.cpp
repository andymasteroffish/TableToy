//
//  TowerFlow/cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/31/15.
//
//

#include "TowerFlow.h"


void TowerFlow::customSetup(){
    baseRange = 400;
    range = baseRange;
    debugColor.setHex(0xdfa320);
    particleType = PARTICLE_SPORT;
    
    ballTime = 0.5;
}

void TowerFlow::setRelativeRangeAndStrength(float rangePrc, float strengthPrc){
    float oldRange = range;
    
    range = baseRange * rangePrc;
    strengthMod = strengthPrc;
    
    if (oldRange != range){
        calculateFieldRange();
    }
}

void TowerFlow::customUpdate(){
    float strength = 3;//2.5;
    float spread = 2;//1.5;// abs(cos(ofGetElapsedTimef())) * 4;
    addFlowCircle(strength, -curAngle, spread);
    
    ballTimer -= deltaTime;
    if (ballTimer < -0.2){
        
        ballPos = pos;
        
        float force = 600;
        
        float thisAngle = curAngle + ofRandom(-PI/8, PI/8);
        ballVel.x = cos(thisAngle) * force;
        ballVel.y = sin(thisAngle) * force;
        
        ballTimer = ballTime + ofRandom(0.1);
        
    }
    
    ballPos += ballVel * deltaTime;
}

void TowerFlow::customDraw(float alphaPrc){
    drawSportsTower(alphaPrc, false);
    
    if (ballTimer >= 0){
        ofColor ballCol = debugColor;
        ballCol.a = 200 * alphaPrc;
        float ballFadeTime = 0.2;
        if (ballTimer < ballFadeTime){
            float prc = ballTimer / ballFadeTime;
            ballCol.a *= prc;
        }
        ofSetColor(ballCol);
        ofCircle(ballPos.x, ballPos.y, 30);
    }
    
}

void TowerFlow::addFlowCircle(float strength, float thisAngle, float spread){
    Bounds bounds = field->getFieldBounds(fieldPos, fieldRange);
    
    //cout<<"angle "<<angle<<endl;
    
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
                        }else{
                            forceToAdd *= 0;    //this is hacky
                        }
                        
                        field->field[x][y].vel += forceToAdd;
                        field->field[x][y].addPotentialParticleType(particleType, particleTypeWeight);
                    }
                }
                
            }
            
            
        }
    }
}