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

//Towers are the game world verison of cups.
//When the cup tracker sees a new cup, it creates a tower which exists in the game world and can affect the vector field.
//All scenes have information about the towers currently on the board. They can be access through the towers vector in Scene

class Tower{
public:
    
    //---------
    //Functions
    //---------
   
    //in your custom tower classes, you probably want to make override functions for all of the virtual functions
    //these will be called automaticly when you'd expect them to be
    virtual void customSetup(){}
    virtual void customUpdate(){}
    virtual void customDraw(float alphaPrc){}
    
    //you shouldn't need to mess with these functions
    void setup(CupInfo thisCup, VectorField * _field);
    void setFromCupInfo(CupInfo thisInfo);
    void update(float _deltaTime);
    void draw(float alphaPrc, bool showCupDebug);
    
    //functions that you may want to call depending on what you're doing
    void calculateFieldRange();     //call this any time you change the range
    
    //you can ignore this one. It is just so I don't duplicate a funciton in the sports scene towers
    void drawSportsTower(float alphaPrc);
    
    
    //---------
    //Useful public variables
    //---------
    ofVec2f pos;        //x,y location in game world value
    float targetAngle;  //angle in radians of the physical cup's current rotation (updated by cup tracker)
    float curAngle;     //angle in radians the tower is suing that quickly eases between the newest targeAngle and the tower's existing angle
    int uniqueID;       //this is the AR code value
    float startTime;    //when (in seconds) the cup was recognized. If the cup is removed and placed back down, this will be the time of the most recent recognition
    float randVal;      //for noise or anything else where it would be useful to have a static but randomly decided value. This is set when the cup is recognizied.
    string towerType;   //a name to identify the tower type
    
    //---------
    //Public variables that deal with the vector field
    //---------
    float range;                //range in game world that this tower effects the vector field
    float fieldRange;           //range converted to field values. Do not edit this manually. Call calculateFieldRange()
    
    ParticleType particleType;  //the type of field particle this tower will make (assuming it has any effect on the vector field)
    float particleTypeWeight;   //how likely a given particle spawned within range of this tower will be of the particlerType this tower uses
    float startingRange;        //Stores how big the range was when the tower started. Used for some effects like shrinking the range. You can mostly ignore this
    
    
    
    //---------
    //Other variables
    //---------
    
    float towerSize;            //used for debugging. This is an aproximation of how big the cup is
    
    float angleXeno;            //prcentage of how close the tower's angle should get to the cup's actual angle each frame
    
    VectorField * field;        //pointer to the vector field so the tower can affect the field
    GridPos fieldPos;           //word pos coverted into the vector field position
    
    float deltaTime;            //time since last frame
    
    
    //flags for the cup tracker
    bool hasBeenRemoved;            //flag to kill this tower
    bool hasBeenCheckedThisFrame;
    
    //debug stuff
    bool isDebugSelected;
    ofVec2f distFromMouseWhenSelected;
    ofColor debugColor;
    
    bool isDebugSelectedForAngle;
    
};

#endif /* defined(__emptyExample__CupTower__) */
