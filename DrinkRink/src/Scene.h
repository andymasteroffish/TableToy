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
#include "ofxControlPanel.h"


class Scene{
public:
    
    
    void setup(CupTracker * _cupTracker, int _gameWidth, int _gameHeight);
    virtual void setupCustom(){}
    
    void reset();
    virtual void resetCustom(){}
    
    void update(float _deltaTime, ofxControlPanel * panel);
    virtual void updateCustom(){}
    void checkPanelValues(ofxControlPanel * panel);
    virtual void checkPanelValuesCustom(ofxControlPanel * panel){}
    
    void checkCups();
    
    void draw();
    virtual void drawBackgroundCustom(){}
    virtual void drawCustom(){}
    
    virtual void keyPressed(int key){}
    virtual void mouseMoved(int x, int y){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    
    
    virtual void addTower(CupInfo thisInfo){}
    void removeTower(int vectorLoc);
    
    void startFade();
    
    
    void makeFieldParticles();
    
    int stringToHex(string input);
    
    
    
    
    string sceneName;
    float deltaTime;
    
    int gameWidth, gameHeight;
    VectorField field;
    CupTracker * cupTracker;
    
    vector<FieldParticle *> fieldParticles;
    vector<Tower *> towers;
    
    bool showCupDebug;
    
    ParticleType defaultParticleType;
    
    //some fucking color info
    ofColor bgCol;
    vector<ofColor> particleColors;
    float cupDebugAlpha;
    vector<ofColor> cupDebugColors;
    
    //fading out when switched
    bool isFading, isDoneFading;
    float fadeTime;
    float fadeTimer;
    float alphaPrc;
    
    //telling the main app to switch scenes
    bool switchScenesFlag;
    int sceneToSwitchTo;
    
    //flag to not use our debug and tetsing values
    bool ignorePanelValues;
    
    //testing different particle options
    int numFieldParticlesPerFrame;
    float p_friction;
    float p_killTime;
    
    bool p_showDot;
    bool p_fillDot;
    float p_dotSize;
    
    bool p_useNoiseWiggle;
    float p_noiseWiggleRange, p_noiseWigglePower;
    float p_noiseWiggleRate;
    
    bool p_useTrails;
    int p_numTrailPositions;
    float p_trailStartWidth, p_trailEndWidth;
    
    
    
};

#endif /* defined(__emptyExample__Sceen__) */
