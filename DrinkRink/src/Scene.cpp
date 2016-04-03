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
    
    particlePic.loadImage("pic/smoke.png");
    
    ignorePanelValues = false;
    
    showCupDebug = false;
    
    setupCustom();
    
}

//--------------------------------------------------------------------------------------------
void Scene::reset(){
    
    isFading = false;
    isDoneFading = false;
    fadeTimer = fadeTime;
    alphaPrc = 1;
    
    switchScenesFlag = false;
    
    resetCustom();
}

//--------------------------------------------------------------------------------------------
void Scene::update(float _deltaTime, ofxControlPanel * panel){
    deltaTime = _deltaTime;
    
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
    //cout<<"update time: "<<(ofGetElapsedTimef()-updateStartTime)<<endl;
    
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
    
    
    checkPanelValuesCustom(panel);
    
    if (ignorePanelValues){
        return;
    }
    
    //colors
    bgCol.setHsb(panel->getValueF("BG_HUE"), panel->getValueF("BG_SAT"), panel->getValueF("BG_BRI"));
    
    //particle shit
    p_friction = panel->getValueF("PARTICLE_FRICTION");
    p_killTime = panel->getValueF("PARTICLE_KILL_TIME");
    p_showDot = panel->getValueB("SHOW_DOT");
    p_fillDot = panel->getValueF("FILL_DOT");
    p_dotSize = panel->getValueF("DOT_SIZE");
    
    p_useNoiseWiggle = panel->getValueB("USE_NOISE_WIGGLE");
    p_noiseWiggleRange = panel->getValueF("NOISE_WIGGLE_RANGE");
    p_noiseWigglePower = panel->getValueF("NOISE_WIGGLE_POWER");
    p_noiseWiggleRate = panel->getValueF("NOISE_WIGGLE_RATE");
    
    p_useTrails = panel->getValueB("USE_TRAIL");
    p_numTrailPositions = panel->getValueF("TRAIL_LENGTH");
    p_trailStartWidth = panel->getValueF("TRAIL_START_THICKNESS");
    p_trailEndWidth = panel->getValueF("TRAIL_END_THICKNESS");
    
    p_usePic = panel->getValueB("USE_PIC");
    p_picScale = panel->getValueF("PIC_SCALE");
    
    particleColors.clear();
    for (int i=0; i<5; i++){
        ofColor thisCol;
        thisCol.setHsb(panel->getValueF("PARTICLE_HUE_"+ofToString(i)), panel->getValueF("PARTICLE_SAT"), panel->getValueF("PARTICLE_BRI"));
        particleColors.push_back(thisCol);
    }
    
    //grid shit
    
    field.gridDrawingAdjust = panel->getValueF("GRID_DRAWING_ADJUST");
    field.showVerticalGrid = panel->getValueB("SHOW_VERTICAL_GRID");
    field.showHorizontalGrid = panel->getValueB("SHOW_HORIZONTAL_GRID");
    field.showGridFill = panel->getValueB("SHOW_GRID_FILL");
    
    field.gridValThreshold = panel->getValueF("GRID_VAL_THRESHOLD");
    field.gridValCeiling = panel->getValueF("GRID_VAL_CEILING");
    
    field.useGridWiggle = panel->getValueB("USE_GRID_WIGGLE");
    field.gridWiggleSpeed = panel->getValueF("GRID_WIGGLE_SPEED");
    field.gridWiggleStrength = panel->getValueF("GRID_WIGGLE_STRENGTH");
    
    field.useGridFade = panel->getValueB("USE_GRID_LINE_FADE");
    field.useVarryingWidths = panel->getValueB("USE_GRID_VARRYING_LINE_WIDTH");
    field.gridMinLineWidth = panel->getValueF("GRID_MIN_LINE_WIDTH");
    field.gridMaxLineWidth = panel->getValueF("GRID_MAX_LINE_WIDTH");
    
    field.showVerticalGridCurved = panel->getValueB("SHOW_VERTICAL_GRID_CURVED");
    field.showHorizontalGridCurved = panel->getValueB("SHOW_HORIZONTAL_GRID_CURVED");
    
    field.gridColor.setHsb(panel->getValueF("GRID_HUE"), panel->getValueF("GRID_SAT"), panel->getValueF("GRID_BRI"));
    
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
    ofSetColor(bgCol, 255*alphaPrc);
    ofFill();
    ofRect(0, 0, gameWidth, gameHeight);
    
    drawBackgroundCustom();
    
    //some visual effects rely on drawing the grid
    //this will do nothing if those effects are not active
    field.drawGrid(alphaPrc);
    
    //draw the field particles
    //float drawStartTime = ofGetElapsedTimef();
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->draw(alphaPrc);
    }
    //cout<<"draw time : "<<(ofGetElapsedTimef()-drawStartTime)<<endl;
    
    
    //draw the towers
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw(alphaPrc, showCupDebug);
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
    vector<FieldCell> cellsAffectedThisFrame;
    vector<GridPos>   cellLocations;
    //vector<ofVec2f> gridPosAffectedThisFrame;
    float minStrengthToCount = 0.01;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            if ( abs(field.field[x][y].vel.x) > minStrengthToCount || abs(field.field[x][y].vel.y > minStrengthToCount) ){
                cellsAffectedThisFrame.push_back(field.field[x][y]);
                GridPos thisPos;
                thisPos.set(x, y);
                cellLocations.push_back(thisPos);
                //gridPosAffectedThisFrame.push_back( field.getExternalPointFromInternal(x,y) );
            }
        }
    }
    
    if (cellsAffectedThisFrame.size() == 0){
        return;
    }
    
    
    for (int i=0; i<10; i++){
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
        
        newP->pic = &particlePic;
        
        if (!ignorePanelValues){
            newP->fric = p_friction;
            newP->killTime = p_killTime;
            newP->showDot = p_showDot;
            newP->fillDot = p_fillDot;
            newP->dotSize = p_dotSize;
            
            newP->useNoiseWiggle = p_useNoiseWiggle;
            newP->noiseWiggleRange = p_noiseWiggleRange;
            newP->noiseWigglePower = p_noiseWigglePower;
            newP->noiseWiggleRate = p_noiseWiggleRate;
            
            newP->useTrails = p_useTrails;
            newP->numTrailPositions = p_numTrailPositions;
            newP->trailStartWidth = p_trailStartWidth;
            newP->trailEndWidth =  p_trailEndWidth;
            
            newP->usePic = p_usePic;
            newP->picScale = p_picScale;
            
            if (particleColors.size() > 0){
                newP->col = particleColors[ (int)ofRandom(particleColors.size())];
            }
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



