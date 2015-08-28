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
#include "ofxControlPanel.h"

class CupTracker{
public:
    
    
    void setup(int _gameWidth, int _gameHeight);
    virtual void setupCustom(){}
    virtual void update(){}
    virtual void updateFromPanel(ofxControlPanel * panel){}
    virtual void draw(){}
    
    //for debug
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    virtual void keyPressed(int key){}
    
    //list of cups
    vector<CupInfo> activeCups;
    
    int gameWidth, gameHeight;
    
    bool isDebug;
    
};

#endif /* defined(__DrinkRink__CupTracker__) */
