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
#include "CupTracker.h"


class CupTrackerDebug : public CupTracker{
public:
    
    void setupCustom();
    
    //for debug
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    
    void debugAddCup(int idNum);
    void debugRemoveCup(int idNum);
    
    
    int nextUniqueID;
    
    //for testing/faking input.
    int aproxCupSize;
    int debugDraggingCupID;
    
};

#endif /* defined(__emptyExample__CamManager__) */
