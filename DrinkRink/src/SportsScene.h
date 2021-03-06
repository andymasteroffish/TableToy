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
#include "BallParticle.h"
#include "Goal.h"
#include "GoalWinFill.h"

#include "Tower.h"
#include "TowerRepeller.h"
#include "TowerFlow.h"
#include "TowerPulse.h"
#include "TowerPaddle.h"
#include "TowerPopper.h"

class SportsScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void updateCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    
    void drawCustom();
    
    void keyPressed(int key);
    
    void spawnBall();
    void killBall(int idNum, int goalID);
    
    void addTower(CupInfo thisCup);
    
    void triggerGameOver();
    
    void addOutwardCircle(GridPos fieldPos, float fieldRange, float strength, ParticleType particleType, float particleTypeWeight);
    
    
    //the balls
    vector<Ball *> balls;
    vector<BallParticle> ballParticles;
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
    
    bool gameOver;
    float gameOverTimer;
    GoalWinFill winFillEffect;
    
    float gameOverCupShrinkTime;
    float gameOverTimetoSwitchScene;
    
    //killing the scene if nothing is hapenning
    float maxTimeWithoutScoreToEndScene;
    float scoreTimer;
    
};

#endif /* defined(__emptyExample__SportsScene__) */
