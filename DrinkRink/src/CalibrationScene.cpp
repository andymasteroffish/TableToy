//
//  CalibrationScene.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 8/24/15.
//
//

#include "CalibrationScene.h"


//--------------------------------------------------------------------------------------------
void CalibrationScene::setupCustom(){
    sceneName = "calibration";
    
    ignorePanelValues = true;
    bgCol.set(10,30,0);
    
    if (cupTracker->isDebug){
        usingDebug = true;
        return;
    }
    
    usingDebug = false;
    
    tracker = (CupTrackerCam *) cupTracker;
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::resetCustom(){
    if (usingDebug){
        return;
    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::updateCustom(){
    if (usingDebug){
        return;
    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::drawCustom(){
    if (usingDebug){
        ofSetColor(255, 255*alphaPrc);
        ofDrawBitmapString("NO CALIBRATION FOR DEBUG TRACKER", 300, gameHeight/2);
        return;
    }
    
    //show the cam image
    
    float scale = 1;
    float maxHeight = 250;
    if (tracker->fullImg.height > maxHeight){
        scale = maxHeight / (float)tracker->fullImg.height;
    }
    
    ofPushMatrix();
    
    ofTranslate(20, 20);
    ofScale(scale, scale);
    
    ofSetColor(255, 255*alphaPrc);
    tracker->fullImg.draw(0, 0, tracker->fullImg.width, tracker->fullImg.height);
    
    //draw the warp points
    int pointSize = 10;
    int lineSize = pointSize*1.5;
    for (int i=0; i<4; i++){
        
        ofSetColor(255,0,0,255*alphaPrc);
        ofNoFill();
        
        ofPoint pnt = tracker->warpPoints[i];
        
        ofCircle(pnt.x, pnt.y, pointSize);
        
        //draw lines
        ofLine(pnt.x, pnt.y, pnt.x-lineSize, pnt.y);
        ofLine(pnt.x, pnt.y, pnt.x, pnt.y-lineSize);
        ofLine(pnt.x, pnt.y, pnt.x+lineSize, pnt.y);
        ofLine(pnt.x, pnt.y, pnt.x, pnt.y+lineSize);
    }
    
    ofPopMatrix();
    
    //draw the resulting image
    ofPushMatrix();
    ofTranslate(20, gameHeight-tracker->grayImage.height-10);
    
    ofSetColor(255, 255*alphaPrc);
    tracker->grayImage.draw(0, 0);
    tracker->drawFiducials(0, 0);
    
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::keyPressed(int key){
    if (usingDebug){
        return;
    }
}


//--------------------------------------------------------------------------------------------
void CalibrationScene::addTower(CupInfo thisCup){
    if (usingDebug){
        return;
    }
    
    TowerCalibration * newTower = new TowerCalibration();
    newTower->setup( thisCup, &field);
    towers.push_back(newTower);
}