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


void SportsScene::setupCustom(){
    field.setupField(ofGetWidth(),ofGetHeight());
    
    ballRepulsionRange = 20;
    ballRepulsionMaxForce = 1;
    
    //testing
//    for (int i=0; i<5; i++){
//        CupInfo thisInfo;
//        addCup(thisInfo);
//    }
}


//clears everythign and gets the toy ready for a new round
void SportsScene::resetCustom(){
    
    //kill all cups if there are any
    for (int i=0; i<cups.size(); i++){
        delete cups[i];
    }
    cups.clear();
    
    //kill all balls if there are any
    for (int i=0; i<balls.size(); i++){
        delete balls[i];
    }
    balls.clear();
    
    
    
    for (int i=0; i<20; i++){
        Ball * newBall = new Ball();
        newBall->setup();
        newBall->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        balls.push_back(newBall);
    }
    
    
}



void SportsScene::updateCustom(){
    field.clear();
    
    //sort the balls from left to right
    sort(balls.begin(), balls.end(), ballSort );
    
    //have the cups do their thing on the field
    for (int i=cups.size()-1; i>=0; i--){
        cups[i]->update(deltaTime);
    }
    
    //actually update the balls
    for (int i=balls.size()-1; i>=0; i--){
        //cout<<"ball "<<i<<" vel "<<balls[i].vel.x<<" , "<<balls[i].vel.y<<endl;
        
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
    
    //update the field particles
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->update(deltaTime, &field);
        if (fieldParticles[i]->killFlag){
            delete fieldParticles[i];
            fieldParticles.erase( fieldParticles.begin() + i);
        }
    }
    
    
    makeFieldParticles();
}


void SportsScene::drawCustom(){
    for (int i=cups.size()-1; i>=0; i--){
        cups[i]->draw();
    }
    
    //testing
    ofSetColor(198,123,233);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        ofCircle(balls[i]->pos, ballRepulsionRange/2);
        balls[i]->draw();
    }
    
    //draw balls
    ofSetColor(233,123,180);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        balls[i]->draw();
        ofDrawBitmapString(ofToString(i), balls[i]->pos.x, balls[i]->pos.y-8);
    }
}


void SportsScene::keyPressed(int key){
    if (key == 'r'){
        for (int i=0; i<balls.size(); i++){
            balls[i]->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        }
    }
}

void SportsScene::makeFieldParticles(){
    vector<ofVec2f> gridPosAffectedThisFrame;
    float minStrengthToCount = 0.01;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            if ( abs(field.field[x][y].x) > minStrengthToCount || abs(field.field[x][y].y > minStrengthToCount) ){
                gridPosAffectedThisFrame.push_back( field.getExternalPointFromInternal(x,y) );
            }
        }
    }
    
    if (gridPosAffectedThisFrame.size() == 0){
        return;
    }
    
    
    for (int i=0; i<10; i++){
        ofVec2f thisPos = gridPosAffectedThisFrame[ ofRandom( (int)gridPosAffectedThisFrame.size() )];
        FieldParticle * newP = new FieldParticle( thisPos.x, thisPos.y );
        fieldParticles.push_back(newP);
    }
}

void SportsScene::addCup(CupInfo thisInfo){
    float startX = ofRandom(100, ofGetWidth()-100);
    float startY = ofRandom(100, ofGetHeight()-100);
    
    int rand = (int)ofRandom(3);
    
    if (rand == 0){
        CupRepeller * newTower = new CupRepeller();
        newTower->setup( startX, startY, &field);
        cups.push_back(newTower);
    }
    if (rand == 1) {
        CupFlow * newTower = new CupFlow();
        newTower->setup( startX, startY, &field);
        cups.push_back(newTower);
    }
    if (rand == 2) {
        CupPulse * newTower = new CupPulse();
        newTower->setup( startX, startY, &field);
        cups.push_back(newTower);
    }
    

}






