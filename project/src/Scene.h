//
//  Sceen.h
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#ifndef __emptyExample__Sceen__
#define __emptyExample__Sceen__

#include "ofMain.h"
#include "VectorField.h"
#include "FieldParticle.h"

#include "CupTracker.h"
#include "CupInfo.h"

#include "Tower.h"


class Scene{
public:
    
    
    void setup(CupTracker * _cupTracker);
    virtual void setupCustom(){}
    
    void reset();
    virtual void resetCustom(){}
    
    void update(float _deltaTime);
    virtual void updateCustom(){}
    
    void checkCups();
    
    void draw();
    virtual void drawCustom(){}
    
    virtual void keyPressed(int key){}
    
    
    virtual void addTower(CupInfo thisInfo){}
    void removeTower(int vectorLoc);
    
    
    void makeFieldParticles();
    
    float deltaTime;
    
    
    string sceneName;
    
    VectorField field;
    
    CupTracker * cupTracker;
    
    vector<FieldParticle *> fieldParticles;
    
    
    vector<Tower *> towers;
    
    
    
};

#endif /* defined(__emptyExample__Sceen__) */
