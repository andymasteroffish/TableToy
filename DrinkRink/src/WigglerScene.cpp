//
//  WigglerScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/1/18.
//
//

#include "WigglerScene.hpp"



//--------------------------------------------------------------------------------------------
void WigglerScene::setupCustom(){
    sceneName = "wiggler";
    
    defaultParticleType =  PARTICLE_WIGGLER;
    bgCol.setHsb(131, 18, 50);
    
    numFieldParticlesPerFrame = 100;
    
    bgShapes.resize(40);
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].setup(gameWidth, gameHeight);
    }
    
}

//--------------------------------------------------------------------------------------------
void WigglerScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    panel->addSlider("blob force", "WIGGLER_BLOB_FORCE", 0.4, 0, 4, false);
    panel->addSlider("num particles per frame", "WIGGLER_PARTICLE_NUM", 100, 10, 200, false);
    
    panel->addSlider("fric", "WIGGLER_FRIC", 0.36, 0, 1, false);
    panel->addSlider("wiggle range", "WIGGLER_RANGE", 1.0, 0, TWO_PI, false);
    panel->addSlider("wiggle power", "WIGGLER_POWER", 0.32, 0, 1, false);
    panel->addSlider("wiggle rate", "WIGGLER_RATE", 1.0, 0, 5, false);
    
    panel->addSlider("particle kill time", "WIGGLER_TIME", 6, 0, 10, false);
    
    
}

//--------------------------------------------------------------------------------------------
void WigglerScene::resetCustom(){
    cupTracker->useCups = false;
    
}

//--------------------------------------------------------------------------------------------
void WigglerScene::checkPanelValuesCustom(ofxControlPanel * panel){
    
    blobForce = panel->getValueF("WIGGLER_BLOB_FORCE");
    
    numFieldParticlesPerFrame = panel->getValueF("WIGGLER_PARTICLE_NUM");
    
    particleFric = panel->getValueF("WIGGLER_FRIC");
    
    particleWiggleRange = panel->getValueF("WIGGLER_RANGE");
    particleWigglePower = panel->getValueF("WIGGLER_POWER");
    particleWiggleRate = panel->getValueF("WIGGLER_RATE");
    
    particleKillTime = panel->getValueF("WIGGLER_TIME");
}

//--------------------------------------------------------------------------------------------
void WigglerScene::updateCustom(){
    //update particles
    for (int i=0; i<fieldParticles.size(); i++){
        fieldParticles[i]->fric = particleFric;
        
        fieldParticles[i]->noiseWiggleRange = particleWiggleRange;
        fieldParticles[i]->noiseWigglePower = particleWigglePower;
        fieldParticles[i]->noiseWiggleRate = particleWiggleRate;
        
        fieldParticles[i]->killTime = particleKillTime;
    }
    
    //blobs
    for (int i=0; i<cupTracker->blobs.size(); i++){
        
        for (int k=0; k<cupTracker->blobs[i].points.size(); k++){
            ofVec2f pnt;
            pnt.x =  cupTracker->blobs[i].points[k].x;
            pnt.y =  cupTracker->blobs[i].points[k].y;
            
            //for each of these points, calculate the field position
            float xPrc = pnt.x / (float)gameWidth;
            float yPrc = pnt.y / (float)gameHeight;
            
            //get the X and Y of the field
            int fieldX = field.fieldWidth * xPrc;
            int fieldY = field.fieldHeight * yPrc;
            
            //cout<<"field size "<<field.fieldWidth<<","<<field.fieldHeight<<endl;
            //cout<<"field pos "<<fieldX<<","<<fieldY<<endl;
            
            ofVec2f normalized = pnt - cupTracker->blobs[i].center;
            normalized.normalize();
            
            //ofVec2f force(0,1);
            field.field[fieldX][fieldY].vel += normalized * 30;
        }
        
    }
    
    //background
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].update(deltaTime);
    }
}


//--------------------------------------------------------------------------------------------
void WigglerScene::drawBackgroundCustom(){
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].draw(alphaPrc);
    }
}

//--------------------------------------------------------------------------------------------
void WigglerScene::drawCustom(){
    
    
    
}

//--------------------------------------------------------------------------------------------
void WigglerScene::keyPressed(int key){
    
}