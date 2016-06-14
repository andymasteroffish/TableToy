//
//  TowerRock.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "TowerRock.h"

void TowerRock::customSetup(){
    range = 230;
    
    debugColor.setHex(0xabb1a9);
}

void TowerRock::customUpdate(){
    float leftSideStrength = 5.5;//4.5;
    float rightSideStrength = 4.25;
    
    addOutwardSemiCircle(rightSideStrength, false);
    addOutwardSemiCircle(leftSideStrength, true);
}

void TowerRock::customDraw(float alphaPrc){
    
    float drawSizeMin = 10;
    float drawSizeMax = 80;
    
    float drawRange = range *0.5;
    
    float alphaMin = 0;
    float alphaMax = 200;
    
    float sizeSpeed = 1;
    float moveSpeed = 1;
    float alphaSpeed = 1;
    float rotSpeed = 10;
    
    ofPushMatrix();
    
    ofTranslate(pos.x, pos.y);
    ofRotate(randVal + ofGetElapsedTimef() * 40);
    
    for (int i=0; i<15; i++){
        
        ofSetCircleResolution( (i%3)+3 );
        
        float thisSize = ofMap(ofNoise(ofGetElapsedTimef()*sizeSpeed, i, uniqueID+0), 0, 1, drawSizeMin, drawSizeMax);
        float thisX = (-1 + ofNoise(ofGetElapsedTimef()*moveSpeed, i, uniqueID+10)*2) * drawRange;
        float thisY = (-1 + ofNoise(ofGetElapsedTimef()*moveSpeed, i, uniqueID+20)*2) * drawRange;
        
        float thisAlpha = ofMap( ofNoise(ofGetElapsedTimef()*alphaSpeed, i, uniqueID+30), 0, 1, alphaMin, alphaMax);
        
        float thisAngle = ofNoise(ofGetElapsedTimef()*rotSpeed, i, uniqueID+40) * TWO_PI*2;
        
        ofSetColor(0, thisAlpha);
        
        ofPushMatrix();
        ofTranslate(thisX, thisY);
        ofRotate(thisAngle);
        
        ofCircle(0, 0, thisSize);
        
        ofPopMatrix();
        
    }
    
    ofPopMatrix();
    
    //put circles back to default
    ofSetCircleResolution(DEFAULT_CIRCLE_RES);
    
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
                
                field->field[x][y].vel += dif * strength * prct;
            }
        }
    }
}