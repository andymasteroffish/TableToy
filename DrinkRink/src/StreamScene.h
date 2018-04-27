//
//  StreamScene.h
//  emptyExample
//
//  Created by Andy Wallace on 7/2/15.
//
//

#ifndef __emptyExample__StreamScene__
#define __emptyExample__StreamScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TowerRock.h"

#include "StreamBackgroundShape.h"

class StreamScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void setStreamForceOnField();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);
    
    vector<StreamBackgroundShape> bgShapes;
    
    float idleKillTime;
    
    
};

#endif /* defined(__emptyExample__StreamScene__) */
