//
//  TDHomeHit.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDHomeHit__
#define __emptyExample__TDHomeHit__

#include "ofMain.h"
#include "ofxControlPanel.h"



class TDHomeHit{
public:
    
    void setup(ofVec2f _pos);
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    ofVec2f pos;
    
    float curSize;
    float growthPerSec;
    
    float killDist, fadeDist;
    bool killMe;
    
};

#endif /* defined(__emptyExample__TDHomeHit__) */
