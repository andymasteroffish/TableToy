//
//  DeepPathScene.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/20/18.
//
//

#ifndef DeepPathScene_hpp
#define DeepPathScene_hpp

#include "ofMain.h"
#include "Scene.h"


class DeepPathScene : public Scene{
public:
    
    
    void setupCustom();
    void setupPanelValues(ofxControlPanel * panel);
    void resetCustom();
    void checkPanelValuesCustom(ofxControlPanel * panel);
    void updateCustom();
    
    void drawBackgroundCustom();
    void drawCustom();
    
    void keyPressed(int key);
    
    void moveFloorRowToBack(int row);
    
    float camSpeed;
    ofVec3f camPos, camLookAtPoint;
    ofEasyCam cam;
    
    ofVec3f origin;
    
    ofLight areaLight;
    
#define FLOOR_GRID_WIDTH 60
#define FLOOR_GRID_DEPTH 50
    ofVec3f floorPoints[FLOOR_GRID_WIDTH][FLOOR_GRID_DEPTH];
    
    float floorSpacing;
    int curFurthestFloorRow;
    

    int killTime;
    
};

#endif /* DeepPathScene_hpp */
