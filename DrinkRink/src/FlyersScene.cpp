//
//  FlyersScene.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "FlyersScene.h"


//--------------------------------------------------------------------------------------------
void FlyersScene::setupCustom(){
    sceneName = "flyers";
}

//--------------------------------------------------------------------------------------------
void FlyersScene::resetCustom(){
    
    flyers.clear();
    
    for (int i=0; i<100; i++){
        Flyer testo;
        testo.setup(&field);
        
        flyers.push_back(testo);
    }
    
}

//--------------------------------------------------------------------------------------------
void FlyersScene::updateCustom(){
    
    //have all flyers push eachother
    for (int i=0; i<flyers.size(); i++){
        for (int j=0; j<flyers.size(); j++){
            flyers[i].addRepulsionForce(&flyers[j]);
        }
    }
    
    //update the flyers
    for (int i=flyers.size()-1; i>=0; i--){
        flyers[i].update(deltaTime);
        if (flyers[i].needsTower && towers.size() > 0){
            int idNum = ofRandom(towers.size());
            flyers[i].setTower(towers[idNum]);
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void FlyersScene::drawCustom(){
    for (int i=0; i<flyers.size(); i++){
        flyers[i].draw(alphaPrc);
    }
}

//--------------------------------------------------------------------------------------------
void FlyersScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void FlyersScene::addTower(CupInfo thisCup){
    TowerRepeller * newTower = new TowerRepeller();
    newTower->setup( thisCup, &field);
    newTower->repelStrength *= 1.5;
    towers.push_back(newTower);
}
