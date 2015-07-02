//
//  CamManager.h
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#ifndef __emptyExample__CamManager__
#define __emptyExample__CamManager__

#include "ofMain.h"
#include "CupInfo.h"

class CupTracker{
public:
    
    void setup();
    void update();
    
    
    //for debug
    void debugUpdate();
    void debugDraw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    
    void debugAddCup(int idNum);
    void debugRemoveCup(int idNum);
    
    
    //list of cups
    vector<CupInfo> activeCups;
    int nextUniqueID;
    
    //for testing/faking input.
    int aproxCupSize;
    bool usingMouseAndKeyboard;
    int debugDraggingCupID;
    
};

#endif /* defined(__emptyExample__CamManager__) */
