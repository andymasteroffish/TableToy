//
//  Ball.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDFoe__
#define __emptyExample__TDFoe__

#include "ofMain.h"

class TDFoe{
public:
    
    void setup(vector<ofVec2f> * _path, float delay);
    void update(float deltaTime);
    void draw();
    void findNextNode();
    void takeDamage(float dmg);
    
    
    float delayTimer;
    
    float startingHealth;
    float health;
    
    float speed;    //pixels per second
    ofVec2f velocity;   //set based on angle and speed
    ofVec2f pos;
    float curAngle;
    
    
    vector<ofVec2f> * path;
    int nextNodeID;
    float minDistFromNodeToAdvance;
    
    //flags
    bool reachedTheEnd;
    bool killMe;
    
    float hitCircleSize;
    
};

#endif /* defined(__emptyExample__TDFoe__) */
