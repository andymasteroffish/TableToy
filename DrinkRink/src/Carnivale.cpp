//
//  Carnivale.cpp
//  DrinkRink
//
//  Created by Anthony on 8/26/15.
//
//

#include "Carnivale.h"
#include "TowerPrism.h"


//--------------------------------------------------------------------------------------------
void Carnivale::setupCustom(){
    sceneName = "carnivale";
}

//--------------------------------------------------------------------------------------------
void Carnivale::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void Carnivale::updateCustom(){

}

//--------------------------------------------------------------------------------------------
void Carnivale::drawCustom(){
    
}

//--------------------------------------------------------------------------------------------
void Carnivale::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void Carnivale::addTower(CupInfo thisCup){
    TowerPrism * newTower = new TowerPrism();
    newTower->setup( thisCup, &field);
    towers.push_back(newTower);
}
