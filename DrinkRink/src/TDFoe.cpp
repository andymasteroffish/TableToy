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
    
    hitCircleSize = 40;
    
    speed = 100 * 4;
    
    minDistFromNodeToAdvance = speed / 20;
    
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
    
    ofSetColor(200, 0, 0, 100);
    ofCircle(0, 0, hitCircleSize);
    
    ofSetColor( ofColor::salmon);
    ofRect(-30,-20, 60, 40);
    
    ofSetColor( ofColor::burlyWood);
    ofRect(20,-20, 10, 40);
    
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