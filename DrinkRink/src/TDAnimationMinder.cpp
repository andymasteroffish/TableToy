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
    
    walkCycleLength[FOE_STRONG] = 4;
    for (int i=0; i<walkCycleLength[FOE_STRONG]; i++){
        walkCycles[FOE_STRONG][i].loadImage("pic/td/foe_strong/squid_walk_"+ofToString(i)+".png");
    }
    
    walkCycleLength[FOE_FAST] = 6;
    for (int i=0; i<walkCycleLength[FOE_FAST]; i++){
        walkCycles[FOE_FAST][i].loadImage("pic/td/foe_fast/skate_walk_"+ofToString(i)+".png");
    }
    
    //wave not set yet
    walkCycleLength[FOE_WAVE] = 3;
    for (int i=0; i<walkCycleLength[FOE_WAVE]; i++){
        walkCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
    }
    
    walkCycleLength[FOE_IGNORE] = 4;
    for (int i=0; i<walkCycleLength[FOE_IGNORE]; i++){
        walkCycles[FOE_IGNORE][i].loadImage("pic/td/foe_ignore/fly_walk_"+ofToString(i)+".png");
    }
    
    
    
//    //testing the others
//    for (int i=1; i<FOE_IGNORE+1; i++){
//        walkCycleLength[i] = 3;
//    }
//    for (int i=0; i<3; i++){
//        
//        walkCycles[FOE_STRONG][i].loadImage("pic/td/foe_strong"+ofToString(i)+".png");
//        walkCycles[FOE_FAST][i].loadImage("pic/td/foe_fast"+ofToString(i)+".png");
//        walkCycles[FOE_WAVE][i].loadImage("pic/td/foe_wave"+ofToString(i)+".png");
//        walkCycles[FOE_IGNORE][i].loadImage("pic/td/foe_ignore"+ofToString(i)+".png");
//    }
    
}