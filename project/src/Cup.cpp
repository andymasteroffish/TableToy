//
//  Cup.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Cup.h"


void Cup::setup(float startX, float startY, VectorField * _field){
    
    pos.set(startX, startY);
    field = _field;
    
    hasBeenRemoved = false;
    
    isDebugSelected = false;
    
    range = 100;
    radius = 30;
}

void Cup::update(){
    
    customUpdate();
}

void Cup::draw(){
    
    customDraw();
    
    //show a debug cup image
    ofSetColor(0, 230, 80, 220);
    ofCircle(pos.x, pos.y, radius);
}

void Cup::onMouseDown(int x, int y, int button){
    if ( ofDistSquared(x,y, pos.x, pos.y) < radius*radius){
        isDebugSelected = true;
        distFromMouseWhenSelected.x = pos.x - x;
        distFromMouseWhenSelected.y = pos.y - y;
    }
}
void Cup::onMouseDrag(int x, int y, int button){
    if (isDebugSelected){
        pos.x = x + distFromMouseWhenSelected.x;
        pos.y = y + distFromMouseWhenSelected.y;
    }
}
void Cup::onMouseRelease(int x, int y, int button){
    isDebugSelected = false;
}