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
    
    drawOffset.set(20, 20);
    
    if (cupTracker->isDebug){
        usingDebug = true;
        return;
    }
    
    controlPanel = NULL;
    
    usingDebug = false;
    
    tracker = (CupTrackerCam *) cupTracker;
    
    curPointDragging = -1;
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
    
    drawScale = 1;
    float maxHeight = 250;
    if (tracker->fullImg.height > maxHeight){
        drawScale = maxHeight / (float)tracker->fullImg.height;
    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mousePressed(int x, int y, int button){
    int adjustedX = x - drawOffset.x;
    int adjustedY = y - drawOffset.y;
    
    int distToClick = 50;
    
    for (int i=0; i<4; i++){
        
        if (ofDist(adjustedX, adjustedY, tracker->warpPoints[i].x*drawScale, tracker->warpPoints[i].y*drawScale) < distToClick){
            cout<<"jesus haunts "<<i<<endl;
            curPointDragging = i;
            draggingOffset.x =  tracker->warpPoints[i].x * drawScale - adjustedX;
            draggingOffset.y =  tracker->warpPoints[i].y * drawScale - adjustedY;
        
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mouseDragged(int x, int y, int button){
    if (controlPanel == NULL){
        cout<<"it not there"<<endl;
        return;
    }
    
    int adjustedX = x - drawOffset.x;
    int adjustedY = y - drawOffset.y;
    
    if (curPointDragging >= 0){
        
        
        float newXVal = CLAMP( (adjustedX+draggingOffset.x)/(tracker->fullImg.width*drawScale) , 0, 1);
        float newYVal = CLAMP( (adjustedY+draggingOffset.y)/(tracker->fullImg.height*drawScale) , 0,1);
        
        controlPanel->setValueF("CAM_WARP_X_"+ofToString(curPointDragging), newXVal);
        controlPanel->setValueF("CAM_WARP_Y_"+ofToString(curPointDragging), newYVal);
    }
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mouseReleased(int x, int y, int button){
    curPointDragging = -1;
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::drawCustom(){
    if (usingDebug){
        ofSetColor(255, 255*alphaPrc);
        ofDrawBitmapString("NO CALIBRATION FOR DEBUG TRACKER", 300, gameHeight/2);
        return;
    }
    
    //show the cam image
    
    ofPushMatrix();
    
    ofTranslate(drawOffset.x, drawOffset.y);
    ofScale(drawScale, drawScale);
    
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
    
    ofSetColor(255,150,150, 255*alphaPrc);
    ofDrawBitmapString("<-- you can drag these points with mouse", drawOffset.x+tracker->fullImg.width*drawScale + 30, gameHeight*0.25);
    
    //draw the resulting image
    ofPushMatrix();
    ofTranslate(80, gameHeight-tracker->grayImage.height*0.75-10);
    
    ofScale(0.75,0.75);
    
    ofSetColor(255, 255*alphaPrc);
    tracker->grayImage.draw(0, 0, tracker->grayImage.width,  tracker->grayImage.height);
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

//--------------------------------------------------------------------------------------------
void CalibrationScene::checkPanelValuesCustom(ofxControlPanel *panel){
    controlPanel = panel;
}
