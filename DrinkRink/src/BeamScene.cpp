//
//  BeamScene.cpp
//  DrinkRink
//
//  Created by Anthony on 8/26/15.
//
//

#include "BeamScene.h"
#include "TowerPrism.h"


//--------------------------------------------------------------------------------------------
void BeamScene::setupCustom(){
    sceneName = "beamscene";
    
    ofSetCircleResolution(360);
    
    filter.setup(ofGetWidth(), ofGetHeight());
    filter.setAberrationAmount(.5);
    filter.setBlurBrightness(100);
    filter.setBlurScale(2);
    filter.setVignetteSize(.9);
    filter.setDistortion(0);
    filter.setNoiseAmount(.1);
    
    //Setup source
    TowerPrism * newTower = new TowerPrism();
    newTower->setup( *new CupInfo, &field);
    newTower->isSource = true;
    newTower->ignoreAutoRemove = true;
    newTower->pos.x = 0;
    newTower->pos.y = ofGetHeight()/2;
    towers.push_back(newTower);

}

//--------------------------------------------------------------------------------------------
void BeamScene::resetCustom(){
    
}

//--------------------------------------------------------------------------------------------
void BeamScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    //Beam Variables
    panel->addLabel("");
    panel->addLabel("Glow Shit");
    
    panel->addSlider("Aberration Amount", "BEAM_ABBERATION", .5, 0, 2, false);
    panel->addSlider("Blur Scale", "BEAM_BLUR_SCALE", 2, 0, 5, false);
    panel->addSlider("Blur Rotation", "BEAM_BLUR_ROTATION", 0, -PI, PI, false);
    panel->addSlider("Blur Brightness", "BEAM_BLUR_BRIGHTNESS", 100, 0, 200, false);
    panel->addSlider("Distortion", "BEAM_DISTORTION", 0, 0, 2, false);
    panel->addSlider("Distortion Size", "BEAM_DISTORTION_SIZE", 1, 0, 2, false);
    panel->addSlider("Noise Amount", "BEAM_NOISE_AMOUNT", .1, 0, 2, false);
    panel->addSlider("Vignette Sharpness", "BEAM_VIGNETTE_SHARPNESS", 0, 0, 10, false);
    panel->addSlider("Vignette Size", "BEAM_VIGNETTE_SIZE", .9, 0, 5, false);
     
    myPanel = panel;
}

//--------------------------------------------------------------------------------------------
void BeamScene::checkPanelValuesCustom(ofxControlPanel * panel){
    filter.setAberrationAmount(panel->getValueF("BEAM_ABBERATION"));
    filter.setBlurScale(panel->getValueF("BEAM_BLUR_SCALE"));
    filter.setBlurRotation(panel->getValueF("BEAM_BLUR_ROTATION"));
    filter.setBlurBrightness(panel->getValueF("BEAM_BLUR_BRIGHTNESS"));
    filter.setDistortion(panel->getValueF("BEAM_DISTORTION"));
    filter.setDistortionSize(panel->getValueF("BEAM_DISTORTION_SIZE"));
    filter.setNoiseAmount(panel->getValueF("BEAM_NOISE_AMOUNT"));
    filter.setVignetteSharpness(panel->getValueF("BEAM_VIGNETTE_SHARPNESS"));
    filter.setVignetteSize(panel->getValueF("BEAM_VIGNETTE_SIZE"));
}

//--------------------------------------------------------------------------------------------

void BeamScene::updateCustom(){
    

}

//--------------------------------------------------------------------------------------------
void BeamScene::drawBackgroundCustom(){

    
    
}

//--------------------------------------------------------------------------------------------

void BeamScene::drawCustom(){
    
    
    
    //Reset length to check against
    for (int i=0; i<towers.size(); i++){
        ((TowerPrism*) towers[i])->beam.beamLength = 3000;
        ((TowerPrism*) towers[i])->lightCount = 0;
    }

    //Begin comparison loop. thisTower checks against thatTower.
    for (int i=0; i<towers.size(); i++) {
        TowerPrism* thisTower = ((TowerPrism*) towers[i]);

        //Is it currently a lightsource / hype?
        if (thisTower->isLit) {
            
            //Check to see who is the closest
            TowerPrism* closest;
            bool foundOne = false;
            float bestDistSq = 6600000;
            
            for (int j=0; j<towers.size(); j++) {
                if (i==j) continue;
                
                TowerPrism* thatTower = ((TowerPrism*) towers[j]);
                
                if (checkForHit(*thatTower, *thisTower)) {
                    float d2 = ofDistSquared(thisTower->pos.x, thisTower->pos.y, thatTower->pos.x, thatTower->pos.y);
                    if (d2 < bestDistSq) {
                        closest = thatTower;
                        bestDistSq = d2;
                        foundOne = true;
                    }
                }
            }
            
            //Closest  determined, apply beam
            if (foundOne) {
                closest->lightCount+=1;
                thisTower->beam.beamLength = sqrt(bestDistSq);
            }
        }
    }
    
    //Draw towers
    filter.begin();
    for (int i=0; i<towers.size(); i++){
        if ( ((TowerPrism*) towers[i])->isLit) ((TowerPrism*) towers[i])->customDraw(1);
    }
    filter.end();

    filter.draw();
    
    for (int i=0; i<towers.size(); i++){
        if ( !((TowerPrism*) towers[i])->isLit) ((TowerPrism*) towers[i])->customDraw(1);
    }
    
}

//--------------------------------------------------------------------------------------------
void BeamScene::keyPressed(int key){
    
}
//--------------------------------------------------------------------------------------------
bool BeamScene::checkForHit(TowerPrism candidate, TowerPrism thisPrism) {
    
    float beamStartX = thisPrism.pos.x;
    float beamStartY = thisPrism.pos.y;
    float beamEndX = thisPrism.beam.beamLength * cos(thisPrism.targetAngle) + beamStartX;
    float beamEndY = thisPrism.beam.beamLength * sin(thisPrism.targetAngle) + beamStartY;
    
    
    float A = candidate.pos.x - thisPrism.pos.x;
    float B = candidate.pos.y - thisPrism.pos.y;
    float C = beamEndX - beamStartX;
    float D = beamEndY - beamStartY;
    
    float dot = A * C + B * D;
    float len_sq = C * C + D * D;
    float param = -1;
    if (len_sq != 0) //in case of 0 length line
        param = dot / len_sq;
    
    float xx, yy;
    
    if (param < 0) {
        xx = beamStartX;
        yy = beamStartY;
    } else if (param > 1) {
        xx = beamEndX;
        yy = beamEndY;
    } else {
        xx = beamStartX + param * C;
        yy = beamStartY + param * D;
    }
    
    float dx = candidate.pos.x - xx;
    float dy = candidate.pos.y - yy;
    
    
    if (dx * dx + dy * dy <= candidate.towerSize * candidate.towerSize) {
        return true;
    } else {
        return false;
    }
}


//--------------------------------------------------------------------------------------------
void BeamScene::addTower(CupInfo thisCup){
    TowerPrism * newTower = new TowerPrism();
    newTower->setup( thisCup, &field);
    towers.push_back(newTower);
}
