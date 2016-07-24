//
//  CamManager.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "CupTrackerDebug.h"


void CupTrackerDebug::setupCustom(){
    aproxCupSize = 80;
    debugDraggingCupID = -1;
    nextUniqueID = 0;
    
    //add some cups
    for (int i=0; i<3; i++){
        debugAddCup();
    }
    
    isDebug = true;
    
}


void CupTrackerDebug::draw(){
    for (int i=0; i<activeCups.size(); i++){
        
        ofSetColor(255, 230, 41);
        
        ofCircle(activeCups[i].pos.x, activeCups[i].pos.y, aproxCupSize);
        
        ofSetColor(100);
        
        float lineEndX =  activeCups[i].pos.x + cos(activeCups[i].angle) * aproxCupSize;
        float lineEndY =  activeCups[i].pos.y + sin(activeCups[i].angle) * aproxCupSize;
        
        ofSetLineWidth(1);
        ofLine( activeCups[i].pos.x, activeCups[i].pos.y, lineEndX, lineEndY);
        
        ofSetColor(0);
        
        ofDrawBitmapString("#:"+ofToString(activeCups[i].uniqueID), activeCups[i].pos.x-20, activeCups[i].pos.y+10);
        
    }
}

void CupTrackerDebug::mousePressed(int x, int y, int button){
    //check if the mouse was over any cup
    for (int i=0; i<activeCups.size(); i++){
        if ( ofDist(x, y, activeCups[i].pos.x*debugDisplayScale, activeCups[i].pos.y*debugDisplayScale) < aproxCupSize*debugDisplayScale){
            debugDraggingCupID = i;
        }
    }
    
}

void CupTrackerDebug::mouseDragged(int x, int y, int button){
    
    //if a cup is being dragged, move it
    if (debugDraggingCupID > -1 && debugDraggingCupID < activeCups.size()){
        
        if (button == 0){
            activeCups[debugDraggingCupID].pos.set(x/debugDisplayScale,y/debugDisplayScale);
        }
        if (button == 2){
            activeCups[debugDraggingCupID].angle = atan2( y-activeCups[debugDraggingCupID].pos.y*debugDisplayScale, x-activeCups[debugDraggingCupID].pos.x*debugDisplayScale);
        }
    }
    
}

void CupTrackerDebug::mouseReleased(int x, int y, int button){
    
    debugDraggingCupID = -1;
    
}

void CupTrackerDebug::keyPressed(int key){
    
    if (key >= '0' && key <= '9'){
        //int typeValue = key - '0';
        //cout<<"gotta add "<<typeValue<<endl;
        debugAddCup();
    }
    
    if (key == 127){
        
        //if there is a cup being dragged around, delete it
        if (debugDraggingCupID > -1 && debugDraggingCupID < activeCups.size()){
            debugRemoveCup(debugDraggingCupID);
            debugDraggingCupID = -1;
        }
        
    }
}

//creates a dummy cup with random values
void CupTrackerDebug::debugAddCup(){
    CupInfo thisCupInfo;
    
    thisCupInfo.uniqueID = nextUniqueID++;
    thisCupInfo.pos.set( ofRandom(gameWidth), ofRandom(gameHeight) );
    thisCupInfo.angle = ofRandom( TWO_PI );
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    
    activeCups.push_back(thisCupInfo);
}

//removes the given dummy cup
void CupTrackerDebug::debugRemoveCup(int idNum){
    activeCups.erase( activeCups.begin()+idNum );
}







