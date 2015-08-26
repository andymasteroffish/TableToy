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
    //fuck the background setting, just black out the whole thing
    ofSetColor(10,30,0);
    ofFill();
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    
    if (usingDebug){
        ofSetColor(255);
        ofDrawBitmapString("NO CALIBRATION FOR DEBUG TRACKER", 300, ofGetHeight()/2);
        return;
    }
    
    //show the cam image
    
    ofPushMatrix();
    
    ofTranslate(20, 20);
    
    ofSetColor(255);
    tracker->fullImg.draw(0, 0, tracker->fullImg.width, tracker->fullImg.height);
    
    //draw the warp points
    int pointSize = 10;
    int lineSize = pointSize*1.5;
    for (int i=0; i<4; i++){
        
        ofSetColor(255,0,0);
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
    ofTranslate(20, ofGetHeight()-tracker->grayImage.height-10);
    
    ofSetColor(255);
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
    
    //no towers for this guy just yet
}
