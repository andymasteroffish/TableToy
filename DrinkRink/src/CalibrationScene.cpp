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
    
    bgCol.set(10,30,20);
    
    drawOffset.set(20, 10);
    maxDisplayHeight = 230;
    
    if (cupTracker->isDebug){
        usingDebug = true;
        return;
    }
    
    controlPanel = NULL;
    
    usingDebug = false;
    
    tracker = (CupTrackerCam *) cupTracker;
    
    //curPointDragging = -1;
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
//    int adjustedX = x - drawOffset.x;
//    int adjustedY = y - drawOffset.y;
//    
//    int distToClick = 50;
//    
//    for (int i=0; i<4; i++){
//        
//        if (ofDist(adjustedX, adjustedY, tracker->warpPoints[i].x*drawScale, tracker->warpPoints[i].y*drawScale) < distToClick){
//            curPointDragging = i;
//            draggingOffset.x =  tracker->warpPoints[i].x * drawScale - adjustedX;
//            draggingOffset.y =  tracker->warpPoints[i].y * drawScale - adjustedY;
//        
//        }
//    }
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mouseDragged(int x, int y, int button){
    if (controlPanel == NULL){
        cout<<"it not there"<<endl;
        return;
    }
    
//    int adjustedX = x - drawOffset.x;
//    int adjustedY = y - drawOffset.y;
//    
//    if (curPointDragging >= 0){
//        
//        
//        float newXVal = CLAMP( (adjustedX+draggingOffset.x)/(tracker->fullImg.width*drawScale) , 0, 1);
//        float newYVal = CLAMP( (adjustedY+draggingOffset.y)/(tracker->fullImg.height*drawScale) , 0,1);
//        
//        controlPanel->setValueF("CAM_WARP_X_"+ofToString(curPointDragging), newXVal);
//        controlPanel->setValueF("CAM_WARP_Y_"+ofToString(curPointDragging), newYVal);
//    }
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::mouseReleased(int x, int y, int button){
    //curPointDragging = -1;
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
    
    //testing
    //tracker->grayImageNoThresh.draw(0, tracker->fullImg.height*2 + 60, tracker->fullImg.width, tracker->fullImg.height);
    
//    //draw the warp points
//    int pointSize = 10;
//    int lineSize = pointSize*1.5;
//    for (int i=0; i<4; i++){
//        
//        ofSetColor(255,0,0,255*alphaPrc);
//        ofNoFill();
//        
//        ofPoint pnt = tracker->warpPoints[i];
//        
//        ofCircle(pnt.x, pnt.y, pointSize);
//        
//        //draw lines
//        ofLine(pnt.x, pnt.y, pnt.x-lineSize, pnt.y);
//        ofLine(pnt.x, pnt.y, pnt.x, pnt.y-lineSize);
//        ofLine(pnt.x, pnt.y, pnt.x+lineSize, pnt.y);
//        ofLine(pnt.x, pnt.y, pnt.x, pnt.y+lineSize);
//    }
    
    //draw the BG image
    ofSetColor(255);
    tracker->grayBGImage.draw(tracker->fullImg.width+10, tracker->grayBGImage.height*0.5, tracker->grayBGImage.width*0.5, tracker->grayBGImage.height*0.5);
    
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(drawOffset.x+tracker->fullImg.width*drawScale+10, 20);
    ofSetColor(255,0,0, 255*alphaPrc);
    ofDrawBitmapString("<-- This is the input from the camera(s)", 0, 0);
    ofDrawBitmapString("<-- you can drag these warp points with mouse", 0, 15);
    
    ofDrawBitmapString(".-- This is the background image used for differencing.", 20, 65);
    ofDrawBitmapString("|   It should be the empty table.", 20, 80);
    ofDrawBitmapString("V   If you move the warp points, you need to retake this.", 20, 95);
    
    ofDrawBitmapString("screen: "+ofToString(ofGetWidth())+" , "+ofToString(ofGetHeight()), 500, 130);
    ofPopMatrix();
    
    //draw the resulting image
    float outputDrawScale = 1;
    if (tracker->fullImg.height > maxDisplayHeight){
        outputDrawScale = maxDisplayHeight / (float)tracker->imgHeight;
    }
    
    ofPushMatrix();
    ofTranslate(drawOffset.x, 500-tracker->imgHeight*outputDrawScale-10);
    
    ofScale(outputDrawScale,outputDrawScale);
    
    ofSetColor(255, 255*alphaPrc);
    tracker->grayImageDemo.draw(0, 0, tracker->imgWidth,  tracker->imgHeight);
    
    //draw threhsold regions over it
    if (showThresholdGrid){
        ofSetColor(201, 175, 0, 255*alphaPrc);
        ofLine(0, tracker->imgHeight/2, tracker->imgWidth, tracker->imgHeight/2);
        int spacing = tracker->imgWidth/12;
        for (int i=0; i<12; i++){
            int xPos = i*spacing;
            ofLine(xPos, 0, xPos, tracker->imgHeight);
            ofDrawBitmapString( ofToString(i), i*spacing + 5, 30);
            ofDrawBitmapString( ofToString(i+12), i*spacing + 5, tracker->imgHeight/2+30);
        }
    }
    
    ofSetColor(255, 255*alphaPrc);
    
    tracker->grayImageNoThresh.draw(tracker->imgWidth+10, 0, tracker->imgWidth*0.5,  tracker->imgHeight*0.5);
    
    tracker->drawARTags(0, 0);
    
    //trying out drawing the blobs
    //testing blobs
    ofVec2f blobStart(0,0);
    for (int i = 0; i < tracker->contourFinder.nBlobs; i++){
        tracker->contourFinder.blobs[i].draw(blobStart.x, blobStart.y);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        if(tracker->contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole",
                               tracker->contourFinder.blobs[i].boundingRect.getCenter().x + blobStart.x,
                               tracker->contourFinder.blobs[i].boundingRect.getCenter().y + blobStart.y);
        }
    }
    
    ofSetColor(255,0,0);
    ofDrawBitmapString("blobs: "+ofToString(tracker->contourFinder.nBlobs), blobStart.x, blobStart.y+tracker->fullImg.getHeight()+25);
    
    //info text
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(drawOffset.x+tracker->fullImg.width*drawScale+10, 400);
    ofSetColor(255,0,0, 255*alphaPrc);
    
    ofDrawBitmapString("^-- This is the greyscale differenced image we feed to the tracker", 10, 0);
    
    ofDrawBitmapString("<-- This is the image with the tracker's thresholding applied", 0, 65);
    ofDrawBitmapString("<-- This recreates the image ultimately used for the game", 0, 80);
    ofPopMatrix();
    
    //redraw the towers so we can see them
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw(alphaPrc * 0.5, false);
    }
    
    //draw the borders
    ofSetColor(255,0,0);
    ofLine(tracker->cupLeftX,   0, tracker->cupLeftX,   gameHeight);
    ofLine(tracker->cupRightX,  0, tracker->cupRightX,  gameHeight);
    ofLine(0, tracker->cupTopY,     gameWidth, tracker->cupTopY);
    ofLine(0, tracker->cupBottomY,  gameWidth, tracker->cupBottomY);
    
    
}

//--------------------------------------------------------------------------------------------
void CalibrationScene::keyPressed(int key){
    if (usingDebug){
        return;
    }
    
    if(key == 'l'){
        for(int i=0; i < towers.size(); i++){
            string msg = ofToString( towers[i]->uniqueID );
            msg += ": ";
            msg += ofToString(towers[i]->curAngle);
            msg += " vs ";
            msg += ofToString(towers[i]->targetAngle);
            ofLog() << msg;
        }
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
    
    showThresholdGrid = panel->getValueB("SHOW_THRESH_LINES");
}
