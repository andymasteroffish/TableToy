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
        walkCycles[FOE_DUMB][i].loadImage("td/foe_dumb/walk_"+ofToString(i+1)+".png");
    }
    deathCycleLength[FOE_DUMB] = 6;
    for (int i=0; i<deathCycleLength[FOE_DUMB]; i++){
        deathCycles[FOE_DUMB][i].loadImage("td/foe_dumb/die_"+ofToString(i+1)+".png");
    }
    
    walkCycleLength[FOE_STRONG] = 4;
    for (int i=0; i<walkCycleLength[FOE_STRONG]; i++){
        walkCycles[FOE_STRONG][i].loadImage("td/foe_strong/walk_"+ofToString(i+1)+".png");
    }
    deathCycleLength[FOE_STRONG] = 7;
    for (int i=0; i<deathCycleLength[FOE_STRONG]; i++){
        deathCycles[FOE_STRONG][i].loadImage("td/foe_strong/die_"+ofToString(i+1)+".png");
    }
    
    walkCycleLength[FOE_FAST] = 6;
    for (int i=0; i<walkCycleLength[FOE_FAST]; i++){
        walkCycles[FOE_FAST][i].loadImage("td/foe_fast/walk_"+ofToString(i+1)+".png");
    }
    deathCycleLength[FOE_FAST] = 5;
    for (int i=0; i<deathCycleLength[FOE_FAST]; i++){
        deathCycles[FOE_FAST][i].loadImage("td/foe_fast/die_"+ofToString(i+1)+".png");
    }
    
    walkCycleLength[FOE_IGNORE] = 4;
    for (int i=0; i<walkCycleLength[FOE_IGNORE]; i++){
        walkCycles[FOE_IGNORE][i].loadImage("td/foe_ignore/walk_"+ofToString(i+1)+".png");
    }
    deathCycleLength[FOE_IGNORE] = 8;
    for (int i=0; i<deathCycleLength[FOE_IGNORE]; i++){
        deathCycles[FOE_IGNORE][i].loadImage("td/foe_ignore/die_"+ofToString(i+1)+".png");
    }
    
    //WAVE FOE IS DEFUNCT!
    walkCycleLength[FOE_WAVE] = 3;
    for (int i=0; i<walkCycleLength[FOE_WAVE]; i++){
        walkCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
    }
    deathCycleLength[FOE_WAVE] = 1;
    for (int i=0; i<deathCycleLength[FOE_WAVE]; i++){
        deathCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
    }
    
    
    //other shit
    ignoreFoeAltWalkCycleLength = 2;
    for (int i=0; i<ignoreFoeAltWalkCycleLength; i++){
        ignoreFoeAltWalkCycle[i].loadImage("td/foe_ignore/fly_"+ofToString(i+1)+".png");
    }
    
    dumbFoeSpawnCycleLength = 6;
    for (int i=0; i<dumbFoeSpawnCycleLength; i++){
        dumbFoeSpawnCycle[i].loadImage("td/foe_dumb/spawn_"+ofToString(i+1)+".png");
    }
    
    for (int i=0; i<NUM_HEART_PICS; i++){
        heartCycle[i].loadImage("td/heart/heart_"+ofToString(i)+".png");
    }
    
    
    
}