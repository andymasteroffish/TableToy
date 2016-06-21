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

enum FoeType{ FOE_DUMB, FOE_STRONG, FOE_FAST, FOE_WAVE, FOE_IGNORE  };

class TDFoe{
public:
    
    void setup(FoeType _type, ofImage * _pic, vector<ofVec2f> * _path, float delay);
    void setPos(ofVec2f _pos, int _nextNode);
    void update(float deltaTime);
    void draw(float alphaPrc);
    void findNextNode(bool snapPos);
    void takeDamage(float dmg);
    void freeze(float time);
    
    void setStatsFromType();
    
    FoeType type;
    
    ofImage * pic;
    
    float delayTimer;
    
    float startingHealth;
    float speed;    //pixels per second
    
    float health;
    
    float freezeTimer;
    float freezeSpeedReduction;
    
    ofVec2f velocity;   //set based on angle and speed
    ofVec2f basePos, pos;
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
