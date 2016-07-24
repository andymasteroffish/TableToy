//
//  TowerTD.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#ifndef __emptyExample__TowerTD__
#define __emptyExample__TowerTD__

#include "ofMain.h"
#include "Tower.h"

enum TD_TOWER_TYPE{ TD_SHOOTER, TD_ICE, TD_FIRE, TD_NUM_TOWERS  };

class TowerTD : public Tower{
public:
    
    void customSetup();
    void setupTowerDefense(TD_TOWER_TYPE type, ofImage * _pic);
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    float timeBetweenShots;
    
    bool spawnShot;
    
    ofImage * pic;
    
    TD_TOWER_TYPE tdType;
    
    float modTimeLastFrame;
    float modTimeOffset;
    
    //shot animaiton
    float shotAnimationTimer;
    float shotAnimationTime;
    float shotAnimationCurve;
    float curScale;
    float shootScale;
    
};

#endif /* defined(__emptyExample__TowerTD__) */
