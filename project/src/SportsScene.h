//
//  SportsScene.h
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#ifndef __emptyExample__SportsScene__
#define __emptyExample__SportsScene__

#include "ofMain.h"
#include "Scene.h"
#include "Ball.h"

#include "Tower.h"
#include "TowerRepeller.h"
#include "TowerFlow.h"
#include "TowerPulse.h"

class SportsScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    void checkCups();
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void makeFieldParticles();
    
    void addTower(CupInfo thisCup);
    
    
    
    //the balls
    vector<Ball *> balls;
    float ballRepulsionRange;
    float ballRepulsionMaxForce;
    
};

#endif /* defined(__emptyExample__SportsScene__) */
