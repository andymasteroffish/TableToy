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
#include "ofxCameraFilter.h"

class BeamScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);

private:
    ofxCameraFilter filter;
    ofxControlPanel * myPanel;
    bool checkForHit(TowerPrism candidate, TowerPrism thisPrism);

    
};
