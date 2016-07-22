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
    
    //TowerDefenseScene(ofxControlPanel * panel);
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void resetCustom();
    void startNextWave();
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
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
    
    //wave info
    vector<TDWaveInfo> waves;
    int curWave;
    float pauseBetweenWaves;
    float pauseBetweenWavesTimer;
    float pauseBeforeFirstFoeEachWave;
    
    
    //list of poitns for foes to follow
    int curPath;
    vector<ofVec2f> path;
    bool debugShowPath;
    
    //background images
    vector<ofImage> bgPics;
    
    //the actual foes on screen
    vector<TDFoe> foes;
    int numStrongBabies;
    
    vector<TDBullet> bullets;
    vector<TDFireball> fireballs;
    vector<TDFreezeCone> freezeCones;
    
    int playerHealth;
    
    
    //images to pass to game elements
    ofImage towerPics[TD_FIRE+1];
    ofImage foePics[FOE_IGNORE+1][NUM_TD_WALK_FRAMES];
    
    //debug stuff
    bool debugFastForward;

    ofxControlPanel * myPanel;
    
};

#endif /* defined(__TabelToy__FlyersScene__) */
