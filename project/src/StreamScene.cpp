//
//  StreamScene.cpp
//  emptyExample
//
//  Created by Andy Wallace on 7/2/15.
//
//

#include "StreamScene.h"


//--------------------------------------------------------------------------------------------
void StreamScene::setupCustom(){
    sceneName = "Stream";
}

//--------------------------------------------------------------------------------------------
void StreamScene::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void StreamScene::updateCustom(){
    setStreamForceOnField();
}

//--------------------------------------------------------------------------------------------
void StreamScene::setStreamForceOnField(){
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
            
            field.field[x][y] += thisForce;
        }
    }
}

//--------------------------------------------------------------------------------------------
void StreamScene::drawCustom(){
    
}

//--------------------------------------------------------------------------------------------
void StreamScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void StreamScene::addTower(CupInfo thisCup){
    TowerRock * newTower = new TowerRock();
    newTower->setup( thisCup, &field);
    towers.push_back(newTower);
}