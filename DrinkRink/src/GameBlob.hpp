//
//  GameBlob.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/25/18.
//
//

#ifndef GameBlob_hpp
#define GameBlob_hpp

#include "ofMain.h"

class GameBlob{
public:
    
    
    vector<ofVec2f> points;
    ofVec2f center;
    float   area;
    float   length;
    
    //for debug
    void draw(){
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofBeginShape();
        for (int i=0; i<points.size(); i++){
            ofVertex(points[i].x, points[i].y);
        }
        ofEndShape();
        
        ofFill();
        ofCircle(center.x, center.y, 4);
    }
};

#endif /* GameBlob_hpp */
