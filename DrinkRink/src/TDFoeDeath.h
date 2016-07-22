//
//  TDFoeDeath.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDFoeDeath__
#define __emptyExample__TDFoeDeath__

#include "ofMain.h"
#include "ofxControlPanel.h"
#include "TDAnimationMinder.h"
#include "TDFoe.h"



class TDFoeDeath{
public:
    
    void steup(TDFoe * parent);
    void update(float deltaTime);
    void draw();
    
    
    TDAnimationMinder * anims;
    
    FoeType type;
    
    float timer;
    float frameTime;
    int curFrame;
    
    ofVec2f pos;
    float angle;
    
    bool killMe;
    
};

#endif /* defined(__emptyExample__TDFoeDeath__) */
