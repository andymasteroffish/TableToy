//
//  WigglerBGShape.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/1/18.
//
//

#ifndef WigglerBGShape_hpp
#define WigglerBGShape_hpp

#include "ofMain.h"

class WigglerBGShape{
public:
    
    void setup(int _gameWidth, int _gameHeight);
    void reset();
    void update(float deltaTime);
    void draw(float alphaPrc);
    
    
    ofVec2f pos;
    
    float timer;
    
    //float xenoSpeed;
    
    float fullSize;
    float overShootSize;
    
    float growTime;
    float overShootTime;
    float pauseTime;
    float overShootTime2;
    float shrinkTime;
    
    float rotSpeed;
    
    int gameWidth, gameHeight;
    
    int mainCol, mainAlpha;
    int outlineCol, outlineAlpha;
    
    
};

#endif /* WigglerBGShape_hpp */
