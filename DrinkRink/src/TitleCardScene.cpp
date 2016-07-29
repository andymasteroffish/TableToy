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
    
    fbo.allocate(gameWidth/2, gameHeight);
    
    titleCardPic.loadImage("pic/title_card.png");
    
    killTime = 10;
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::setupPanelValues(ofxControlPanel * panel){
    
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    
    panel->addSlider("Time before moving on", "TITLE_CARD_WAIT_TIME", 10, 1, 60, true);
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::resetCustom(){
    
}


//--------------------------------------------------------------------------------------------
void TitleCardScene::checkPanelValuesCustom(ofxControlPanel * panel){
    killTime = panel->getValueF("TITLE_CARD_WAIT_TIME");
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::updateCustom(){
    
    fbo.begin();
    ofClear(0, 0, 0);
    
    ofSetColor(255);
    titleCardPic.draw(0, 0);
    
    fbo.end();
    
    if (activeTimer >= killTime){
        switchScenesFlag = true;
    }
    
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::drawBackgroundCustom(){
    ofSetColor(255, 255*alphaPrc);
    fbo.draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(gameWidth, gameHeight);
    ofScale(-1, -1);
    fbo.draw(0,0);
    ofPopMatrix();
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::drawCustom(){
    
    ofSetColor(255);
    ofDrawBitmapString("welcome to hell, fuck bird", gameWidth/2-30, gameHeight/2+80);
}

//--------------------------------------------------------------------------------------------
void TitleCardScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void TitleCardScene::addTower(CupInfo thisCup){
    Tower * newTower = new Tower();
    newTower->setup( thisCup, &field);
    newTower->debugColor.set(20, 20, 20);
    towers.push_back(newTower);
}