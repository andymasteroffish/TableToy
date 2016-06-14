//
//  TDFoe.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFoe.h"


void TDFoe::setup(vector<ofVec2f> * _path, float delay){
    path = _path;
    
    delayTimer = delay;
    
    startingHealth = 3;
    health = startingHealth;
    
    speed = 100;
    
    minDistFromNodeToAdvance = 5;
    
    nextNodeID = 0;
    findNextNode();
    
    reachedTheEnd = false;
    killMe = false;
}

void TDFoe::update(float deltaTime){
    
    //check if we are not still waiting to start
    delayTimer -= deltaTime;
    if (delayTimer > 0){
        return;
    }
    
    //move along
    if (!reachedTheEnd){
        pos += velocity * deltaTime;
        
        if (ofDistSquared(pos.x, pos.y, path->at(nextNodeID).x, path->at(nextNodeID).y) < minDistFromNodeToAdvance*minDistFromNodeToAdvance){
            findNextNode();
        }
    }
    
    
    
    
}

void TDFoe::draw(){
    if (delayTimer > 0){
        return;
    }
    
    //debug test
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate( ofRadToDeg(curAngle) );
    
    ofSetColor( ofColor::salmon);
    ofRect(-20,-10, 40, 20);
    
    ofSetColor( ofColor::burlyWood);
    ofRect(10,-10, 10, 20);
    
    ofPopMatrix();
    
    
}

void TDFoe::findNextNode(){
    //snap it to the current node
    pos = path->at(nextNodeID);
    
    //advance the node
    nextNodeID++;
    
    //check if we reached the end
    if (nextNodeID >= path->size()){
        reachedTheEnd = true;
        return;
    }
    
    //set the angle and velocity
    curAngle = atan2(path->at(nextNodeID).y-pos.y, path->at(nextNodeID).x-pos.x);
    velocity.x = cos(curAngle) * speed;
    velocity.y = sin(curAngle) * speed;
}

void TDFoe::takeDamage(float dmg){
    health -= dmg;
    if (health <= 0){
        killMe = true;
    }
    
}