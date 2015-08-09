//
//  Goal.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "Goal.h"


void Goal::setup(bool _isLeft, VectorField * _field){
    
    field = _field;
    
    isLeft = _isLeft;
    
    if (isLeft){
        baseCol = ofColor::red;
    }else{
        baseCol = ofColor::blue;
    }
    
    //range in pixels
    closeRange = 50;
    farRange = 160;
    //range in field units
    closeFieldRange = (float)( (closeRange / (float)field->externalWidth) * field->fieldWidth);
    farFieldRange = (float)( (farRange / (float)field->externalWidth) * field->fieldWidth);
    
    //strength in field units
    closeFieldStrength = 1.5;
    farFieldStrength = 0.5;
    
    //killing
    killRange = closeRange / 2;
    
    //position this thing
    pos.y = ofGetHeight()/2;
    pos.x = isLeft ? 70 : ofGetWidth()-70;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
}

void Goal::reset(){
    score = 0;
}

void Goal::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    addInwardCircle(closeFieldStrength, closeFieldRange);
    addInwardCircle(farFieldStrength, farFieldRange);
}

void Goal::draw(float alphaPrc){
    
    ofSetColor(baseCol, 100*alphaPrc);
    ofCircle(pos.x, pos.y, farRange);
    
    ofSetColor(baseCol, 200*alphaPrc);
    ofCircle(pos.x, pos.y, closeRange);
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(score), pos.x, pos.y);
    
}


bool Goal::checkIsBallDead(Ball * ball){
    
    float distSq = ofDistSquared(ball->pos.x, ball->pos.y, pos.x, pos.y);
    
    if (distSq < powf(killRange,2)){
        markScore();
        return true;
    }
    
    return false;
    
}

void Goal::markScore(){
    score++;
}


void Goal::addInwardCircle(float strength, float range){
    Bounds bounds = field->getFieldBounds(fieldPos, range);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(fieldPos.x, fieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < range){
                float prct = 1.0f - (distance / range);
                
                ofVec2f dif;
                dif.x = (x - fieldPos.x);
                dif.y = (y - fieldPos.y);
                dif.normalize();
                
                field->field[x][y] -= dif * strength * prct;
            }
        }
    }
}