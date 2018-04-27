//
//  Sceen.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "Scene.h"

//--------------------------------------------------------------------------------------------
void Scene::setup(CupTracker * _cupTracker, int _gameWidth, int _gameHeight){
    cupTracker = _cupTracker;
    
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;
    
    field.setupField(gameWidth, gameHeight);
    
    fadeTime = 3;
    
    
    showCupDebug = false;
    
    numFieldParticlesPerFrame = 15;
    
    setupCustom();
}

//--------------------------------------------------------------------------------------------
void Scene::reset(){
    
    isFading = false;
    isDoneFading = false;
    fadeTimer = fadeTime;
    alphaPrc = 1;
    
    switchScenesFlag = false;
    
    idleTimer = 0;
    activeTimer = 0;
    
    //assume we need full funcitonality
    cupTracker->useBlobs = true;
    cupTracker->useCups = true;
    
    resetCustom();
}

//--------------------------------------------------------------------------------------------
void Scene::update(float _deltaTime, ofxControlPanel * panel){
    deltaTime = _deltaTime;
    
    activeTimer += deltaTime;
    idleTimer += deltaTime;
    
    checkPanelValues(panel);
    
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
    //float updateStartTime = ofGetElapsedTimef();
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->update(deltaTime, &field);
        if (fieldParticles[i]->killFlag){
            delete fieldParticles[i];
            fieldParticles.erase( fieldParticles.begin() + i);
        }
    }
    
    //When switching scenes, the current scene fades out
    //when isDoneFadiing is true, the scene will stop updating
    if (isFading){
        fadeTimer -= deltaTime;
        alphaPrc = fadeTimer/fadeTime;
        
        if (alphaPrc <= 0){
            alphaPrc = 0;
            isDoneFading = true;
        }
    }
}

//--------------------------------------------------------------------------------------------
void Scene::checkPanelValues(ofxControlPanel *panel){
    
    idleTowerMoveThreshold = panel->getValueF("IDLE_MOVE_THRESH");
    idleTowerRotateThreshold = panel->getValueF("IDLE_ROTATE_THRESH");
    
    checkPanelValuesCustom(panel);
    
}


//--------------------------------------------------------------------------------------------
//make sure our colleciton of towers matches up with cups in the real world
void Scene::checkCups(){
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
                //store the old values
                float prevAngle = towers[k]->targetAngle;
                ofVec2f prevPos = towers[k]->pos;
                
                //update
                towers[k]->setFromCupInfo(thisCup);
                towers[k]->hasBeenCheckedThisFrame = true;    //mark that we checked it so it doesn't get killed
                foundTower = true;                          //and mark that this cup is accounted for
                
                //check if it moved enough to not be considered idle
                if ( ofDistSquared(prevPos.x, prevPos.y, towers[k]->pos.x, towers[k]->pos.y) > idleTowerMoveThreshold*idleTowerMoveThreshold){
                    //cout<<"big move"<<endl;
                    idleTimer = 0;
                }
                if ( abs(prevAngle-towers[k]->targetAngle) > idleTowerRotateThreshold){
                    //cout<<"big angle"<<endl;
                    idleTimer = 0;
                }
                
                break;
            }
        }
        
        //if no tower was found, it is a new cup, and we need a tower for it!
        if ( !foundTower ){
            idleTimer = 0;
            addTower(thisCup);
        }
        
    }
    
    //now that we've gone through all cups, go through and remove any towers not accounted for
    for (int i=towers.size()-1; i>=0; i--){
        if ( !towers[i]->hasBeenCheckedThisFrame && !towers[i]->ignoreAutoRemove){
            idleTimer = 0;
            removeTower(i);
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void Scene::draw(){
    //background
    ofSetColor(bgCol, 255*alphaPrc);
    ofFill();
    ofRect(0, 0, gameWidth, gameHeight);
    
    drawBackgroundCustom();
    
    //some visual effects rely on drawing the grid
    //this will do nothing if those effects are not active
    field.drawGrid(alphaPrc);
    
    //draw the field particles
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->draw(alphaPrc);
    }
    
    //draw the towers
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw(alphaPrc, showCupDebug);
    }
    
    //draw anything special for this scene
    drawCustom();
}


//--------------------------------------------------------------------------------------------
void Scene::removeTower(int vectorLoc){
    removingTowerCustom(towers[vectorLoc]);
    delete towers[vectorLoc];
    towers.erase( towers.begin()+vectorLoc);
}


//--------------------------------------------------------------------------------------------
void Scene::makeFieldParticles(){
    vector<FieldCell> cellsAffectedThisFrame;
    vector<GridPos>   cellLocations;
    float minStrengthToCount = 0.01;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            if ( abs(field.field[x][y].vel.x) > minStrengthToCount || abs(field.field[x][y].vel.y) > minStrengthToCount ){
                cellsAffectedThisFrame.push_back(field.field[x][y]);
                GridPos thisPos;
                thisPos.set(x, y);
                cellLocations.push_back(thisPos);
            }
        }
    }
    
    if (cellsAffectedThisFrame.size() == 0){
        return;
    }
    
    
    for (int i=0; i<numFieldParticlesPerFrame; i++){
        int idNum = ofRandom( (int)cellsAffectedThisFrame.size() );
        FieldCell * thisCell = &cellsAffectedThisFrame[ idNum ];
        ofVec2f thisPos = field.getExternalPointFromInternal(cellLocations[idNum].x, cellLocations[idNum].y);

        FieldParticle * newP = new FieldParticle( thisPos.x, thisPos.y );
        
        ParticleType typeToSet = thisCell->getRandomParticleType();
        
        if (typeToSet != PARTICLE_NO_TYPE){
            newP->setType(typeToSet);
        }else{
            newP->setType(defaultParticleType);
        }
        
        //add it to the list
        fieldParticles.push_back(newP);
    }
}


//--------------------------------------------------------------------------------------------
void Scene::startFade(){
    isFading = true;
}


//--------------------------------------------------------------------------------------------
int Scene::stringToHex(string input){
    unsigned int hexVal;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> hexVal;
    return hexVal;
}



