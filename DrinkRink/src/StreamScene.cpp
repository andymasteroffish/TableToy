//
//  StreamScene.cpp
//  emptyExample
//
//  Created by Andy Wallace on 7/2/15.
//
//

#include "StreamScene.h"


//--------------------------------------------------------------------------------------------
void StreamScene::setupCustom(){
    sceneName = "stream";
    
    defaultParticleType =  PARTICLE_STREAM;
    bgCol.set(ofRandom(10),ofRandom(10),ofRandom(10));
    
    numFieldParticlesPerFrame = 25;
    
    //give us some bg shapes
    for (int i=0; i<25; i++){
        StreamBackgroundShape bgShape;
        bgShape.setup(gameWidth, gameHeight);
        bgShapes.push_back(bgShape);
    }
}

//--------------------------------------------------------------------------------------------
void StreamScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    
    panel->addSlider("idle time to kill", "STREAM_IDLE_KILL_TIME", 20, 1, 120, false);
}

//--------------------------------------------------------------------------------------------
void StreamScene::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void StreamScene::checkPanelValuesCustom(ofxControlPanel * panel){
    idleKillTime = panel->getValueF("STREAM_IDLE_KILL_TIME");
}

//--------------------------------------------------------------------------------------------
void StreamScene::updateCustom(){
    setStreamForceOnField();
    
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].update(deltaTime);
    }
    
//    cout<<"timer "<<activeTimer<<endl;
//    cout<<"idle timer "<<idleTimer<<endl;
    
    if (activeTimer > killTime || idleTimer > idleKillTime){
        switchScenesFlag = true;
    }
}

//--------------------------------------------------------------------------------------------
void StreamScene::setStreamForceOnField(){
    float minX = 0.1;
    float maxX = 3;
    
    float yRange = 1;
    
    float noiseScale = 0.5;
    float noiseSpeed = 0.2;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            ofVec2f thisForce;
            
            float xPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed );
            thisForce.x =  xPrc * maxX + (1-xPrc) * minX;
            
            float yPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed, 1000 );
            thisForce.y = yPrc * yRange + (1-yPrc) * (-yRange);
            
            field.field[x][y].vel += thisForce;
        }
    }
}

//--------------------------------------------------------------------------------------------
void StreamScene::drawBackgroundCustom(){
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].draw(alphaPrc);
    }
    ofSetCircleResolution(22);  //return it to default
}

//--------------------------------------------------------------------------------------------
void StreamScene::drawCustom(){
    
}

//--------------------------------------------------------------------------------------------
void StreamScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void StreamScene::addTower(CupInfo thisCup){
    TowerRock * newTower = new TowerRock();
    newTower->setup( thisCup, &field);
    towers.push_back(newTower);
}
