//
//  Carnivale.h
//  DrinkRink
//
//  Created by Anthony on 8/26/15.
//
//

#ifndef __DrinkRink__Carnivale__
#define __DrinkRink__Carnivale__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"

class Carnivale : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
        
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);
    
    
};


#endif /* defined(__DrinkRink__Carnivale__) */
