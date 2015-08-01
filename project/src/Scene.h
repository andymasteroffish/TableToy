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

#include "ofxXmlSettings.h"


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
    
    void startFade();
    
    
    void makeFieldParticles();
    
    void readXML();
    virtual void readXMLCustom(ofxXmlSettings xml){}
    int stringToHex(string input);
    
    float deltaTime;
    
    
    string sceneName;
    
    VectorField field;
    
    CupTracker * cupTracker;
    
    vector<FieldParticle *> fieldParticles;
    
    
    vector<Tower *> towers;
    
    //some fucking color info
    ofColor bgCol;
    vector<ofColor> particleColors;
    float cupDebugAlpha;
    vector<ofColor> cupDebugColors;
    
    //fading out when switched
    bool isFading, isDoneFading;
    float fadeTime;
    float fadeTimer;
    float fadePrc;
    
    
    
};

#endif /* defined(__emptyExample__Sceen__) */
