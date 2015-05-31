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
#include "GridPos.h"

class VectorField{
    
public:
    
    //the internal dimensions (grid size ie 60x40)
    #define FIELD_WIDTH 120
    #define FIELD_HEIGHT 30
    
    //external dimensions (screen pixel size ie 1024x768)
    int externalWidth, externalHeight;
    
    //the actual field
    ofVec2f field[FIELD_WIDTH][FIELD_HEIGHT];
    
    //drawing
    float drawingStrengthAdjust;
    
    
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
    //void getFieldBounds(GridPos fieldPos, float fieldRadius, int &startX, int &startY, int &endX, int &endY);
    
    void addOutwardCircle(float x, float y, float radius, float strength);
    void addOutwardSemiCircle(float x, float y, float radius, float strength, bool onLeft);
    
    void addFlowCircle(float x, float y, float radius,  float strength, float angle, float spread);
    void addFlowCircleFuckUp(float x, float y, float radius); //I fucked somehting up and it was kind of cool
    
    void addPulseCircle(float x, float y, float radius, float strength, float externalPulseDist, float externalPulseSize);
    
    void setStreamForce(); //pushes the enitre field towards the right semi randomly. Used in stream mode.
    
    
    
    //test funcitons
    void debugDraw();
    
    
    
    
};

#endif /* defined(__emptyExample__VectorField__) */
