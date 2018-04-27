//
//  PaintScene.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/27/18.
//
//

#ifndef PaintScene_hpp
#define PaintScene_hpp

#include "ofMain.h"
#include "Scene.h"

class PaintScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    ofFbo fbo;
    
    ofImage paperPic, paperFadePic;
    
    vector<ofImage> brushes;
    
    int saturaiton, brightness;
    float chanceToDrawPoint;
    float minScale, maxScale;
    
    int bgFade;
    
    float killTime;
    
    
    
};


#endif /* PaintScene_hpp */
