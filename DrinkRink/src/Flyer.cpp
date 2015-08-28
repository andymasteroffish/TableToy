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
    bonusTrargetForceIncreasePerFrame = 0.001;
    curAngle = 0;
    
    fric = 0.95;
    
    fieldForceAdjust = 0.1;
    
    distToTargetToCount = 15;
    
    repelRange = 30;
    repelForce = 2;
    
    pos.set( ofRandom(field->gameWidth), ofRandom(field->gameHeight) );
    
    isFree = true;
    targetTower = NULL;
    needsTower = false;
    orbitDist = ofRandom(70,120);
    
    maxTimeToOrbit = 40;
    maxTimeToBeFree = 10;
    
    orbitTimer = 3; //this is dumb
    
    targetPos.set( pos.x, pos.y);
    resetTarget = true;
    
}

void Flyer::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    orbitTimer -= deltaTime;
    
    if (orbitTimer < 0){
        if (isFree){
            needsTower = true;
        }else{
            setFree();
        }
    }
    
    
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
    
    //are we clsoe enough to the target?
    if (resetTarget || ofDistSquared(pos.x, pos.y, targetPos.x, targetPos.y) < powf(distToTargetToCount, 2)){
        
        if (isFree){
            targetPos.set( ofRandom(field->gameWidth), ofRandom(field->gameHeight));
        }else{
            ofVec2f towerPos = targetTower->pos;
            targetPos = towerPos;
            
            
            //get the line from the tower
            ofVec2f fromTower = pos-towerPos;
            fromTower.normalize();
            fromTower.rotate(15*orbitDir);
            
            targetPos = towerPos + fromTower * orbitDist;
        }
        
        bonusTargetForce = 0;
        
        resetTarget = false;
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
//    if (isFree){
//        ofNoFill();
//    }else{
//        ofFill();
//    }
//    
//    ofCircle(pos.x, pos.y, repelRange);
//    
//    ofSetColor(0);
//    ofDrawBitmapString(ofToString(orbitTimer), pos.x, pos.y);
    
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


void Flyer::setFree(){
    isFree = true;
    targetTower = NULL;
    orbitTimer = ofRandom(1, maxTimeToBeFree);
    resetTarget = true;
}

void Flyer::setTower(Tower *newTarget){
    isFree = false;
    needsTower = false;
    targetTower = newTarget;
    orbitTimer = ofRandom(1, maxTimeToOrbit);
    orbitDir = 1;//ofRandom(100) > 50 ? 1 : -1;
    resetTarget = true;
}



