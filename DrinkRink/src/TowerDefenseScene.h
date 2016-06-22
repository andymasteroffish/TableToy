//
//  FlyersScene.h
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#ifndef __TabelToy__TowerDefenseScene__
#define __TabelToy__TowerDefenseScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TowerTD.h"

#include "TDFoe.h"

#include "TDBullet.h"
#include "TDFireball.h"
#include "TDFreezeCone.h"

class TDWaveInfo{
public:
    float timeBetweenFoes;
    vector<FoeType> foes;
};


class TowerDefenseScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void startNextWave();
    void updateCustom();
    
    void drawCustom();
    
    void keyPressed(int key);
    
    void addTower(CupInfo thisCup);
    void removingTowerCustom(Tower * towerBeingRemoved);
    
    void takeDamage();
    
    void spawnShot(TowerTD * source);
    void spawnFireball(ofVec2f pos);
    void spawnFreezeCone(Tower * source);
    
    void spawnStrongBabies(TDFoe parent);
    
    void setWavesFromFile(string fileName);
    
    //wave info
    vector<TDWaveInfo> waves;
    int curWave;
    float pauseBetweenWaves;
    float pauseBetweenWavesTimer;
    
    //list of poitns for foes to follow
    vector<ofVec2f> path;
    
    //the actual foes on screen
    vector<TDFoe> foes;
    
    vector<TDBullet> bullets;
    vector<TDFireball> fireballs;
    vector<TDFreezeCone> freezeCones;
    
    int playerHealth;
    
    
    //images to pass to game elements
    ofImage towerPics[TD_FIRE+1];
    ofImage foePics[FOE_IGNORE+1];

    
    
};

#endif /* defined(__TabelToy__FlyersScene__) */
