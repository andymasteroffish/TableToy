//
//  CalibrationScene.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/24/15.
//
//

#ifndef __DrinkRink__CalibrationScene__
#define __DrinkRink__CalibrationScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"

class CalibrationScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);
    
    
    
};

#endif /* defined(__DrinkRink__CalibrationScene__) */
