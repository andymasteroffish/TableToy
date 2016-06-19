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
    
    playerHealth = 3;
    
    //gameW 2560
    //gameH 800
    path.clear();
    path.resize(8);
    path[0].set(100,200);
    path[1].set(500,200);
    path[2].set(500,600);
    path[3].set(1110,600);
    path[4].set(1110,250);
    path[5].set(2200,250);
    path[6].set(2200,400);
    path[7].set(2400,400);
    
    
    
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::resetCustom(){
    
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
        newFoe->setup(&path, i*2);
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
            delete foes[i];
            foes.erase( foes.begin()+i );
        }
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::drawCustom(){
    
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
        foes[i]->draw();
    }
    
    //draw the bullets
    for (int i=0; i<bullets.size(); i++){
        bullets[i].draw();
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::keyPressed(int key){
    
}


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::addTower(CupInfo thisCup){
    TowerTD * newTower = new TowerTD();
    newTower->setup( thisCup, &field);
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
