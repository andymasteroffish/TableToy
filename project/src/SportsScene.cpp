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
    
    
    //make some balls! SPORTS!
    for (int i=0; i<20; i++){
        Ball * newBall = new Ball();
        newBall->setup();
        newBall->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        balls.push_back(newBall);
    }
    
}


//--------------------------------------------------------------------------------------------
void SportsScene::updateCustom(){
    
    //update goals
    for (int i=0; i<NUM_GOALS; i++){
        goals[i].update(deltaTime);
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
        
    }
    
    
    
    
    
}

//--------------------------------------------------------------------------------------------
void SportsScene::checkPanelValuesCustom(ofxControlPanel *panel){
    ballColor.setHsb(panel->getValueF("BALL_HUE"), panel->getValueF("BALL_SAT"), panel->getValueF("BALL_BRI"));
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
void SportsScene::addTower(CupInfo thisCup){
    
    if (thisCup.typeID == 0 || thisCup.typeID > 2){
        TowerRepeller * newTower = new TowerRepeller();
        newTower->setup( thisCup, &field);
        newTower->debugColor = cupDebugColors[0];
        towers.push_back(newTower);
    }
    if (thisCup.typeID == 1) {
        TowerFlow * newTower = new TowerFlow();
        newTower->setup( thisCup, &field);
        newTower->debugColor = cupDebugColors[1];
        towers.push_back(newTower);
    }
    if (thisCup.typeID == 2) {
        TowerPulse * newTower = new TowerPulse();
        newTower->setup( thisCup, &field);
        newTower->debugColor = cupDebugColors[2];
        towers.push_back(newTower);
    }
    

}


//--------------------------------------------------------------------------------------------
void SportsScene::readXMLCustom(ofxXmlSettings xml){
    ballColor.setHex( stringToHex( xml.getValue("BALLS", "ffffff")) );

    int cupDebugColorNum = 0;
    string cupDebugColorName = "CUPDEBUG"+ofToString(cupDebugColorNum);
    while (xml.tagExists(cupDebugColorName)){
        ofColor thisCol;
        thisCol.setHex( stringToHex( xml.getValue(cupDebugColorName, "ffffff")) );
        thisCol.a = cupDebugAlpha;
        cupDebugColors.push_back(thisCol);
        cupDebugColorNum++;
        cupDebugColorName = "CUPDEBUG"+ofToString(cupDebugColorNum);
    }
}






