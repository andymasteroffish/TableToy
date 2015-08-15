//
//  FlyersScene.h
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#ifndef __TabelToy__FlyersScene__
#define __TabelToy__FlyersScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TowerRepeller.h"

#include "Flyer.h"

class FlyersScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);
    
    
    vector<Flyer> flyers;
    
    
};

#endif /* defined(__TabelToy__FlyersScene__) */
