//
//  SportsScene.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "SportsScene.h"


// comparison routine for sorting
bool ballSort(  Ball * a, Ball * b ) {
    return a->pos.x < b->pos.x;
}


//--------------------------------------------------------------------------------------------
void SportsScene::setupCustom(){
    
    numFieldParticlesPerFrame = 15;
    
    ballRepulsionRange = 30;
    ballRepulsionMaxForce = 1;
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].setup(i==0, &field);
    }
    
    maxNumBalls = 15;
    timeBetweenBallSpawns = 1;
    
    nextBallSpawnsOnTop = true; //this just flips with each spawn
    
    sceneName = "sports";
    sceneToSwitchTo = 2;    //stream
    
    gameOverCupShrinkTime = 2;
    gameOverTimetoSwitchScene = 12;
    
    ballColor.setHsb(212, 114, 242);
    
    bgCol.set(250,249,240);
    defaultParticleType =  PARTICLE_SPORT;
    
    ignorePanelValues = true;
}


//--------------------------------------------------------------------------------------------
//clears everything and gets the toy ready for a new round
void SportsScene::resetCustom(){
    
    
    //kill all balls if there are any
    for (int i=0; i<balls.size(); i++){
        delete balls[i];
    }
    balls.clear();
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].reset();
    }
    
    
    ballSpawnTimer = 0;
    
    gameOver = false;
    gameOverTimer = 0;
    
    winFillEffect.setup();
}


//--------------------------------------------------------------------------------------------
void SportsScene::updateCustom(){
    
    //put an outward force on the edges to keep balls from getting stuck
    float bumperRange = 8;
    float bumperStrength = 0.5;
    float bumerParticleWeight = 1;
    
    addOutwardCircle(GridPos(-1, -1), bumperRange, bumperStrength, PARTICLE_GOAL_LEFT, bumerParticleWeight);
    addOutwardCircle(GridPos(-1, field.fieldHeight+1), bumperRange, bumperStrength, PARTICLE_GOAL_LEFT, bumerParticleWeight);
    addOutwardCircle(GridPos(field.fieldWidth+1, -1), bumperRange, bumperStrength, PARTICLE_GOAL_RIGHT, bumerParticleWeight);
    addOutwardCircle(GridPos(field.fieldWidth+1, field.fieldHeight+1), bumperRange, bumperStrength, PARTICLE_GOAL_RIGHT, bumerParticleWeight);
    
    
    //update goals
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].update(deltaTime);
        if (!gameOver && goals[i].hasWon){
            triggerGameOver();
        }
    }
    
    //spawn balls?
    ballSpawnTimer += deltaTime;
    if (ballSpawnTimer > timeBetweenBallSpawns && balls.size() < maxNumBalls && !gameOver){
        spawnBall();
    }
    
    //sort the balls from left to right
    sort(balls.begin(), balls.end(), ballSort );
    
    //actually update the balls
    for (int i=balls.size()-1; i>=0; i--){
        
        //for each ball, get the repulsion form any nearby balls
        for (int j= i-1; j >= 0; j--){
            //stop chekcing if we're out of range
            if ( fabs(balls[j]->pos.x - balls[i]->pos.x) > ballRepulsionRange){
                break;
            }
            balls[i]->addRepulsionForce(balls[j], ballRepulsionRange, ballRepulsionMaxForce);
        }
        
        balls[i]->update(&field);
        
        //ready to die in a goal?
        for (int g=0; g<NUM_GOALS; g++){
            if (goals[g].checkIsBallDead(balls[i])){
                killBall(i, g);
            }
        }
    }
    
    //and the particles
    for (int i=ballParticles.size()-1; i>=0; i--){
        ballParticles[i].update(deltaTime);
        if (ballParticles[i].timer > ballParticles[i].killTime){
            ballParticles.erase( ballParticles.begin()+i );
        }
    }
    
    
    //game over effect
    if (gameOver){
        gameOverTimer += deltaTime;
        
        float towerRangePrc = 1 - gameOverTimer/gameOverCupShrinkTime;
        towerRangePrc = MAX(0, towerRangePrc);
        for (int i=0; i<towers.size(); i++){
            if (towers[i]->range > 0){
                towers[i]->range = towers[i]->startingRange * towerRangePrc;
                towers[i]->calculateFieldRange();
            }
        }
        
        winFillEffect.update(deltaTime);
        
        if (gameOverTimer >= gameOverTimetoSwitchScene){
            switchScenesFlag = true;
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void SportsScene::checkPanelValuesCustom(ofxControlPanel *panel){
    if (ignorePanelValues){
        return;
    }
    
    ballColor.setHsb(panel->getValueF("BALL_HUE"), panel->getValueF("BALL_SAT"), panel->getValueF("BALL_BRI"));
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].checkPanelValues(panel);
    }
}

//--------------------------------------------------------------------------------------------
void SportsScene::drawCustom(){
    
    //don't draw the main game if we're doing the scene switch off
    if (gameOverTimer < gameOverTimetoSwitchScene){
        for (int i=0; i<NUM_GOALS; i++){
            goals[i].draw(alphaPrc);
        }
        
        //draw balls
        ofFill();
//        ofSetupScreenOrtho(ofGetWidth(), ofGetHeight(), -100, 100); //for fun 3d effect
        ofEnableDepthTest();
        for (int i=0; i<balls.size(); i++){
            balls[i]->draw(alphaPrc);
            //ofDrawBitmapString(ofToString(i), balls[i]->pos.x, balls[i]->pos.y-8);
        }
        ofDisableDepthTest();
        

        for (int i=0; i<ballParticles.size(); i++){
            ballParticles[i].draw(alphaPrc);
        }
        ofSetCircleResolution(DEFAULT_CIRCLE_RES); // put the resolution back to default
    }
    
    winFillEffect.draw(alphaPrc);
}


//--------------------------------------------------------------------------------------------
void SportsScene::keyPressed(int key){
    
}

//--------------------------------------------------------------------------------------------
void SportsScene::spawnBall(){
    Ball * newBall = new Ball(nextBallSpawnsOnTop, gameWidth, gameHeight, ballColor);
    balls.push_back(newBall);
    nextBallSpawnsOnTop = !nextBallSpawnsOnTop;
    ballSpawnTimer = 0;
}

//--------------------------------------------------------------------------------------------
void SportsScene::killBall(int idNum, int goalID){
    //add some sparks or some shit
    ofVec2f targetPos = balls[idNum]->pos;
    if (goalID >= 0){
        targetPos = goals[goalID].pos;
    }
    for (int i=0; i<20; i++){
        BallParticle thisParticle;
        thisParticle.setup( *balls[idNum], targetPos);
        ballParticles.push_back(thisParticle);
    }
    
    //remove the ball
    balls.erase( balls.begin() + idNum );
}

//--------------------------------------------------------------------------------------------
void SportsScene::addTower(CupInfo thisCup){
    
    if (thisCup.uniqueID%3 == 0 ){
        TowerRepeller * newTower = new TowerRepeller();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    if (thisCup.uniqueID%3 == 2) {
        TowerFlow * newTower = new TowerFlow();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    if (thisCup.uniqueID%3 == 1) {
        TowerPulse * newTower = new TowerPulse();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    

}



//--------------------------------------------------------------------------------------------
void SportsScene::triggerGameOver(){
    gameOver = true;
    gameOverTimer = 0;
    
    while(balls.size() > 0){
        killBall(0, -1);
    }
    
    //figure out who lost
    if (goals[0].hasWon){
        winFillEffect.start(goals[0]);
        goals[1].hasLost = true;
    }else{
        winFillEffect.start(goals[1]);
        goals[0].hasLost = true;
    }
}



//--------------------------------------------------------------------------------------------
void SportsScene::addOutwardCircle(GridPos fieldPos, float fieldRange, float strength, ParticleType particleType, float particleTypeWeight){
    Bounds bounds = field.getFieldBounds(fieldPos, fieldRange);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(fieldPos.x, fieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < fieldRange){
                float prct = 1.0f - (distance / fieldRange);
                
                ofVec2f dif;
                dif.x = (x - fieldPos.x);
                dif.y = (y - fieldPos.y);
                dif.normalize();
                
                field.field[x][y].vel += dif * strength * prct;
                field.field[x][y].addPotentialParticleType(particleType, particleTypeWeight);
            }
        }
    }
}

