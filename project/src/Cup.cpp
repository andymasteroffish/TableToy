//
//  Cup.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "Cup.h"


void Cup::setup(float startX, float startY, VectorField * _field){
    
    angle = 0;
    
    pos.set(startX, startY);
    field = _field;
    
    hasBeenRemoved = false;
    
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
    
    radius = 30;    //how big the physical cup is
    
    
    customSetup();
}

void Cup::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    customUpdate();
}

void Cup::draw(){
    
    customDraw();
    
    //show a debug cup image
    ofSetColor(debugColor);
    ofCircle(pos.x, pos.y, radius);
    ofSetColor(0);
    ofLine(pos.x, pos.y, pos.x+cos(angle)*radius*0.8, pos.y+sin(angle)*radius*0.8);
}

void Cup::onMouseDown(int x, int y, int button){
    if ( ofDistSquared(x,y, pos.x, pos.y) < radius*radius){
        
        if (button == 0){
            isDebugSelected = true;
            distFromMouseWhenSelected.x = pos.x - x;
            distFromMouseWhenSelected.y = pos.y - y;
        }
        if (button == 2) {
            isDebugSelectedForAngle = true;
        }
    }
}
void Cup::onMouseDrag(int x, int y, int button){
    if (isDebugSelected){
        pos.x = x + distFromMouseWhenSelected.x;
        pos.y = y + distFromMouseWhenSelected.y;
    }
    
    if (isDebugSelectedForAngle){
        angle = atan2( y-pos.y, x-pos.x);
    }
    
}
void Cup::onMouseRelease(int x, int y, int button){
    isDebugSelected = false;
    isDebugSelectedForAngle = false;
}