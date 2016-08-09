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

#include "BetterFont.h"

#include "Tower.h"
#include "TowerTD.h"

#include "TDFoe.h"
#include "TDFoeDeath.h"
#include "TDAnimationMinder.h"

#include "TDBullet.h"
#include "TDBulletHit.h"
#include "TDFireball.h"
#include "TDFreezeCone.h"

#include "TDHomeHit.h"

class TDWaveInfo{
public:
    float timeBetweenFoes;
    vector<FoeType> foes;
};


class TowerDefenseScene : public Scene{
public:
    
    //TowerDefenseScene(ofxControlPanel * panel);
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void resetCustom();
    void startNextWave();
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void drawMessage();
    
    void keyPressed(int key);
    
    void addTower(CupInfo thisCup);
    void removingTowerCustom(Tower * towerBeingRemoved);
    
    void takeDamage();
    
    void spawnShot(TowerTD * source);
    void spawnFireball(ofVec2f pos);
    void spawnFreezeCone(Tower * source);
    
    void spawnStrongBabies(TDFoe parent);
    
    void setMessage(string newMessage, float displayTime);
    
    void setWavesFromFile(string fileName);
    
    void setPath(int curWave);
    
    //displaying shit
    BetterFont fontBig;
    
    string curMessage;
    float messageDisplayTime;
    float messageTimer;
    float firstWaveMessageLeadTimer;
    
    //wave info
    vector<TDWaveInfo> waves;
    int curWave;
    float pauseBetweenWaves;
    float pauseBetweenWavesTimer;
    float pauseBeforeFirstFoeEachWave;
    float pauseBeforeVeryFirstWave;
    
    
    //list of poitns for foes to follow
    int curPath;
    vector<ofVec2f> path[2];
    bool debugShowPath;
    
    //background images
    vector<ofImage> bgPics;
    
    //the actual foes on screen
    vector<TDFoe> foes;
    vector<TDFoeDeath> deadFoes;
    int numStrongBabies;
    
    vector<TDBullet> bullets;
    vector<TDFireball> fireballs;
    vector<TDFreezeCone> freezeCones;
    
    vector<TDBulletHit> bulletHits;
    
    int playerHealth;
    vector<TDHomeHit> homeHits;
    
    //animations and other images
    TDAnimationMinder anims;
    ofImage towerPics[TD_FIRE+1];
    ofImage projectilePics[TD_FIRE+1];
    ofImage baseBorder, baseCenter;
    ofImage fireballPic, bulletHitPic;
    
    //switching out of the game whent he player wins or loses
    bool gameOver;
    bool didWin;
    float endGameTimer;
    float endGameTimeBeforeNextScene;
    
    //debug stuff
    bool debugFastForward;
    bool debugInvincible;
    bool debugPause;

    ofxControlPanel * myPanel;
    int towerSpawnRates[TD_NUM_TOWERS];
    
};

#endif /* defined(__TabelToy__FlyersScene__) */
