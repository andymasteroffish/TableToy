//
//  Flyer.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "Flyer.h"


void Flyer::setup(VectorField * _field){
    
    field = _field;

    speed = 0.1;
    bonusTargetForce = 0;
    bonusTrargetForceIncreasePerFrame = 0.0003;
    curAngle = 0;
    
    fric = 0.95;
    
    fieldForceAdjust = 0.3;
    
    distToTargetToCount = 2;
    
    repelRange = 30;
    repelForce = 2;
    
    pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()) );
    
    isFree = true;
    targetTower = NULL;
    
    targetPos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    
}

void Flyer::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    
    //friction
    vel *= fric;
    
    //move towards target
    ofVec2f vecToTarget =  targetPos - pos;
    vecToTarget.normalize();
    vel += vecToTarget * (speed+bonusTargetForce);
    
    //get field force
    vel += field->getForceFromPos(pos) * fieldForceAdjust;
    
    //actually adjust position
    pos += vel;
    
    if ( ofDistSquared(pos.x, pos.y, targetPos.x, targetPos.y) < powf(distToTargetToCount, 2)){
        targetPos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        bonusTargetForce = 0;
        //cout<<"ding dong "<<targetPos.x<<" , "<<targetPos.y<<endl;
    }
    
    bonusTargetForce += bonusTrargetForceIncreasePerFrame;
    
    
    
    curAngle = atan2(vel.y, vel.x);
    
    //cout<<"pos "<<pos.x<<" , "<<pos.y<<endl;
    //cout<<"vel "<<vel.x<<" , "<<vel.y<<endl;
    
}

void Flyer::draw(float alphaPrc){
    
    ofPushMatrix();
    
    ofTranslate(pos.x, pos.y);
    
    ofRotate( ofRadToDeg(curAngle) );
    
    ofSetColor(255, 10, 10, 255*alphaPrc);
    
    int testSize = 10;
    ofRect(-testSize/2, -testSize/2, testSize, testSize);
    
    ofPopMatrix();
    
    //testing
//    ofCircle(targetPos.x,targetPos.y,5);
//    ofSetColor(255, 10, 10, 100*alphaPrc);
//    ofLine(targetPos.x, targetPos.y, pos.x, pos.y);
//    
//    ofCircle(pos.x, pos.y, repelRange);
    
}


void Flyer::addRepulsionForce(Flyer * other){
    ofVec2f diff = pos - other->pos;
    
    if (diff.lengthSquared() < repelRange*repelRange){
        float prc = 1 - (diff.length() / repelRange);
        diff.normalize();
        
        ofVec2f forceToAdd = diff * prc * repelForce;
        //cout<<"repel "<<diff.x<<endl;
        //cout<<"kick "<<forceToAdd.x<<" , "<<forceToAdd.y<<endl;
        
        other->vel -= diff * prc * repelForce;
    }
}



