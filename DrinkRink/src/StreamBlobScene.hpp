//
//  StreamBlobScene.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#ifndef StreamBlobScene_hpp
#define StreamBlobScene_hpp

#include "ofMain.h"
#include "Scene.h"

#include "StreamBackgroundShape.h"

class StreamBlobScene : public Scene{
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
    
    
    
    vector<StreamBackgroundShape> bgShapes;
    
    float killTime;
    
    float blobForce;
    
    bool drawDebugBobs;
    
    
};

#endif /* StreamBlobScene_hpp */
