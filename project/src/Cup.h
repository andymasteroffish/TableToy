//
//  CupTower.h
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#ifndef __emptyExample__CupTower__
#define __emptyExample__CupTower__

#include "ofMain.h"
#include "VectorField.h"
#include "Utils.h"

class Cup{
public:
    
    ofVec2f pos;
    float angle;
    
    float cupSize;
    
    float range;
    float fieldRange;
    
    VectorField * field;
    
    float deltaTime;
    
    GridPos fieldPos;
    
    bool hasBeenRemoved; //flag to kill
    
    void setup(float startX, float startY, VectorField * _field);
    virtual void customSetup(){}
    
    void update(float _deltaTime);
    virtual void customUpdate(){}
    
    void calculateFieldRange();
    
    void draw();
    virtual void customDraw(){}
    
    
    //debug stuff
    bool isDebugSelected;
    ofVec2f distFromMouseWhenSelected;
    ofColor debugColor;
    
    bool isDebugSelectedForAngle;
    
    
    
    
};

#endif /* defined(__emptyExample__CupTower__) */
