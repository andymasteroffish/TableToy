//
//  GoalWinFill.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/27/15.
//
//

#ifndef __DrinkRink__GoalWinFill__
#define __DrinkRink__GoalWinFill__

#include "ofMain.h"
#include "Goal.h"

class GoalWinFill{
public:
    
    
    void setup();
    void start(Goal winningGoal);
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    int numRings;
    bool isActive;
    float timer;
    
    float timeBeforeRings;
    float timeBetweenRings;
    float growthRate;
    
    float sat, bri;
    float baseHue;
    
    ofVec2f pos;
    
};

#endif /* defined(__DrinkRink__GoalWinFill__) */
