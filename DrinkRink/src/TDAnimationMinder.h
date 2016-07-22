//
//  TDAnimationMinder.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDAnimationMinder__
#define __emptyExample__TDAnimationMinder__

#include "ofMain.h"
#include "ofxControlPanel.h"

enum FoeType{ FOE_DUMB, FOE_STRONG, FOE_FAST, FOE_WAVE, FOE_IGNORE, NUM_TD_FOES  };


class TDAnimationMinder{
public:
    
    void setup();
   
    ofImage walkCycles[NUM_TD_FOES][6];
    int walkCycleLength[NUM_TD_FOES];
    
};

#endif /* defined(__emptyExample__TDAnimationMinder__) */
