//
//  StreamBlobScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#include "StreamBlobScene.hpp"



//--------------------------------------------------------------------------------------------
void StreamBlobScene::setupCustom(){
    sceneName = "stream_blob";
    
    defaultParticleType =  PARTICLE_STREAM;
    bgCol.set(ofRandom(10),ofRandom(10),ofRandom(10));
    
    numFieldParticlesPerFrame = 25;
    
    //give us some bg shapes
    for (int i=0; i<25; i++){
        StreamBackgroundShape bgShape;
        bgShape.setup(gameWidth, gameHeight);
        bgShapes.push_back(bgShape);
    }
    
    drawDebugBobs = false;
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    panel->addSlider("blob force", "STREAM_BLOB_FORCE", 0.4, 0, 2, false);
    panel->addToggle("show contours", "STREAM_SHOW_BLOBS", false);
    
    //panel->addSlider("kill time", "STREAM_KILL_TIME", 60, 1, 500, false);
    //panel->addSlider("idle time to kill", "STREAM_IDLE_KILL_TIME", 20, 1, 120, false);
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::checkPanelValuesCustom(ofxControlPanel * panel){
    killTime = panel->getValueF("STREAM_KILL_TIME");
    blobForce = panel->getValueF("STREAM_BLOB_FORCE");
    drawDebugBobs = panel->getValueB("STREAM_SHOW_BLOBS");
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::updateCustom(){
    setStreamForceOnField();
    
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
            field.field[fieldX][fieldY].vel += normalized * blobForce;;
        }

    }
    
    
    //background
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].update(deltaTime);
    }
    
    
    if (activeTimer > killTime ){
        switchScenesFlag = true;
    }
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::setStreamForceOnField(){
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
void StreamBlobScene::drawBackgroundCustom(){
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].draw(alphaPrc);
    }
    ofSetCircleResolution(22);  //return it to default
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::drawCustom(){
    
    if (drawDebugBobs){
        for (int i=0; i<cupTracker->blobs.size(); i++){

            cupTracker->blobs[i].draw();
        }
    }
    
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::keyPressed(int key){
    
}
