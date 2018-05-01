//
//  WigglerScene.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/1/18.
//
//

#ifndef WigglerScene_hpp
#define WigglerScene_hpp

#include "ofMain.h"
#include "Scene.h"
#include "WigglerBGShape.hpp"

class WigglerScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    
    float blobForce;
    
    float particleFric;
    float particleWiggleRange;
    float particleWigglePower;
    float particleWiggleRate;
    float particleKillTime;
    
    vector<WigglerBGShape> bgShapes;
    
    
};

#endif /* WigglerScene_hpp */
