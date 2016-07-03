//
//  TDFireball.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDFireball__
#define __emptyExample__TDFireball__

#include "ofMain.h"
#include "ofxControlPanel.h"

class TDFireball{
public:
    
    void setup(ofVec2f _pos, ofxControlPanel * panel);
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    ofVec2f pos;
    
    float startSize;
    float dmg;
    
    float timer;
    float killTime;
    
    ofColor col;
   
    
};

#endif /* defined(__emptyExample__TDFireball__) */
