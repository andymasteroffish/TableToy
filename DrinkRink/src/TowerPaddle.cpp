//
//  TowerPaddlecpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerPaddle.h"

void TowerPaddle::customSetup(){
    
    range = 300;
    
    debugColor.setHex(0x1010E6);
    particleType = PARTICLE_SPORT;
    
}

void TowerPaddle::customUpdate(){
    
    points.clear();
    
    float thisFieldRange = 3;
    float thisStrength = 3;
    
    float stepDist = 15;
    int numSteps = range/stepDist;
    ofVec2f step;
    step.x = cos(curAngle) * stepDist;
    step.y = sin(curAngle) * stepDist;
    
    cout<<"num steps "<<numSteps<<endl;
    cout<<"step.x "<<step.x<<endl;
    
    for (int i = 4; i<numSteps; i++){
        float thisX = pos.x + step.x * i;
        float thisY = pos.y + step.y * i;
        
        ofVec2f thisPos(thisX, thisY);
        points.push_back(thisPos);
        addOutwardCircle(thisX, thisY, thisFieldRange, thisStrength);
    }
    
}


void TowerPaddle::addOutwardCircle(float xPos, float yPos, float thisFieldRange, float strength){
    GridPos thisFieldPos = field->getInternalPointFromExternal(xPos, yPos);
    
    Bounds bounds = field->getFieldBounds(thisFieldPos, fieldRange);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(thisFieldPos.x, thisFieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < thisFieldRange){
                float prct = 1.0f - (distance / thisFieldRange);
                
                ofVec2f dif;
                dif.x = (x - thisFieldPos.x);
                dif.y = (y - thisFieldPos.y);
                dif.normalize();
                
                field->field[x][y].vel += dif * strength * prct;
                field->field[x][y].addPotentialParticleType(particleType, particleTypeWeight);
            }
        }
    }
}

void TowerPaddle::customDraw(float alphaPrc){
    drawSportsTower(alphaPrc);
    
    //ofSetColor(255,0,0);
    for (int i=0; i<points.size(); i++){
        
        float drawSize = 10 + sin(ofGetElapsedTimef()*2.5+i*0.5) * 3;
        
        ofVec2f offset;
        offset.x = -1 + (ofNoise(i, uniqueID, ofGetElapsedTimef())*2) * 3;
        offset.y = -1 + (ofNoise(i+100, uniqueID, ofGetElapsedTimef())*2) * 3;
        
        ofCircle(points[i].x+offset.x, points[i].y+offset.y, drawSize);
    }
}



