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
#include "ofxControlPanel.h"

class TDBullet{
public:
    
    void setup(ofVec2f _pos, float _angle, float startDist, bool _isFire, ofImage * _pic, ofxControlPanel * panel);
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    ofVec2f pos;
    ofVec2f vel;
    
    float size;
    float dmg;
    
    ofColor col;
    
    bool isFire;
    
    ofImage * pic;
    float angle;
   
    
};

#endif /* defined(__emptyExample__TDBullet__) */
