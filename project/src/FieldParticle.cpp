//
//  FieldParticle.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "FieldParticle.h"


FieldParticle::FieldParticle(float x, float y){
    setup(x,y);
}

void FieldParticle::setup(float x, float y){
    killTime = 3;
    killVel = 0.01;
    
    velToStartFading = 1;
    
    pos.set(x,y);
    vel.set(0,0);
    fric = 0.8;
    col.set( ofRandom(255), ofRandom(255), ofRandom(255) );
    
    timer = 0;
    
    killFlag = false;
    
    setAlpha();

}

void FieldParticle::update(float deltaTime, VectorField * field){
    vel += field->getForceFromPos(pos) * 0.5;
    vel *= fric;
    pos += vel;
    
    timer += deltaTime;
    if (timer > killTime || ( abs(vel.x) < killVel && abs(vel.y) < killVel) ){
        killFlag = true;
    }
    
    setAlpha();
}

void FieldParticle::draw(){
    
    ofSetColor(col);
    ofCircle(pos, 2);
    
}

void FieldParticle::setAlpha(){
    float maxVel = MAX( abs(vel.x), abs(vel.y) );
    if (maxVel < velToStartFading){
        float prct = maxVel/velToStartFading;
        col.a = prct * 255;
    }else{
        col.a = 255;
    }

    //also start to fade if it is running out of time
    float timeLeft = killTime-timer;
    float timeToFade = 0.4;
    if ( timeLeft < timeToFade ){
        float newAlpha = (timeLeft/timeToFade) * 255;
        col.a = MIN(newAlpha, col.a);
    }
    
}
