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

class TowerTD : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    float timeBetweenShots;
    float shotTimer;
    
    bool spawnShot;
    
    ofImage * pic;
    
};

#endif /* defined(__emptyExample__TowerTD__) */
