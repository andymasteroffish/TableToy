//
//  TitleCardScene.cpp
//  emptyExample
//
//  Created by Andy Wallace on 7/2/15.
//
//

#include "TitleCardScene.h"


//--------------------------------------------------------------------------------------------
void TitleCardScene::setupCustom(){
    sceneName = "title_card";
    
    bgCol.set(0,0,0);
    ignorePanelValues = true;
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::updateCustom(){
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::drawBackgroundCustom(){
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::drawCustom(){
    
    ofSetColor(255);
    ofDrawBitmapString("welcome to hell, fuck bird", gameWidth/2, gameHeight/2);
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::keyPressed(int key){
    
}


////--------------------------------------------------------------------------------------------
//void TitleCardScene::addTower(CupInfo thisCup){
//    TowerRock * newTower = new TowerRock();
//    newTower->setup( thisCup, &field);
//    towers.push_back(newTower);
//}
