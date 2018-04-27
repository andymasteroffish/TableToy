//
//  DeepPathScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/20/18.
//
//

#include "DeepPathScene.hpp"

void DeepPathScene::setupCustom(){
    bgCol.set(0,0,0);
    
    sceneName = "deep_path";
    
   
    
    
    
    //set up the camera
    origin.set(0,0,0);
    cam.setTarget(origin);
    
    camPos.set(0, 10, 0);
    camSpeed = 100;
    
//    //and the light
//    areaLight.setup();
//    //areaLight.enable();
//    areaLight.setPointLight();
//    //areaLight.  . setAreaLight(400, 400);
//    float fCol = 1.0;   // 0.1
//    areaLight.setAmbientColor(ofColor(255.0, 255.0, 255.0));
//    areaLight.setAttenuation(1.0,0.0001,0.0001);
//    //areaLight.setAttenuation(0.0001,0.0001,0.0001);
//    areaLight.setDiffuseColor(ofColor(255.0, 255.0, 255.0));
//    areaLight.setSpecularColor(ofColor(255.0, 255.0, 255.0));
    
    
    //create floor tiles
    floorSpacing =  20;
    for (int x=0; x<FLOOR_GRID_WIDTH; x++){
        for (int z=0; z<FLOOR_GRID_DEPTH; z++ ){
            floorPoints[x][z].x = x*floorSpacing - ( (FLOOR_GRID_WIDTH*floorSpacing) /2);
            floorPoints[x][z].z = -z*floorSpacing;
            
            float noiseX = floorPoints[x][z].x + -( (FLOOR_GRID_WIDTH*floorSpacing) /2);
            float noiseZ = abs(floorPoints[x][z].z);
            float minPeak = -100;
            float maxPeak = 10;
            float noiseSpeed = 0.001;
            floorPoints[x][z].y = ofMap(ofNoise(noiseX*noiseSpeed, noiseZ*noiseSpeed),0,1, minPeak, maxPeak);
        }
    }
    curFurthestFloorRow = FLOOR_GRID_DEPTH-1;
    
}

void DeepPathScene::setupPanelValues(ofxControlPanel * panel){
//    panel->addPanel(sceneName, 1, false);
//    panel->setWhichPanel(sceneName);
//    panel->setWhichColumn(0);
    
    
}

void DeepPathScene::resetCustom(){
     cupTracker->useCups = false;
}

void DeepPathScene::checkPanelValuesCustom(ofxControlPanel * panel){
    
}

void DeepPathScene::updateCustom(){
    int closeRow = (curFurthestFloorRow+1)%FLOOR_GRID_DEPTH;
    int nextCloseRow = (closeRow+1)%FLOOR_GRID_DEPTH;
    
    int centerX = FLOOR_GRID_WIDTH/2;
    
    camPos.z -= camSpeed * deltaTime;
    camPos.x = sin(ofGetElapsedTimef()) * 3;
    
    float zPrc = ofMap(camPos.z - floorSpacing, floorPoints[centerX][closeRow].z, floorPoints[centerX][nextCloseRow].z, 0, 1);
    
    //float camXeno = 0.05;
    
    float camHeightAboveGround = 30;
    float heightA = floorPoints[centerX][closeRow].y + camHeightAboveGround;
    float heightB = floorPoints[centerX][nextCloseRow].y + camHeightAboveGround;
    camPos.y =  heightA * (1-zPrc) + heightB * zPrc;
    
    //camPos.y = camPos.y * (1-camXeno) + (floorPoints[centerX][closeRow].y + camHeightAboveGround) * camXeno;
    
    cam.setPosition(camPos);
    
    camLookAtPoint.x = 0;
    camLookAtPoint.z = camPos.z - 20;
    
    int lookAtRow = (closeRow + 2) %FLOOR_GRID_DEPTH;
    int lookAtRowNext = (lookAtRow + 1)%FLOOR_GRID_DEPTH;
    float lookAtHeight = camHeightAboveGround * 0.8;
    
    float lookHeightA =(floorPoints[centerX][lookAtRow].y + lookAtHeight);
    float lookHeightB =(floorPoints[centerX][lookAtRowNext].y + lookAtHeight);
    
    float camLookYTarget = lookHeightA * (1-zPrc) + lookHeightB * zPrc;
    
    float lookYPaddingPrc = 0.15;
    camLookAtPoint.y = camPos.y * lookYPaddingPrc + camLookYTarget * (1-lookYPaddingPrc);
    //camLookAtPoint.y = camLookAtPoint.y * (1-camXeno) + (floorPoints[centerX][lookAtRow].y + camHeightAboveGround*0.8) * camXeno;
    
    
    cam.lookAt(camLookAtPoint);
    
    //check if the closest floor row is behind the camera
    if (floorPoints[0][closeRow].z > camPos.z){
        moveFloorRowToBack(closeRow);
    }
    
}

void DeepPathScene::drawBackgroundCustom(){
    
}

void DeepPathScene::drawCustom(){
    ofEnableDepthTest();
    //ofEnableLighting();
    
    float lineSize = 50;
    
    cam.begin();
    
    
    //draw the floor
    //ofSetColor(30);
    ofSetColor(255,255,255,255*alphaPrc);
    for (int x=0; x<FLOOR_GRID_WIDTH-1; x++){
        for (int z=0; z<FLOOR_GRID_DEPTH-1; z++ ){
            
            int thisRow = curFurthestFloorRow-z;
            if (thisRow < 0) thisRow += FLOOR_GRID_DEPTH;
            
            int nextRow = thisRow-1;
            if (nextRow < 0)    nextRow += FLOOR_GRID_DEPTH;
            
            ofLine(floorPoints[x][thisRow], floorPoints[x+1][thisRow]);
            ofLine(floorPoints[x][thisRow], floorPoints[x][nextRow]);
        }
    }
    
    
    cam.end();
    
    ofDisableDepthTest();
    //ofDisableLighting();
}

void DeepPathScene::keyPressed(int key){
    
}


//--------------------------------------------------------------
void DeepPathScene::moveFloorRowToBack(int row){
    //cout<<"slam row "<<row<<endl;
    
    float newZ = floorPoints[0][curFurthestFloorRow].z - floorSpacing;
    
    //move it all down
    //for (int z=)
    
    for (int x=0; x<FLOOR_GRID_WIDTH; x++ ){
        floorPoints[x][row].z = newZ;
        
        float noiseX = floorPoints[x][row].x + -( (FLOOR_GRID_WIDTH*floorSpacing) /2);
        float noiseZ = abs(newZ);
        float minPeak = -100;
        float maxPeak = 10;
        float noiseSpeed = 0.001;
        floorPoints[x][row].y = ofMap(ofNoise(noiseX*noiseSpeed, noiseZ*noiseSpeed),0,1, minPeak, maxPeak);
    }
    
    curFurthestFloorRow = row;
}
