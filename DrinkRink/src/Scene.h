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

//A Scene is where the game happens. You can almost trate this like you would ofApp in a standard oF application.
//Each scene has its own setup, update, draw funcitons etc
//Scenes are automaticly hooked into Cup Tracker and will create, move, and remove Towers as cups are added or rmeoved from the board
//Scenes also maintain their own vector field so Towers or the scene itself can create particle effects

//When making a new scene, don't forget to give it a SCENE_[YOUR_SCENE] ID number in ofApp.h and to include it in setup() in ofApp.cpp
//You'll also need to increase NUM_SCENES by 1 (in ofApp.h just above where you define the scene's ID

class Scene{
public:
    
    
    //---------
    //Override Functions
    //---------
    
    //override function that you can replace in your Scene class. These will be called automaticly as needed.
    //if you do not need them, don't do anything and they will be innactive (called but won't do anything)
    virtual void setupCustom(){}            //called when the scene is fist setup on launch. Use for initialization
    virtual void setupPanelValues(ofxControlPanel * panel){}         //if you want to add a control panel screen for the scene, do it here
    virtual void resetCustom(){}            //called when this scene is switched to. Will be called every time we return to this scene
    virtual void updateCustom(){}           //update function called every frame while this scene is active
    virtual void drawBackgroundCustom(){}   //a draw call that is called first, before field particle are drawn
    virtual void drawCustom(){}             //main draw call. Drawn on top of field particles
    virtual void checkPanelValuesCustom(ofxControlPanel * panel){}  //hooks into the control panel if you want to add custom sliders etc. for debug and testing
    virtual void removingTowerCustom(Tower * towerBeingRemoved){}   //called when a tower is removed. Useful if anything in your scene is dependent on specific towers
    
    //the addTower function adds a blank tower by default. You will almost ceratinly want to make an override funciton to replace this so that your Scene spawns the correct Tower types
    //your custom addTower should follow the same basic patters. Make sure to call setup on any new tower and to add it to the towers vector
    virtual void addTower(CupInfo thisCup){
        Tower * newTower = new Tower();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    
    //override function only used for debug and testing. Ignore if you don't need them. They are called exactly when you'd expect them to be
    virtual void keyPressed(int key){}
    virtual void mouseMoved(int x, int y){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    
    //---------
    //Standard Functions
    //---------
    //standard scene functions. Don't mess with these too much. Use the asociated override functions to do your own stuff
    //All of these functions should be called automaticly so you shouldn't need to worry about them in any new Scene class you create
    void setup(CupTracker * _cupTracker, int _gameWidth, int _gameHeight);
    void reset();
    void update(float _deltaTime, ofxControlPanel * panel);
    void checkPanelValues(ofxControlPanel * panel);
    void checkCups();
    void draw();
    
    void removeTower(int vectorLoc);
    void startFade();
    
    void makeFieldParticles();
    
    int stringToHex(string input);
    
    
    //---------
    //Useful Public Variables
    //---------
    
    string sceneName;           //give your scene a name in setupCustom()! This is just for internal use and will not be displayed
    int gameWidth, gameHeight;  //width and height of the game world. These are set automaticly. Do not change them.
    vector<Tower *> towers;     //a list of all towers currently active in the scene. This is maintained autocamticly. You should not manually add or remove elements
    
    float deltaTime;            //time since last frame. Used to do things in realtime instead of being framearte indipendent. This is updated automaticly each frame and should not be adjusted.
    
    float activeTimer;          //how long has this scene been running?
    float idleTimer;            //how long has it been since somebody moved a cup?
    
    vector<FieldParticle *> fieldParticles; //a list of all of the field particles currently active
    ParticleType defaultParticleType;       //the default particle that this scene should spawn. If you do not define this in setupCustom, the default particle will be used
    int numFieldParticlesPerFrame;          //how many field particles to generate every frame. If not set in setupCustom a default value is used
    
    //Some Utility stuff
    VectorField field;          //the vector field used to create the field particles. For the most part, you won't need to mess with this
    CupTracker * cupTracker;    //the cup tracker that tells the scene where new cups are and converts them to towers. Don't mess with this.
    bool showCupDebug;          //flag to show debug cups. Turned on or off by a keystroke in ofApp
    
    //Telling the main app to switch scenes
    //Use these to have your scene anounce that it is done so the main app can switch to the next one
    bool switchScenesFlag;      //set this to true to switch scenes. The main app will set it back to false after the switch has been made
    //int sceneToSwitchTo;        //the ID number of the scene you'd like to. At least for now, you must specify something, although you can always set it to be a random value
        //THIS HAS BEEN REMOVED
    
    //Some color info
    ofColor bgCol;                  //set this in setupCustom. It will be the backgorund color of your scene
    vector<ofColor> particleColors; //I'm not 100% that this is still being used
    
    //Debug color info. You probably don't need to mess with this
    float cupDebugAlpha;
    vector<ofColor> cupDebugColors;
    
    //fading out when switched
    //do not edit these values.
    bool isFading, isDoneFading;
    float fadeTime;
    float fadeTimer;
    float alphaPrc;
    
    //some stuff for tracking when a cup has been moved enough to reset the idle timer
    float idleTowerMoveThreshold;
    float idleTowerRotateThreshold;
    
    
    //Testing different particle options
    //These maybe aren't being used? I don't know. Don't fuck with them I guess
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
