//
//  Sceen.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "Scene.h"

//--------------------------------------------------------------------------------------------
void Scene::setup(CupTracker * _cupTracker){
    cupTracker = _cupTracker;
    
    field.setupField(ofGetWidth(),ofGetHeight());
    
    fadeTime = 3;
    
    setupCustom();
    
    readXML();
}

//--------------------------------------------------------------------------------------------
void Scene::reset(){
    
    isFading = false;
    isDoneFading = false;
    fadeTimer = fadeTime;
    fadePrc = 1;
    
    resetCustom();
}

//--------------------------------------------------------------------------------------------
void Scene::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    field.clear();
    
    //make sure cups and towers match
    checkCups();
    
    //have the towers do their thing on the field
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->update(deltaTime);
    }
    
    //let the scene do what it does
    updateCustom();
    
    //make some field particles so we cna see what the fuck's going on in here!
    makeFieldParticles();
    
    //update the field particles
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->update(deltaTime, &field);
        if (fieldParticles[i]->killFlag){
            delete fieldParticles[i];
            fieldParticles.erase( fieldParticles.begin() + i);
        }
    }
    
    if (isFading){
        fadeTimer -= deltaTime;
        fadePrc = fadeTimer/fadeTime;
        
        if (fadePrc <= 0){
            fadePrc = 0;
            isDoneFading = true;
        }
    }
}



//--------------------------------------------------------------------------------------------
void Scene::checkCups(){
    //make sure our colleciton of towers matches up with cups in the real world
    
    //first, mark each tower as having not yet been checked this frame
    for (int i=0; i<towers.size(); i++){
        towers[i]->hasBeenCheckedThisFrame = false;
    }
    
    //go through the list of real world cups
    for (int i=0; i<cupTracker->activeCups.size(); i++){
        CupInfo thisCup = cupTracker->activeCups[i];
        
        bool foundTower = false;
        
        //check if there is a coresponding tower
        for (int k=0; k<towers.size(); k++){
            if (towers[k]->uniqueID == thisCup.uniqueID){
                towers[k]->setFromCupInfo(thisCup);
                towers[k]->hasBeenCheckedThisFrame = true;    //mark that we checked it so it doesn't get killed
                foundTower = true;                          //and mark that this cup is accounted for
                break;
            }
        }
        
        //if no tower was found, it is a new cup, and we need a tower for it!
        if ( !foundTower ){
            addTower(thisCup);
        }
        
    }
    
    //now that we've gone through all cups, go through and remove any towers not accounted for
    for (int i=towers.size()-1; i>=0; i--){
        if ( !towers[i]->hasBeenCheckedThisFrame ){
            removeTower(i);
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void Scene::draw(){
    //background
    ofSetColor(bgCol);
    ofFill();
    ofRect(0, 0, ofGetWidth(),ofGetHeight());
    
    //draw the field particles
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->draw(fadePrc);
    }
    
    //draw the towers
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw(fadePrc);
    }
    
    //draw anything special for this scene
    drawCustom();
}


//--------------------------------------------------------------------------------------------
void Scene::removeTower(int vectorLoc){
    delete towers[vectorLoc];
    towers.erase( towers.begin()+vectorLoc);
}


//--------------------------------------------------------------------------------------------
void Scene::makeFieldParticles(){
    vector<ofVec2f> gridPosAffectedThisFrame;
    float minStrengthToCount = 0.01;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            if ( abs(field.field[x][y].x) > minStrengthToCount || abs(field.field[x][y].y > minStrengthToCount) ){
                gridPosAffectedThisFrame.push_back( field.getExternalPointFromInternal(x,y) );
            }
        }
    }
    
    if (gridPosAffectedThisFrame.size() == 0){
        return;
    }
    
    
    for (int i=0; i<10; i++){
        ofVec2f thisPos = gridPosAffectedThisFrame[ ofRandom( (int)gridPosAffectedThisFrame.size() )];
        ofColor thisCol = particleColors[ (int)ofRandom(particleColors.size()) ];
        FieldParticle * newP = new FieldParticle( thisPos.x, thisPos.y, thisCol );
        fieldParticles.push_back(newP);
    }
}


//--------------------------------------------------------------------------------------------
void Scene::startFade(){
    isFading = true;
}


//--------------------------------------------------------------------------------------------
void Scene::readXML(){
    ofxXmlSettings xml;
    
    cout<<"loading xml for "<<sceneName<<" scene"<<endl;
    
    if (xml.loadFile(sceneName+".xml")){
        
        string bgHexString = xml.getValue("BGCOLOR", "000000");
        bgCol.setHex( stringToHex(bgHexString) );
        readXMLCustom(xml);
        
        int particleColNum = 0;
        while (xml.tagExists("PARTICLECOL"+ofToString(particleColNum))){
            particleColNum++;
            ofColor thisCol;
            thisCol.setHex( stringToHex( xml.getValue("PARTICLECOL"+ofToString(particleColNum), "ffffff")) );
            particleColors.push_back(thisCol);
        }
        
        readXMLCustom(xml);
        
    }else{
        cout<<"your XML didn't load"<<endl;
        return false;
    }
    
    
}


//--------------------------------------------------------------------------------------------
int Scene::stringToHex(string input){
    unsigned int hexVal;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> hexVal;
    return hexVal;
}



