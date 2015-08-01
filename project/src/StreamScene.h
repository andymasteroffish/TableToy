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
#include "Ball.h"

#include "Tower.h"
#include "TowerRock.h"

class StreamScene : public Scene{
public:
    
    
    void setupCustom();
    void resetCustom();
    void updateCustom();
    
    void setStreamForceOnField();
    
    void drawCustom();
    
    void keyPressed(int key);
    
    
    void addTower(CupInfo thisCup);
    
    virtual void readXMLCustom(ofxXmlSettings xml);
    
    
};

#endif /* defined(__emptyExample__StreamScene__) */
