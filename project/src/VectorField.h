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

class VectorField{
    
public:
    
    //the internal dimensions
    #define FIELD_WIDTH 120
    #define FIELD_HEIGHT 40
    int fieldWidth, fieldHeight; //and some variables ot make it more accessible
    
    //external dimensions (screen pixel size ie 1024x768)
    int externalWidth, externalHeight;
    
    //the actual field
    ofVec2f field[FIELD_WIDTH][FIELD_HEIGHT];
    
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
