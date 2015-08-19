//
//  CamManager.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "CupTrackerDebug.h"


void CupTrackerDebug::setup(){
    
    activeCups.clear();
    
    aproxCupSize = 40;
    debugDraggingCupID = -1;
    nextUniqueID = 0;
    
    usingMouseAndKeyboard = true;  //TURN THIS THE FUCK OFF IF YOU PUT TUIO STUFF IN
    
}

void CupTrackerDebug::update(){
    
    if (usingMouseAndKeyboard){
        debugUpdate();
    }
    else{
    
        // THIS IS WHERE WE SHOULD BE CHECKING FOR TUIO ETC.
        // Going through the vector of CupInfo, making sure everything is in place
        // removing cups that are no longer there, adding new ones
        // blah blah blah
        
    }
    
}


//for debug

void CupTrackerDebug::debugUpdate(){
    //do we need anything here?
}

void CupTrackerDebug::debugDraw(){
    for (int i=0; i<activeCups.size(); i++){
        
        ofSetColor(255, 230, 41);
        
        ofCircle(activeCups[i].pos.x, activeCups[i].pos.y, aproxCupSize);
        
        ofSetColor(100);
        
        float lineEndX =  activeCups[i].pos.x + cos(activeCups[i].angle) * aproxCupSize;
        float lineEndY =  activeCups[i].pos.y + sin(activeCups[i].angle) * aproxCupSize;
        
        ofSetLineWidth(1);
        ofLine( activeCups[i].pos.x, activeCups[i].pos.y, lineEndX, lineEndY);
        
        ofSetColor(0);
        
        ofDrawBitmapString("t:"+ofToString(activeCups[i].typeID), activeCups[i].pos.x-20, activeCups[i].pos.y-10);
        ofDrawBitmapString("#:"+ofToString(activeCups[i].uniqueID), activeCups[i].pos.x-20, activeCups[i].pos.y+10);
        
    }
}

void CupTrackerDebug::mousePressed(int x, int y, int button){
    if (!usingMouseAndKeyboard) return;
    
    //check if the mouse was over any cup
    for (int i=0; i<activeCups.size(); i++){
        if ( ofDist(x, y, activeCups[i].pos.x, activeCups[i].pos.y) < aproxCupSize){
            debugDraggingCupID = i;
        }
    }
    
}

void CupTrackerDebug::mouseDragged(int x, int y, int button){
    if (!usingMouseAndKeyboard) return;
    
    //if a cup is being dragged, move it
    if (debugDraggingCupID > -1 && debugDraggingCupID < activeCups.size()){
        
        if (button == 0){
            activeCups[debugDraggingCupID].pos.set(x,y);
        }
        if (button == 2){
            activeCups[debugDraggingCupID].angle = atan2( y-activeCups[debugDraggingCupID].pos.y, x-activeCups[debugDraggingCupID].pos.x);
        }
    }
    
}

void CupTrackerDebug::mouseReleased(int x, int y, int button){
    if (!usingMouseAndKeyboard) return;
    
    debugDraggingCupID = -1;
    
}

void CupTrackerDebug::keyPressed(int key){
    if (!usingMouseAndKeyboard) return;
    
    if (key >= '0' && key <= '9'){
        int typeValue = key - '0';
        //cout<<"gotta add "<<typeValue<<endl;
        debugAddCup(typeValue);
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
void CupTrackerDebug::debugAddCup(int typeID){
    CupInfo thisCupInfo;
    
    thisCupInfo.typeID = typeID;
    thisCupInfo.uniqueID = nextUniqueID++;
    thisCupInfo.pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()) );
    thisCupInfo.angle = ofRandom( TWO_PI );
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    
    activeCups.push_back(thisCupInfo);
}

//removes the given dummy cup
void CupTrackerDebug::debugRemoveCup(int idNum){
    activeCups.erase( activeCups.begin()+idNum );
}







