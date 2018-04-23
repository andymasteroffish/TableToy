//
//  EyeScene.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#ifndef EyeScene_hpp
#define EyeScene_hpp

#include "ofMain.h"
#include "Scene.h"

#include "Tower.h"
#include "TowerRock.h"

#include "StreamBackgroundShape.h"

class EyeScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawCustom();
    void drawEye(float xPos, float yPos, float size, float time, int depth);
    
    void keyPressed(int key);
    
    
    ofShader eyeShader;
    
    float scanY, scanH, scanW;
    
    float scanYRange;
    float scanYSpeed;
    float scanYResetPrc;
    
    float scanBaseW;
    float scanWSpeed;
    float scanWChangePrc;
    
    ofVideoPlayer vid;
    
    float curHue, curSat;
    float hueDrunkRange, satDrunkRange;
    
    float baseScale;
    float curScale;
    
    
    
    float killTime;
    
};


#endif /* EyeScene_hpp */
