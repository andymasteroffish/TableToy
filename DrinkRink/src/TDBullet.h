//
//  TDBullet.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDBullet__
#define __emptyExample__TDBullet__

#include "ofMain.h"

class TDBullet{
public:
    
    void setup(ofVec2f _pos, float angle);
    void update(float deltaTime);
    void draw();
    
    ofVec2f pos;
    ofVec2f vel;
    
    float size;
    float dmg;
   
    
};

#endif /* defined(__emptyExample__TDBullet__) */
