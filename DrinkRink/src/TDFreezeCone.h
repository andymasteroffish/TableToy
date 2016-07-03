//
//  TDFreezeCone.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__TDFreezeCone__
#define __emptyExample__TDFreezeCone__

#include "ofMain.h"
#include "Tower.h"
#include "TDFoe.h"
#include "ofxControlPanel.h"

class TDFreezeCone{
public:
    
    void setup(Tower * _parentTower, ofxControlPanel * panel);
    void update(float deltaTime, vector<TDFoe> * foes);
    void checkFoes(vector<TDFoe> * foes);
    void draw(float alphaPrc);
    
    //this code from http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
    bool isPointInCone(ofVec2f point);
    
    ofVec2f pos;
    
    float freezeTime;   //how long to chill the foe
    
    float timer;
    float killTime;
    
    ofColor col;
    
    vector<ofVec2f> points;
    float spreadPrc;
    
    Tower * parentTower;
   
    
};

#endif /* defined(__emptyExample__TDFreezeCone__) */
