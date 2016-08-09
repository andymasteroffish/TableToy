//
//  TowerPrism.cpp
//  DrinkRink
//
//  Created by Anthony on 6/28/16.
//
//

#include "TowerPrism.h"


#include "TowerPrism.h"

void TowerPrism::customSetup(){
    pos.x = 0;
    pos.y = ofGetHeight()/2;
    targetAngle = 0;

}

void TowerPrism::customUpdate(){
    
}

void TowerPrism::customDraw(float alphaPrc){
    
    if (lightCount > 0 || isSource) {
        isLit = true;
    } else {
        isLit = false;
    }
    
    //if(!isSource && isLit) cout<< "IM NOT SOURCE BUT LIT" << endl;
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate( ofRadToDeg(targetAngle));
    
    //How the tower actually looks
    ofSetColor(255, 255, 255);
    ofCircle(0, 0, towerSize);
    
    //Draw Beam
    if (isLit) {
        beam.customDraw();
    }
    
    //Debug
    ofSetColor(0, 0, 0);
    ofLine(0, 0, towerSize, 0);
    
    ofPopMatrix();
    
}