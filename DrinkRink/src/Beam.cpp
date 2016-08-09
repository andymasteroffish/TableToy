//
//  Beam.cpp
//  DrinkRink
//
//  Created by Anthony on 6/28/16.
//
//

#include "Beam.h"



void Beam::customSetup(){
  
    
}


void Beam::customDraw(){
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y-beamWidth/2);
    ofSetColor(255, 255, 255);
    ofFill();
    ofRect(0, 0, beamLength, beamWidth);
    ofPopMatrix();
    
}

void Beam::customUpdate(){
    
    
    
}

void Beam::calculateBeam(){
    
    
}