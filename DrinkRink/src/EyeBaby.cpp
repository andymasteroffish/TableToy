//
//  EyeBaby.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/2/18.
//
//

#include "EyeBaby.hpp"

void EyeBaby::setup(float x, float y){
    pos.set(x,y);
    
    preferredAngle = -PI/4;
    curAngle = preferredAngle;
    
    moveSpeed = 60;
    turnSpeed = PI * 1.5;
    turnSpeedSlow = turnSpeed * 0.25;
    
    feelerDist = 40;
    feelerSpread = PI/5;
    feelersPos.resize(2);
    feelersBeingTouched.resize(2);
    
    update(0);
    
    
}


void EyeBaby::checkFeelers(float otherX, float otherY, float otherSize){
    for (int i=0; i<feelersPos.size(); i++){
        if (feelersBeingTouched[i] == false){
            if ( ofDistSquared(feelersPos[i].x, feelersPos[i].y, otherX, otherY) < otherSize){
                feelersBeingTouched[i] = true;
                //cout<<"touch "<<i<<endl;
            }
        }
    }
    
}

//update must be called after checkFeelers
void EyeBaby::update(float deltaTime){
    
    //check if we should be turning
    if (feelersBeingTouched[0]){
        curAngle -= turnSpeed * deltaTime;
    }
    else if (feelersBeingTouched[1]){
        curAngle += turnSpeed * deltaTime;
    }
    else{
        float slowSpeedThisFrame = turnSpeedSlow * deltaTime;
        if (curAngle > preferredAngle){
            curAngle -= slowSpeedThisFrame;
        }
        if (curAngle < preferredAngle){
            curAngle += slowSpeedThisFrame;
        }
        if ( abs(curAngle-preferredAngle) < slowSpeedThisFrame*2){
            curAngle = preferredAngle;
        }
    }
    
    //move
    pos.x += cos(curAngle) * moveSpeed * deltaTime;
    pos.y += sin(curAngle) * moveSpeed * deltaTime;
    
    
    //set feeler positions
    feelersPos[0].x = pos.x + cos(curAngle + feelerSpread) * feelerDist;
    feelersPos[0].y = pos.y + sin(curAngle + feelerSpread) * feelerDist;
    
    feelersPos[1].x = pos.x + cos(curAngle - feelerSpread) * feelerDist;
    feelersPos[1].y = pos.y + sin(curAngle - feelerSpread) * feelerDist;
    
    //turn things off for next frame
    for (int i=0; i<feelersBeingTouched.size(); i++){
        feelersBeingTouched[i] = false;
    }
    
}



void EyeBaby::debugDraw(){
    ofFill();
    ofSetColor(0, 0, 255);
    ofCircle(pos.x, pos.y, 20);
    for (int i=0; i<feelersPos.size(); i++){
        if (feelersBeingTouched[i]){
            ofSetColor(0, 255, 0);
        }else{
            ofSetColor(0, 0, 255);
        }
        ofCircle(feelersPos[i].x, feelersPos[i].y, 10);
    }
    
}