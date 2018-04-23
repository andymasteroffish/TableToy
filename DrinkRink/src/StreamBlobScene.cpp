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
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    panel->addSlider("blob force", "STREAM_BLOB_FORCE", 0.4, 0, 2, false);
    
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
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::updateCustom(){
    setStreamForceOnField();
    
    //our blobs (this is super inificient)
    curBlobs.clear();
    float srcImgWidth = 1280 ;
    float srcImgHeight = 480 ;
    
    float newXScale = gameHeight/srcImgHeight;
    float newYScale = gameWidth/srcImgWidth;
    
    for (int i = 0; i < cupTracker->contourFinder.nBlobs; i++){
        StreamBlob blob;
        blob.center.set( cupTracker->contourFinder.blobs[i].centroid.x*newXScale, cupTracker->contourFinder.blobs[i].centroid.y*newYScale);
        
        for (int k=0; k<cupTracker->contourFinder.blobs[i].nPts; k++){
            ofVec2f pnt;
            pnt.x =  cupTracker->contourFinder.blobs[i].pts[k].x * newXScale;
            pnt.y =  cupTracker->contourFinder.blobs[i].pts[k].y * newYScale;
            blob.points.push_back(pnt);
            
            //for each of these points, calculate the field position
            float xPrc = pnt.x / (float)gameWidth;
            float yPrc = pnt.y / (float)gameHeight;
            
            //get the X and Y of the field
            int fieldX = field.fieldWidth * xPrc;
            int fieldY = field.fieldHeight * yPrc;
            
            //cout<<"field size "<<field.fieldWidth<<","<<field.fieldHeight<<endl;
            //cout<<"field pos "<<fieldX<<","<<fieldY<<endl;
            
            ofVec2f normalized = pnt - blob.center;
            normalized.normalize();
            
            //ofVec2f force(0,1);
            field.field[fieldX][fieldY].vel += normalized * blobForce;;
        }
        
        curBlobs.push_back(blob);
        
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
    
    for (int i=0; i<curBlobs.size(); i++){
        curBlobs[i].draw();
    }
    
//    float srcImgWidth = 1280 ;
//    float srcImgHeight = 480 ;
//    
//    float newXScale = gameHeight/srcImgHeight;
//    float newYScale = gameWidth/srcImgWidth;
//    
//    cout<<"new "<<newXScale<<" "<<newYScale<<endl;
//    
//    ofPushMatrix();
//    ofScale(newXScale, newYScale);
//    
//    //blobs
//    ofVec2f blobStart(0,0);
//    for (int i = 0; i < cupTracker->contourFinder.nBlobs; i++){
//        cupTracker->contourFinder.blobs[i].draw(blobStart.x, blobStart.y);
//        
//    }
//    
//    ofPopMatrix();
    
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::keyPressed(int key){
    
}
