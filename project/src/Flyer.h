//
//  Flyer.h
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#ifndef __TabelToy__Flyer__
#define __TabelToy__Flyer__

#include "ofMain.h"
#include "Tower.h"
#include "VectorField.h"

class Flyer{
public:
    
    void setup(VectorField * _field);
    void update(float _deltaTime);
    void draw(float alphaPrc);
    
    void addRepulsionForce(Flyer * other);
    
    ofVec2f pos;
    ofVec2f vel;
    
    float fric;
    float speed;
    
    float curAngle;
    
    float deltaTime;
    
    VectorField * field;
    float fieldForceAdjust;
    
    bool isFree; //when not free, it's orbitting around a tower
    Tower * targetTower;
    float orbitDist; //how far from the center of the tower to orbit
    
    ofVec2f targetPos;
    float distToTargetToCount;
    
    float bonusTargetForce;
    float bonusTrargetForceIncreasePerFrame;
    
    //bonking other flyers
    float repelRange;
    float repelForce;
    
    
};

#endif /* defined(__TabelToy__Flyer__) */
