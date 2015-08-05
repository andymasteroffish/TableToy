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
    
    fieldWidth = FIELD_WIDTH;
    fieldHeight = FIELD_HEIGHT;
    
    externalWidth = outerW;
    externalHeight = outerH;
    
    drawingStrengthAdjust = 15;
    
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
Bounds VectorField::getFieldBounds(GridPos fieldPos, float fieldRadius){
    Bounds bounds;
    
    bounds.topLeft.x  = MAX(fieldPos.x - fieldRadius, 0);
    bounds.topLeft.y  = MAX(fieldPos.y - fieldRadius, 0);
    bounds.bottomRight.x    = MIN(fieldPos.x + fieldRadius + 1, FIELD_WIDTH-1);
    bounds.bottomRight.y    = MIN(fieldPos.y + fieldRadius + 1, FIELD_HEIGHT-1);
    
    return bounds;
}


//-------------------------------------------------------------
//by using x, y (instead of y, x) in atan2, I created a cool effect
void VectorField::addFlowCircleFuckUp(float x, float y, float radius){
    //get our center
    GridPos fieldPos = getInternalPointFromExternal(x, y);
    //and the radius in field size
    float radiusPrct = radius / (float)externalWidth;
    float fieldRadius = (float)(radiusPrct * FIELD_WIDTH);
    
    //figure out how far we have to go
    int startX, startY, endX, endY;
    startX  = MAX(fieldPos.x - fieldRadius, 0);
    startY  = MAX(fieldPos.y - fieldRadius, 0);
    endX    = MIN(fieldPos.x + fieldRadius + 1, FIELD_WIDTH-1);
    endY    = MIN(fieldPos.y + fieldRadius + 1, FIELD_HEIGHT-1);
    //getFieldBounds(fieldPos, fieldRadius, startX, startY, endX, endY);
    
    
    //some test values
    float strength = 4;
    float baseAngle = 0;
    
    //first find everything that could be inside
    
    for (int x=startX; x < endX; x++){
        for (int y=startY; y< endY; y++){
            
            //for each point get the angle to the center
            float angleToCenter = atan2( x-fieldPos.x, y-fieldPos.y);   //this is the line that fucked it up!
            
            field[x][y].x = cos(angleToCenter) * strength;
            field[x][y].y = sin(angleToCenter) * strength;
            
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


//-------------------------------------------------------------
void VectorField::drawGrid(float alphaPrc){
    
    //these should be set via panel
    gridColor = ofColor::black;
//    gridDrawingAdjust = 15;
//    
//    showVerticalGrid = false;
//    showHorizontalGrid = false;
//    showGridFill = false;
//    
//    useGridWiggle = false;
//    gridWiggleSpeed = 1;
//    gridWiggleStrength = 4;
//    
//    useGridFade = false;
//    gridValThreshold = 0.1;
//    gridValCeiling = 3;
//    
//    useVarryingWidths = false;
//    gridMinLineWidth = 0.5;
//    gridMaxLineWidth = 4;
//    
//    showVerticalGridCurved = true;
//    showHorizontalGridCurved = true;

    ofSetLineWidth(1);
    ofSetColor(gridColor, 255*alphaPrc);
    
    ofVec2f points[FIELD_WIDTH][FIELD_HEIGHT];
    float strengthPrc[FIELD_WIDTH][FIELD_HEIGHT];
    
    float scaleX = (float)externalWidth / (float)FIELD_WIDTH;
    float scaleY = (float)externalHeight / (float)FIELD_HEIGHT;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            
            //figure out where this line will be
            float px = x * scaleX;
            float py = y * scaleY;
            float px2 = px + field[x][y].x * gridDrawingAdjust;
            float py2 = py + field[x][y].y * gridDrawingAdjust;
            
            points[x][y].set(px2, py2);
            
            if (useGridFade || useVarryingWidths || showGridFill){
                if (field[x][y].x != 0 || field[x][y].y != 0){
                    strengthPrc[x][y] = ofMap(field[x][y].length(), gridValThreshold, gridValCeiling, 0, 1, true);
                }else{
                    strengthPrc[x][y] = 0;
                }
            }
            
            if (useGridWiggle){
                points[x][y].x += ofNoise( ofGetElapsedTimef()*gridWiggleSpeed, x, y ) * gridWiggleStrength;
                points[x][y].y += ofNoise( ofGetElapsedTimef()*gridWiggleSpeed, x, y ) * gridWiggleStrength;
            }
            
            
            
        }
    }
    
    //connect all of these bastards
    for (int x=1; x<FIELD_WIDTH; x++){
        for (int y=1; y<FIELD_HEIGHT; y++){
            ofVec2f anchor = points[x][y];
            if (showHorizontalGrid){
                float alphaVal = 1;
                float lineWidth = 1;
                if (useGridFade){
                    alphaVal = MAX(strengthPrc[x][y], strengthPrc[x-1][y]);
                }
                if (useVarryingWidths){
                    lineWidth = ofMap( MAX(strengthPrc[x][y], strengthPrc[x-1][y]), 0 , 1, gridMinLineWidth, gridMaxLineWidth);
                }
                if (alphaVal > 0 && lineWidth > 0){
                    ofSetColor(gridColor, 255*alphaPrc*alphaVal);
                    ofSetLineWidth(lineWidth);
                    ofLine(anchor, points[x-1][y]);
                }
            }
            if (showVerticalGrid){
                float alphaVal = 1;
                float lineWidth = 1;
                if (useGridFade){
                    alphaVal = MAX(strengthPrc[x][y], strengthPrc[x][y-1]);
                }
                if (useVarryingWidths){
                    lineWidth = ofMap( MAX(strengthPrc[x][y], strengthPrc[x-1][y]), 0 , 1, gridMinLineWidth, gridMaxLineWidth);
                }
                if (alphaVal > 0 && lineWidth > 0){
                    ofSetColor(gridColor, 255*alphaPrc*alphaVal);
                    ofSetLineWidth(lineWidth);
                    ofLine(anchor, points[x][y-1]);
                }
            }
            
            if (showGridFill){
                float fillAlphaPrc = (strengthPrc[x][y] + strengthPrc[x-1][y] + strengthPrc[x][y-1] + strengthPrc[x-1][y-1]) / 4.0f;
                if (fillAlphaPrc > 0){
                    ofSetColor(gridColor, 255*alphaPrc*fillAlphaPrc);
                    ofFill();
                    ofBeginShape();
                    ofVertex(points[x][y].x, points[x][y].y);
                    ofVertex(points[x-1][y].x, points[x-1][y].y);
                    ofVertex(points[x-1][y-1].x, points[x-1][y-1].y);
                    ofVertex(points[x][y-1].x, points[x][y-1].y);
                    ofEndShape();
                }
            }
        }
    }
    
    //curved line?
    if (showVerticalGridCurved){
        ofNoFill();
        for (int x=0; x<FIELD_WIDTH; x++){
            ofBeginShape();
            for (int y=1; y<FIELD_HEIGHT; y++){
                ofCurveVertex(points[x][y].x, points[x][y].y);
            }
            ofEndShape();
        }
    }
    if (showHorizontalGridCurved){
        ofNoFill();
        for (int y=0; y<FIELD_HEIGHT; y++){
            ofBeginShape();
            for (int x=1; x<FIELD_WIDTH; x++){
                ofCurveVertex(points[x][y].x, points[x][y].y);
            }
            ofEndShape();
        }
    }
    
}





