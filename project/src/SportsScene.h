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
#include "Goal.h"

#include "Tower.h"
#include "TowerRepeller.h"
#include "TowerFlow.h"
#include "TowerPulse.h"

class SportsScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    
    void drawCustom();
    
    void keyPressed(int key);
    
    void spawnBall();
    void killBall(int idNum);
    
    void addTower(CupInfo thisCup);
    
    
    //the balls
    vector<Ball *> balls;
    float ballRepulsionRange;
    float ballRepulsionMaxForce;
    ofColor ballColor;
    
    int maxNumBalls;
    float ballSpawnTimer;
    float timeBetweenBallSpawns;
    bool nextBallSpawnsOnTop;
    
    //goals
#define NUM_GOALS 2
    Goal goals[NUM_GOALS];
    
};

#endif /* defined(__emptyExample__SportsScene__) */
