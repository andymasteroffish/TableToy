//
//  FlyersScene.h
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#ifndef __TabelToy__TowerDefenseScene__
#define __TabelToy__TowerDefenseScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TDFoe.h"


class TowerDefenseScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    
    void drawCustom();
    
    void keyPressed(int key);
    
    void addTower(CupInfo thisCup);
    
    void takeDamage();
    
    vector<ofVec2f> path;
    
    vector<TDFoe * > foes;
    
    int playerHealth;

    
    
};

#endif /* defined(__TabelToy__FlyersScene__) */
