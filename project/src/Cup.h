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

class Cup{
public:
    
    ofVec2f pos;
    float angle;
    
    float radius;
    
    float range;
    
    VectorField * field;
    
    bool hasBeenRemoved; //flag to kill
    
    void setup(float startX, float startY, VectorField * _field);
    virtual void customSetup(){}
    
    void update();
    virtual void customUpdate(){}
    
    void draw();
    virtual void customDraw(){}
    
    
    void onMouseDown(int x, int y, int button);
    void onMouseDrag(int x, int y, int button);
    void onMouseRelease(int x, int y, int button);
    
    //debug stuff
    bool isDebugSelected;
    ofVec2f distFromMouseWhenSelected;
    ofColor debugColor;
    
    bool isDebugSelectedForAngle;
    
    
    
    
};

#endif /* defined(__emptyExample__CupTower__) */
