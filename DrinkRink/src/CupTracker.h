//
//  CupTracker.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/20/15.
//
//

#ifndef __DrinkRink__CupTracker__
#define __DrinkRink__CupTracker__

#include "ofMain.h"
#include "CupInfo.h"

class CupTracker{
public:
    
    
    void setup();
    virtual void setupCustom(){}
    virtual void update(){}
    virtual void draw(){}
    
    //for debug
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    virtual void keyPressed(int key){}
    
    //list of cups
    vector<CupInfo> activeCups;
    //int nextUniqueID;
    
    
    
};

#endif /* defined(__DrinkRink__CupTracker__) */
