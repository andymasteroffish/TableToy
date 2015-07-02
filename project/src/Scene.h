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
#include "CupInfo.h"
#include "Cup.h"

class Scene{
public:
    
    
    void setup();
    virtual void setupCustom(){}
    void reset();
    virtual void resetCustom(){}
    void update(float _deltaTime);
    virtual void updateCustom(){}
    void draw();
    virtual void drawCustom(){}
    
    virtual void keyPressed(int key){}
    
    
    virtual void addCup(CupInfo thisInfo){}
    
    float deltaTime;
    
    
    string sceneName;
    
    VectorField field;
    
    vector<FieldParticle *> fieldParticles;
    
    
    vector<Cup *> cups;
    
    
    
};

#endif /* defined(__emptyExample__Sceen__) */
