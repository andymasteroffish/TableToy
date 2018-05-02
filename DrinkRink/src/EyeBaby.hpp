//
//  EyeBaby.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/2/18.
//
//

#ifndef EyeBaby_hpp
#define EyeBaby_hpp

#include "ofMain.h"

class EyeBaby{
public:
    
    void setup(float x, float y);
    
    void checkFeelers(float otherX, float otherY, float otherSize);
    void update(float deltaTime);
    
    void debugDraw();
    
    
    ofVec2f pos;
    
    vector<ofVec2f> feelersPos;
    vector<bool>    feelersBeingTouched;
                
    float feelerDist;
    float feelerSpread;
    
    float curAngle;
    float moveSpeed;
    
    float preferredAngle;
    float turnSpeed, turnSpeedSlow;
    
    
};

#endif /* EyeBaby_hpp */
