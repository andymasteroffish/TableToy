//
//  TDBulletHit.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDBulletHit__
#define __emptyExample__TDBulletHit__

#include "ofMain.h"

class TDBulletHit{
public:
    
    void setup(ofVec2f _pos, ofImage * _pic);
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    ofVec2f pos;
    
    float timer;
    float killTime;
    
    ofImage * pic;
    float angleDeg;
    
    bool killMe;
    
    
};

#endif /* defined(__emptyExample__TDBulletHit__) */
