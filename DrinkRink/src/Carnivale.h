//
//  Carnivale.h
//  DrinkRink
//
//  Created by Anthony on 8/26/15.
//
//

#pragma once

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TowerPrism.h"
#include "Beam.h"

class Carnivale : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
        
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);

private:
    
    vector<TowerPrism> prisms;

    
};
