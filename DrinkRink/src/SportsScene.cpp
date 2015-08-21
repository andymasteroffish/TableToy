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
    
    ballRepulsionRange = 30;
    ballRepulsionMaxForce = 1;
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].setup(i==0, &field);
    }
    
    maxNumBalls = 15;
    timeBetweenBallSpawns = 1;
    
    nextBallSpawnsOnTop = true; //this just flips with each spawn
    
    sceneName = "sports";
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
    
}


//--------------------------------------------------------------------------------------------
void SportsScene::updateCustom(){
    
    //update goals
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].update(deltaTime);
    }
    
    //spawn balls?
    ballSpawnTimer += deltaTime;
    
    if (ballSpawnTimer > timeBetweenBallSpawns && balls.size() < maxNumBalls){
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
                killBall(i);
            }
        }
    }
    
    
}

//--------------------------------------------------------------------------------------------
void SportsScene::checkPanelValuesCustom(ofxControlPanel *panel){
    ballColor.setHsb(panel->getValueF("BALL_HUE"), panel->getValueF("BALL_SAT"), panel->getValueF("BALL_BRI"));
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].checkPanelValues(panel);
    }
}

//--------------------------------------------------------------------------------------------
void SportsScene::drawCustom(){
    
    
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].draw(alphaPrc);
    }
    
    
    //testing
//    ofSetColor(198,123,233, fadePrc*255);
//    ofFill();
//    for (int i=0; i<balls.size(); i++){
//        ofCircle(balls[i]->pos, ballRepulsionRange/2);
//        balls[i]->draw();
//    }
    
    //draw balls
    ofSetColor(ballColor, alphaPrc*255);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        balls[i]->draw();
        //ofDrawBitmapString(ofToString(i), balls[i]->pos.x, balls[i]->pos.y-8);
    }
}


//--------------------------------------------------------------------------------------------
void SportsScene::keyPressed(int key){
    if (key == 'r'){
        for (int i=0; i<balls.size(); i++){
            balls[i]->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        }
    }
}

//--------------------------------------------------------------------------------------------
void SportsScene::spawnBall(){
    Ball * newBall = new Ball(nextBallSpawnsOnTop);
    balls.push_back(newBall);
    nextBallSpawnsOnTop = !nextBallSpawnsOnTop;
    ballSpawnTimer = 0;
}

//--------------------------------------------------------------------------------------------
void SportsScene::killBall(int idNum){
    //add some sparks or some shit
    
    //remove the ball
    balls.erase( balls.begin() + idNum );
}

//--------------------------------------------------------------------------------------------
void SportsScene::addTower(CupInfo thisCup){
    
    if (thisCup.uniqueID == 0 || thisCup.uniqueID > 2){
        TowerRepeller * newTower = new TowerRepeller();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    if (thisCup.uniqueID == 1) {
        TowerFlow * newTower = new TowerFlow();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    if (thisCup.uniqueID == 2) {
        TowerPulse * newTower = new TowerPulse();
        newTower->setup( thisCup, &field);
        towers.push_back(newTower);
    }
    

}


