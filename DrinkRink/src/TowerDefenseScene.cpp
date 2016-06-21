//
//  TowerDefenseScene.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "TowerDefenseScene.h"


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setupCustom(){
    sceneName = "tower defense";
    
    towerPics[0].loadImage("pic/td/tower_shooter.png");
    
    foePics[FOE_DUMB].loadImage("pic/td/foe_dumb.png");
    foePics[FOE_STRONG].loadImage("pic/td/foe_strong.png");
    foePics[FOE_FAST].loadImage("pic/td/foe_fast.png");
    foePics[FOE_WAVE].loadImage("pic/td/foe_wave.png");
    foePics[FOE_IGNORE].loadImage("pic/td/foe_ignore.png");
    
    
    
    //gameW 2560
    //gameH 800
    path.clear();
    path.resize(8);
    path[0].set(100,200);
    path[1].set(500,200);
    path[2].set(500,600);
    path[3].set(1110,600);
    path[4].set(1110,250);
    path[5].set(1800,250);
    path[6].set(1800,400);
    path[7].set(2200,400);
    
    
    
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::resetCustom(){
    
    playerHealth = 3;
    
    //clear out any old foes
    while(foes.size() > 0){
        delete foes[0];
        foes.erase(foes.begin());
    }
    
    //clear out bullets
    bullets.clear();
    
    //make some demo foes
    for (int i=0; i<20; i++){
        TDFoe * newFoe = new TDFoe();
        if (i%5 == 0){
            newFoe->setup(FOE_DUMB, &foePics[FOE_DUMB], &path, i*2);
        }
        if (i%5 == 1){
            newFoe->setup(FOE_STRONG, &foePics[FOE_STRONG], &path, i*2);
        }
        if (i%5 == 2){
            newFoe->setup(FOE_FAST, &foePics[FOE_FAST], &path, i*2);
        }
        if (i%5 == 3){
            newFoe->setup(FOE_WAVE, &foePics[FOE_WAVE], &path, i*2);
        }
        if (i%5 == 4){
            newFoe->setup(FOE_IGNORE, &foePics[FOE_IGNORE], &path, i*2);
        }
        foes.push_back(newFoe);
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::updateCustom(){
    
    //check all towers to see if they are doing thangs (like Big Bear)
    for (int i=0; i<towers.size(); i++){
        if (towers[i]->towerType == "td_shooter"){
            TowerTD * thisShooter = (TowerTD *)towers[i];
            if (thisShooter->spawnShot){
                thisShooter->spawnShot = false;
                spawnShot(thisShooter);
            }
        }
    }
    
    //update the bullets
    for (int i=bullets.size()-1; i>=0; i--){
        bullets[i].update(deltaTime);
        
        //if it out of bounds?
        float padding = bullets[i].size*2;
        if (bullets[i].pos.x < -padding || bullets[i].pos.x > gameWidth+padding || bullets[i].pos.y < -padding || bullets[i].pos.y > gameHeight+padding){
            bullets.erase(bullets.begin()+i);
        }
        
        //check all foes to see if it hit any
        else{
            for (int f=0; f<foes.size(); f++){
                float minDistSq = powf( (foes[f]->hitCircleSize + bullets[i].size), 2);
                if ( ofDistSquared(foes[f]->pos.x, foes[f]->pos.y,  bullets[i].pos.x,  bullets[i].pos.y) < minDistSq){
                    foes[f]->takeDamage(bullets[i].dmg);
                    bullets.erase(bullets.begin()+i);
                }
            }
        }
    }
    
    
    //update foes
    for (int i=foes.size()-1; i>=0; i--){
        foes[i]->update(deltaTime);
        
        if (foes[i]->reachedTheEnd){
            takeDamage();
            foes[i]->killMe = true;    //remove the foe
        }
        
        //check if the foe died
        if (foes[i]->killMe){
            if (foes[i]->type == FOE_STRONG){
                spawnStrongBabies(foes[i]);
            }
            delete foes[i];
            foes.erase( foes.begin()+i );
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::drawCustom(){
    
    //draw the home
    ofFill();
    float homeSize = 60;
    ofSetColor(ofColor::purple);
    ofCircle(path[path.size()-1].x, path[path.size()-1].y, homeSize);
    
    //show the player health aorund if
    float angleSpacing = TWO_PI/playerHealth;
    float heartSize = 20;
    float heartDist = heartSize + homeSize + 15;
    for (int i=0; i<playerHealth; i++){
        ofSetColor(ofColor::pink);
        float thisAngle = angleSpacing*i + ofGetElapsedTimef()*0.5;
        float xPos = path[path.size()-1].x + cos(thisAngle) * heartDist;
        float yPos = path[path.size()-1].y + sin(thisAngle) * heartDist;
        ofCircle(xPos, yPos, heartSize);
    }
    
    //debug draw the path
    ofSetColor(20);
    for (int i=0; i<path.size(); i++){
        if (i>0){
            ofLine(path[i], path[i-1]);
        }
        ofCircle(path[i].x, path[i].y, 10);
    }
    
    
    //draw the foes
    for (int i=0; i<foes.size(); i++){
        foes[i]->draw(alphaPrc);
    }
    
    //draw the bullets
    for (int i=0; i<bullets.size(); i++){
        bullets[i].draw();
    }
    
    //is the player dead?
    if (playerHealth <= 0){
        ofSetColor(255,0,0);
        
        for (int i=0; i<30; i++){
            ofDrawBitmapString("YOU DEAD", gameWidth * ofNoise(ofGetElapsedTimef()*0.2, i), gameHeight * ofNoise(ofGetElapsedTimef()*0.1, i, 10));
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::addTower(CupInfo thisCup){
    TowerTD * newTower = new TowerTD();
    newTower->setup( thisCup, &field);
    newTower->pic = &towerPics[0];
    towers.push_back(newTower);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::takeDamage(){
    playerHealth--;
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::spawnShot(Tower * source){
    TDBullet newBullet;
    newBullet.setup(source->pos, source->angle);
    bullets.push_back(newBullet);
}

//--------------------------------------------------------------------------------------------
//the strong foe spawns two normal foes when it dies
void TowerDefenseScene::spawnStrongBabies(TDFoe * parent){
    float angle = ofRandom(TWO_PI);
    float dist = 50;
    for (int i=0; i<2; i++){
        
        ofVec2f newPos;
        newPos.x = parent->pos.x + cos(angle) * dist;
        newPos.y = parent->pos.y + sin(angle) * dist;
        angle +=  PI;
        
        TDFoe * newFoe = new TDFoe();
        newFoe->setup(FOE_DUMB, &foePics[FOE_DUMB], &path, 0);
        newFoe->setPos(newPos, parent->nextNodeID);
        foes.push_back(newFoe);
    }
}
