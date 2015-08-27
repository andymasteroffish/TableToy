//
//  CupTracker.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 8/20/15.
//
//

#include "CupTracker.h"



void CupTracker::setup(int _gameWidth, int _gameHeight){
    activeCups.clear();
    
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;
    
    setupCustom();
    
}


