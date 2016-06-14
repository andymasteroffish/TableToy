//
//  TowerDefenseScene.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "TowerDefenseScene.h"


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setupCustom(){
    sceneName = "tower defense";
    
    playerHealth = 3;
    
    //gameW 2560
    //gameH 800
    path.clear();
    path.resize(8);
    path[0].set(100,200);
    path[1].set(500,200);
    path[2].set(500,600);
    path[3].set(1110,600);
    path[4].set(1110,250);
    path[5].set(2200,250);
    path[6].set(2200,400);
    path[7].set(2400,400);
    
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::resetCustom(){
    
    //clear out any old foes
    while(foes.size() > 0){
        delete foes[0];
        foes.erase(foes.begin());
    }
    
    //make some demo foes
    for (int i=0; i<20; i++){
        TDFoe * newFoe = new TDFoe();
        newFoe->setup(&path, i*2);
        foes.push_back(newFoe);
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::updateCustom(){
    
    for (int i=foes.size()-1; i>=0; i--){
        foes[i]->update(deltaTime);
        
        if (foes[i]->reachedTheEnd){
            takeDamage();
            foes[i]->killMe = true;    //remove the foe
        }
        
        //check if the foe died
        if (foes[i]->killMe){
            delete foes[i];
            foes.erase( foes.begin()+i );
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::drawCustom(){
    
    //debug draw the path
    ofSetColor(20);
    for (int i=0; i<path.size(); i++){
        if (i>0){
            ofLine(path[i], path[i-1]);
        }
        ofCircle(path[i].x, path[i].y, 10);
    }
    
    //draw the foes
    for (int i=0; i<foes.size(); i++){
        foes[i]->draw();
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::addTower(CupInfo thisCup){
//    TowerRepeller * newTower = new TowerRepeller();
//    newTower->setup( thisCup, &field);
//    newTower->repelStrength *= 1.5;
//    towers.push_back(newTower);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::takeDamage(){
    playerHealth--;
}
