//
//  VectorField.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#include "VectorField.h"



//-------------------------------------------------------------
void VectorField::setupField(int outerW, int outerH){
    
    externalWidth = outerW;
    externalHeight = outerH;
    
    drawingStrengthAdjust = 5;
    
    clear();
    
}


//-------------------------------------------------------------
void VectorField::clear(){
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            field[x][y].set(0,0);
        }
    }
}

//-------------------------------------------------------------
void VectorField::fade(float fadeVal){
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            field[x][y].x *= fadeVal;
            field[x][y].y *= fadeVal;
        }
    }
}

//-------------------------------------------------------------
ofVec2f VectorField::getForceFromPos(ofVec2f pos){
    return getForceFromPos(pos.x, pos.y);
}

ofVec2f VectorField::getForceFromPos(float xPos, float yPos){
    
    //cout<<"external pos "<<xPos<<" , "<<yPos<<endl;
    
    GridPos internalPos = getInternalPointFromExternal(xPos, yPos);
    
    //cout<<"internal "<<internalPos.x<<" , "<<internalPos.y<<endl;
    
    //anything out of bound can return 0
    if (!internalPos.isInBounds(FIELD_WIDTH, FIELD_HEIGHT)){
        ofVec2f returnVal;
        returnVal.set(0,0);
        return returnVal;
    }
    
    //otherwiose return the force value
    return field[internalPos.x][internalPos.y];
}

//-------------------------------------------------------------
GridPos VectorField::getInternalPointFromExternal(float externalX, float externalY){
    
    //convert from xpos and ypos to percentages
    float xPrct = externalX / (float)externalWidth;
    float yPrct = externalY / (float)externalHeight;
    
    //figure out where we are in the field array
    GridPos returnVal;
    returnVal.x = (int)(xPrct * FIELD_WIDTH);
    returnVal.y = (int)(yPrct * FIELD_HEIGHT);
    
    return returnVal;
}

//-------------------------------------------------------------
ofVec2f VectorField::getExternalPointFromInternal(int internalX, int internalY){
    //get the percentage
    float xPrct = (float)internalX / (float)FIELD_WIDTH;
    float yPrct = (float)internalY / (float)FIELD_HEIGHT;
    
    //figure out where we are in the external size
    ofVec2f returnVal;
    returnVal.x = externalWidth * xPrct;
    returnVal.y = externalHeight * yPrct;
    
    return returnVal;
}


//-------------------------------------------------------------
void VectorField::addOutwardCircle(float x, float y, float radius, float strength){
    
    //get our center
    GridPos fieldPos = getInternalPointFromExternal(x, y);
    //and the radius in field size
    float radiusPrct = radius / (float)externalWidth;
    float fieldRadius = (float)(radiusPrct * FIELD_WIDTH);
    
    //figure out how far we have to go
    int startX  = MAX(fieldPos.x - fieldRadius, 0);
    int startY  = MAX(fieldPos.y - fieldRadius, 0);
    int endX    = MIN(fieldPos.x + fieldRadius, FIELD_WIDTH);
    int endY    = MIN(fieldPos.y + fieldRadius, FIELD_HEIGHT);
    
    for (int x=startX; x < endX; x++){
        for (int y=startY; y< endY; y++){
            
            float distance =  (float)sqrt( (fieldPos.x-x) * (fieldPos.x-x) +
                                          (fieldPos.y-y) * (fieldPos.y-y));
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < fieldRadius){
                
                float prct = 1.0f - (distance / fieldRadius);
                float strongness = strength * prct;
                
                float unit_px = ( fieldPos.x - x) / distance;
                float unit_py = ( fieldPos.y - y) / distance;
                field[x][y].x -= unit_px * strongness;
                field[x][y].y -= unit_py * strongness;
            }
        }
    }
}

//-------------------------------------------------------------
//THIS IS DUMB AND REDUNDANT. IF YOU KEEP IT, WRAP IT UP IN OUTWARD CIRCLE SOMEHOW
void VectorField::addOutwardSemiCircle(float x, float y, float radius, float strength, bool onLeft){
    
    //get our center
    GridPos fieldPos = getInternalPointFromExternal(x, y);
    //and the radius in field size
    float radiusPrct = radius / (float)externalWidth;
    float fieldRadius = (float)(radiusPrct * FIELD_WIDTH);
    
    //figure out how far we have to go
    int startX  = MAX(fieldPos.x - fieldRadius, 0);
    int startY  = MAX(fieldPos.y - fieldRadius, 0);
    int endX    = MIN(fieldPos.x + fieldRadius, FIELD_WIDTH);
    int endY    = MIN(fieldPos.y + fieldRadius, FIELD_HEIGHT);
    
    if (onLeft){
        endX = fieldPos.x;
    }else{
        startX = fieldPos.x;
    }
    
    for (int x=startX; x < endX; x++){
        for (int y=startY; y< endY; y++){
            
            float distance =  (float)sqrt( (fieldPos.x-x) * (fieldPos.x-x) +
                                          (fieldPos.y-y) * (fieldPos.y-y));
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < fieldRadius){
                
                float prct = 1.0f - (distance / fieldRadius);
                float strongness = strength * prct;
                
                float unit_px = ( fieldPos.x - x) / distance;
                float unit_py = ( fieldPos.y - y) / distance;
                field[x][y].x -= unit_px * strongness;
                field[x][y].y -= unit_py * strongness;
            }
        }
    }
}

//-------------------------------------------------------------
void VectorField::setStreamForce(){
    
    float minX = 0.1;
    float maxX = 3;
    
    float yRange = 1;
    
    float noiseScale = 0.5;
    float noiseSpeed = 0.2;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            ofVec2f thisForce;
            
            float xPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed );
            thisForce.x =  xPrc * maxX + (1-xPrc) * minX;
            
            float yPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed, 1000 );
            thisForce.y = yPrc * yRange + (1-yPrc) * (-yRange);
            
            field[x][y] += thisForce;
        }
    }
    
}


//-------------------------------------------------------------
void VectorField::debugDraw(){
    
    ofSetLineWidth(1);
    
    float scaleX = (float)externalWidth / (float)FIELD_WIDTH;
    float scaleY = (float)externalHeight / (float)FIELD_HEIGHT;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            
            //figure out where this line will be
            float px = x * scaleX;
            float py = y * scaleY;
            float px2 = px + field[x][y].x * drawingStrengthAdjust;
            float py2 = py + field[x][y].y * drawingStrengthAdjust;
            
            ofLine( px, py, px2, py2 );
            
            // draw a baseline to show direction
            // get the line as vector, calculate length, then normalize.
            // rotate and draw based on length
            ofVec2f line;
            line.set(px2-px, py2-py);
            float length = line.length();
            line.normalize();
            line.rotate(90);  // these are angles in degrees
            ofLine(px - line.x*length*0.2, py - line.y*length*0.2, px + line.x*length*0.2, py + line.y*length*0.2);
            
            ofCircle(px,py, 1);
            
        }
    }
    
}






