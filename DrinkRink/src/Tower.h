//
//  Tower.h
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
#include "CupInfo.h"

class Tower{
public:
    
   
    
    bool hasBeenRemoved; //flag to kill
    bool hasBeenCheckedThisFrame;
    
    void setup(CupInfo thisCup, VectorField * _field);
    virtual void customSetup(){}
    
    void setFromCupInfo(CupInfo thisInfo);
    
    void update(float _deltaTime);
    virtual void customUpdate(){}
    
    void calculateFieldRange();
    
    void draw(float alphaPrc);
    virtual void customDraw(float alphaPrc){}
    
    
    ofVec2f pos;
    float angle;
    int uniqueID;   //this is what links it to a physical cup
    float startTime;
    
    float towerSize;
    
    float range;
    float fieldRange;
    
    VectorField * field;
    
    float deltaTime;
    
    GridPos fieldPos;
    
    
    //debug stuff
    bool isDebugSelected;
    ofVec2f distFromMouseWhenSelected;
    ofColor debugColor;
    
    bool isDebugSelectedForAngle;
    
    bool showDebugImage;
    
    
};

#endif /* defined(__emptyExample__CupTower__) */
