//
//  TDFoe.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDFoe__
#define __emptyExample__TDFoe__

#include "ofMain.h"
#include "ofxControlPanel.h"
#include "TDAnimationMinder.h"



class TDFoe{
public:
    
    void setup(FoeType _type, TDAnimationMinder * _anims, vector<ofVec2f> * _path, float delay, ofxControlPanel * panel);
    void setPos(ofVec2f _pos, int _nextNode);
    void update(float deltaTime);
    void draw(float alphaPrc);
    void findNextNode(bool snapPos);
    void takeDamage(float dmg);
    void freeze(float time);
    
    //void setStatsFromType();
    
    FoeType type;
    
    //animations
    TDAnimationMinder * anims;
    
    float animTimer;
    float frameTime;
    int curFrame;
    
    //getting hit animation
    float hitAnimationTime;
    float hitAnimationTimer;
    float hitBlinkSpeed;
    
    //movement and game values
    float delayTimer;
    
    float startingHealth;
    float speed;    //pixels per second
    
    float health;
    
    float freezeTimer;
    float freezeSpeedReduction;
    
    float waveDist, wavePeriod;
    float ignoreFoeSpeedIncrease;
    bool ignoringPath;
    float randVal;
    
    ofVec2f velocity;   //set based on angle and speed
    ofVec2f basePos, pos;
    float curAngle;
    float displayAngle;
    
    
    vector<ofVec2f> * path;
    int nextNodeID;
    float minDistFromNodeToAdvance;
    
    //flags
    bool reachedTheEnd;
    bool killMe;
    
    float hitCircleSize;
    
};

#endif /* defined(__emptyExample__TDFoe__) */
