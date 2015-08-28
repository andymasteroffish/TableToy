//
//  VectorField.h
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#ifndef __emptyExample__VectorField__
#define __emptyExample__VectorField__

#include "ofMain.h"
#include "Utils.h"

class FieldCell{
public:
    ofVec2f vel;
    //vector<ParticleType> potentialParticleTypes;    //HOLY SHIT THIS IS UGLY
    
    int curNumTypes;
    ParticleType potentialParticleTypes[NUM_PARTICLE_TYPES] ;
    float typeWeights[NUM_PARTICLE_TYPES];
    
    void reset(){
        vel.set(0,0);
        curNumTypes = 0;
    }
    
    void addPotentialParticleType(ParticleType type, float weight){
        //check if it's in there
        for (int i=0; i<curNumTypes; i++){
            if (potentialParticleTypes[i] == type){
                typeWeights[i] += weight;
                return;
            }
        }
        //add if if there's room (there should always be room)
        if (curNumTypes <= NUM_PARTICLE_TYPES){
            potentialParticleTypes[curNumTypes] = type;
            typeWeights[curNumTypes] = weight;
            curNumTypes++;
        }else{
            cout<<"NO ROOM FOR PARTICLE TYPE. HOW DID THIS HAPPEN????"<<endl;
        }
    }
    
    ParticleType getRandomParticleType(){
        
        if (curNumTypes == 0){
            return PARTICLE_NO_TYPE;
        }
        
        float totalWeight = 0;
        for (int i=0; i<curNumTypes; i++){
            totalWeight += typeWeights[i];
        }
        
        float thisVal = ofRandom(totalWeight);
        for (int i=0; i<curNumTypes; i++){
            thisVal -= typeWeights[i];
            if (thisVal <= 0){
                return potentialParticleTypes[i];
            }
        }
        
    }
    
};

class VectorField{
    
public:
    
    //the internal dimensions
    #define FIELD_WIDTH 120
    #define FIELD_HEIGHT 40
    int fieldWidth, fieldHeight; //and some variables ot make it more accessible
    
    //external dimensions
    int gameWidth, gameHeight;
    
    //the actual field
    FieldCell field[FIELD_WIDTH][FIELD_HEIGHT];
    
    //drawing
    float drawingStrengthAdjust;
    
    //trying out displays
    ofColor gridColor;
    float gridDrawingAdjust;
    bool showVerticalGrid;
    bool showHorizontalGrid;
    bool showGridFill;
    bool useGridWiggle;
    float gridWiggleSpeed;
    float gridWiggleStrength;
    bool useGridFade;
    bool useVarryingWidths;
    float gridValThreshold;
    float gridValCeiling;
    float gridMinLineWidth, gridMaxLineWidth;
    bool showVerticalGridCurved;
    bool showHorizontalGridCurved;
    
    //**************
    //functions
    //**************
    
    void setupField(int outerW, int outerH);
    
    void clear();               //wipes the field
    void fade(float fadeVal);   //lowers all values
    
    //getting info from the field
    ofVec2f getForceFromPos(ofVec2f pos);
    ofVec2f getForceFromPos(float xPos, float yPos);
    
    GridPos getInternalPointFromExternal(float externalX, float externalY);
    ofVec2f getExternalPointFromInternal(int internalX, int internalY);
    
    //affecting the field
    Bounds getFieldBounds(GridPos fieldPos, float fieldRadius);
    
    void addFlowCircleFuckUp(float x, float y, float radius); //I fucked somehting up and it was kind of cool
    
    void setStreamForce(); //pushes the enitre field towards the right semi randomly. Used in stream mode.
    
    
    
    //test funcitons
    void debugDraw();
    
    //trying out displays
    void drawGrid(float alphaPrc);
    
    
    
    
    
};

#endif /* defined(__emptyExample__VectorField__) */
