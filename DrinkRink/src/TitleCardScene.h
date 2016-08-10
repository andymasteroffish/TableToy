//
//  TitleCardScene.h
//  emptyExample
//
//  Created by Andy Wallace on 7/2/15.
//
//

#ifndef __emptyExample__TitleCardScene__
#define __emptyExample__TitleCardScene__

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"

class TitleCardScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    void addTower(CupInfo thisCup);
    
    ofFbo fbo;
    
#define NUM_TITLE_PICS 3
    ofImage titleCardPic[NUM_TITLE_PICS];
    int curPic;
    float frameRate;
    float frameTimer;
    
    float killTime;
    
};

#endif /* defined(__emptyExample__TitleCardScene__) */
