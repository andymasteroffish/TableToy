//
//  TowerPaddle.h
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#ifndef __emptyExample__TowerPaddle__
#define __emptyExample__TowerPaddle__

#include "ofMain.h"
#include "Tower.h"

class TowerPaddle : public Tower{
public:
    
    void customSetup();
    void customUpdate();
    
    void customDraw(float alphaPrc);
    
    
    void addOutwardCircle(float xPos, float yPos, float thisFieldRange, float strength);
    
    vector<ofVec2f> points;
    
};

#endif /* defined(__emptyExample__TowerPaddle__) */
