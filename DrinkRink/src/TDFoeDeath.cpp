//
//  TDFoeDeath.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFoeDeath.h"


void TDFoeDeath::steup(TDFoe * parent){
    
    anims = parent->anims;
    type = parent->type;
    pos = parent->pos;
    angle = parent->displayAngle;
    
    timer = 0;
    curFrame = 0;
    
    frameTime = 0.1;
    
    killMe = false;
    
}

void TDFoeDeath::update(float deltaTime){
    timer += deltaTime;
    
    if (timer > frameTime){
        timer -= frameTime;
        if (curFrame < anims->deathCycleLength[type]-1){
            curFrame++;
        }else{
            killMe = true;
        }
        
    }
    
}

void TDFoeDeath::draw(float alphaPrc){
    
    ofSetColor(255 * alphaPrc);
    ofPushMatrix();
    
    ofTranslate(pos.x, pos.y);
    ofRotate(ofRadToDeg(angle) - 90);   //remove this tweak once the images are facing the right way
    
    ofImage * thisPic = &anims->deathCycles[type][curFrame];
    thisPic->draw(-thisPic->getWidth()/2, -thisPic->getHeight()/2);
    
    ofPopMatrix();
    
}