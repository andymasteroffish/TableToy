//
//  Beam.cpp
//  DrinkRink
//
//  Created by Anthony on 6/28/16.
//
//

#include "Beam.h"



void Beam::customSetup(){
    if(endWidth == 0){
        endWidth = startWidth;
    }
  
    
}


void Beam::customDraw(){
    ofPushMatrix();
    ofTranslate(startX, startY);
    ofSetColor(255, 255, 255);
    ofFill();
    ofRect(0, -startWidth/2, bLength, startWidth);
    ofPopMatrix();
    
}

void Beam::customUpdate(){
    
    
    
}

void Beam::calculateBeam(){
    
    
}