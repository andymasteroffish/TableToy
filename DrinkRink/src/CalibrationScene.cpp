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
    
    drawOffset.set(20, 10);
    maxDisplayHeight = 230;
    
    if (cupTracker->isDebug){
        usingDebug = true;
        return;
    }
    
    controlPanel = NULL;
    
    usingDebug = false;
    
#ifdef USE_BLOB_DETECTION
    tracker = (CupTrackerBlob *) cupTracker;
#else
    tracker = (CupTrackerCam *) cupTracker;
#endif
    
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
    if (tracker->fullImg.height > maxDisplayHeight){
        drawScale = maxDisplayHeight / (float)tracker->fullImg.height;
    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mousePressed(int x, int y, int button){
    int adjustedX = x - drawOffset.x;
    int adjustedY = y - drawOffset.y;
    
    int distToClick = 50;
    
    for (int i=0; i<4; i++){
        
        if (ofDist(adjustedX, adjustedY, tracker->warpPoints[i].x*drawScale, tracker->warpPoints[i].y*drawScale) < distToClick){
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
    //draw what the camera sees
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
    
    //draw the BG image
    ofSetColor(255);
    tracker->grayBGImage.draw(tracker->fullImg.width+10, tracker->grayBGImage.height*0.5, tracker->grayBGImage.width*0.5, tracker->grayBGImage.height*0.5);
    
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(drawOffset.x+tracker->fullImg.width*drawScale+10, gameHeight*0.04);
    ofSetColor(255,150,150, 255*alphaPrc);
    ofDrawBitmapString("<-- This is the input from the camera(s)", 0, 0);
    ofDrawBitmapString("<-- you can drag these warp points with mouse", 0, 15);
    
    ofDrawBitmapString(".-- This is the background image used for differencing.", 20, 65);
    ofDrawBitmapString("|   It should be the empty table.", 20, 80);
    ofDrawBitmapString("V   If you move the warp points, you need to retake this.", 20, 95);
    ofPopMatrix();
    
    //draw the resulting image
    float outputDrawScale = 1;
    if (tracker->fullImg.height > maxDisplayHeight){
        outputDrawScale = maxDisplayHeight / (float)tracker->imgHeight;
    }
    
    ofPushMatrix();
    ofTranslate(drawOffset.x, gameHeight-tracker->imgHeight*outputDrawScale-10);
    
    ofScale(outputDrawScale,outputDrawScale);
    
    ofSetColor(255, 255*alphaPrc);
    tracker->grayImageDemo.draw(0, 0, tracker->imgWidth,  tracker->imgHeight);
    tracker->grayImageNoThresh.draw(tracker->imgWidth+10, 0, tracker->imgWidth*0.5,  tracker->imgHeight*0.5);
    
    tracker->drawARTags(0, 0);
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(drawOffset.x+tracker->fullImg.width*drawScale+10, gameHeight*0.8);
    ofSetColor(255,150,150, 255*alphaPrc);
    
    ofDrawBitmapString("^-- This is the greyscale differenced image we feed to the tracker", 10, 0);
    
    ofDrawBitmapString("<-- This is the image with the tracker's thresholding applied", 0, 65);
    ofDrawBitmapString("<-- This recreates the image ultimately used for the game", 0, 80);
    ofPopMatrix();
    
    //redraw the towers so we can see them
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw(alphaPrc * 0.5);
    }
    
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
