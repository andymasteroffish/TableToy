//
//  TDAnimationMinder.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDAnimationMinder.h"



void TDAnimationMinder::setup(){
    
    walkCycleLength[FOE_DUMB] = 4;
    for (int i=0; i<walkCycleLength[FOE_DUMB]; i++){
        walkCycles[FOE_DUMB][i].loadImage("pic/td/foe_dumb/eye_walk_"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_DUMB] = 6;
    for (int i=0; i<deathCycleLength[FOE_DUMB]; i++){
        deathCycles[FOE_DUMB][i].loadImage("pic/td/foe_dumb/eye_die_"+ofToString(i)+".png");
    }
    
    walkCycleLength[FOE_STRONG] = 4;
    for (int i=0; i<walkCycleLength[FOE_STRONG]; i++){
        walkCycles[FOE_STRONG][i].loadImage("pic/td/foe_strong/squid_walk_"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_STRONG] = 7;
    for (int i=0; i<deathCycleLength[FOE_STRONG]; i++){
        deathCycles[FOE_STRONG][i].loadImage("pic/td/foe_strong/squid_die_"+ofToString(i)+".png");
    }
    
    walkCycleLength[FOE_FAST] = 6;
    for (int i=0; i<walkCycleLength[FOE_FAST]; i++){
        walkCycles[FOE_FAST][i].loadImage("pic/td/foe_fast/skate_walk_"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_FAST] = 5;
    for (int i=0; i<deathCycleLength[FOE_FAST]; i++){
        deathCycles[FOE_FAST][i].loadImage("pic/td/foe_fast/skate_die_"+ofToString(i)+".png");
    }
    
    //wave not set yet
    walkCycleLength[FOE_WAVE] = 3;
    for (int i=0; i<walkCycleLength[FOE_WAVE]; i++){
        walkCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_WAVE] = 1;
    for (int i=0; i<deathCycleLength[FOE_WAVE]; i++){
        deathCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
    }
    
    walkCycleLength[FOE_IGNORE] = 4;
    for (int i=0; i<walkCycleLength[FOE_IGNORE]; i++){
        walkCycles[FOE_IGNORE][i].loadImage("pic/td/foe_ignore/fly_walk_"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_IGNORE] = 8;
    for (int i=0; i<deathCycleLength[FOE_IGNORE]; i++){
        deathCycles[FOE_IGNORE][i].loadImage("pic/td/foe_ignore/fly_die_"+ofToString(i)+".png");
    }
    
    
    //other shit
    ignoreFoeAltWalkCycleLength = 2;
    for (int i=0; i<ignoreFoeAltWalkCycleLength; i++){
        ignoreFoeAltWalkCycle[i].loadImage("pic/td/foe_ignore/fly_fly_"+ofToString(i)+".png");
    }
    
    
    
}