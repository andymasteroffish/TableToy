//
//  Ball.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Ball.h"

/*
Ball::Ball(){
    setup(false);
}
 */

Ball::Ball(bool spawnOnTop, int _gameWidth, int _gameHeight, ofColor _col){
    setup(spawnOnTop, _gameWidth, _gameHeight, _col);
}

void Ball::setup(bool spawnOnTop, int _gameWidth, int _gameHeight, ofColor _col){
    
    friction = 0.995;
    
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;
    
    col = _col;
    
    drawSize = 15;
    
    float startVel = 1;
    float startPadding = 20;
    float startingXOffset = ofRandom(-10,10);
    
    //startingXOffset = -ofGetWidth()/2 + 80; //TESTING
    startVel = 5;
    
    if (spawnOnTop){
        pos.set(gameWidth/2+startingXOffset, -startPadding);
        vel.set(0,startVel);
    }else{
        pos.set(gameWidth/2+startingXOffset, gameHeight + startPadding);
        vel.set(0,-startVel);
    }
    
    justSpawned = true;
}

void Ball::addRepulsionForce(Ball * other, float radius, float maxForce){
    if (justSpawned){
        return;
    }
    
    ofVec2f diff = pos - other->pos;
    
    if (diff.length() < radius){
        float prc = 1 - (diff.length() / radius);
        diff.normalize();
        
        vel += diff * prc * maxForce;
        other->vel -= diff * prc * maxForce;
    }
}

void Ball::update(VectorField * field){
    
    if (!justSpawned){
        vel += field->getForceFromPos(pos);
    }
    
    vel *= friction;
    
    pos += vel;
    
    rollVal += vel;
    
    //simple bounce
    if (!justSpawned){
        if (pos.x < 0){
            pos.x = 0;
            vel.x = MAX(vel.x, -vel.x);
        }
        if (pos.x > gameWidth){
            pos.x = gameWidth;
            vel.x = MIN(vel.x, -vel.x);
        }
        if (pos.y < 0){
            pos.y = 0;
            vel.y = MAX(vel.y, -vel.y);
        }
        if (pos.y > gameHeight){
            pos.y = gameHeight;
            vel.y = MIN(vel.y, -vel.y);
        }
    }else{
        if (pos.x > 1 && pos.x < gameWidth-1 && pos.y > 1 && pos.y < gameHeight-1){
            justSpawned = false;
        }
    }
    
}

void Ball::draw(float alphaPrc){
    
    float rollStrength = 2;
    
    ofSetColor(col, 255*alphaPrc);
    ofFill();
    //ofCircle(pos.x, pos.y, drawSize);
    ofDrawSphere(pos.x, pos.y, drawSize);
    
    ofSetColor(0, 255*alphaPrc);
    ofNoFill();
    
    
    ofSetLineWidth(2);
    
    ofCircle(pos.x, pos.y, drawSize);
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateY(rollVal.x * rollStrength);
    ofRotateX(rollVal.y * -rollStrength);
    
    ofCircle(0, 0, drawSize+0.5);
    
    ofPopMatrix();
    
}


