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

#include "Cup.h"
#include "CupRepeller.h"
#include "CupRock.h"
#include "CupFlow.h"
#include "CupPulse.h"

class SportsScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    void drawCustom();
    
    
    void makeFieldParticles();
    
    void addCup(CupInfo thisInfo);
    
    
    
    //the balls
    vector<Ball *> balls;
    float ballRepulsionRange;
    float ballRepulsionMaxForce;
    
};

#endif /* defined(__emptyExample__SportsScene__) */
