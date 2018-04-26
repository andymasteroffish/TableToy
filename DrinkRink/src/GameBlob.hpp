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
    
    int uniqueID;
    float randVal;  //does nothing by itself but can be referenced in scenes if useful
    
    //for tracking - don't use in scene
    bool foundThisFrame;
    
    void setup(int _id){
        uniqueID = _id;
        randVal = ofRandom(0,9999);
    }
    
    
    void update(ofVec2f _center, float _area, float _length, vector<ofVec2f> blobPnts){
        foundThisFrame = true;
        
        center.set(_center.x, _center.y);
        area = _area;
        length = _length;
        
        points.clear();
        for (int i=0; i<blobPnts.size(); i++){
            ofVec2f pnt;
            pnt.x = blobPnts[i].x;
            pnt.y = blobPnts[i].y;
            points.push_back(pnt);
        }
    }
    
    
    //for debug
    void draw(){
        float hue = (int)randVal % 255;
        ofColor col;
        col.setHsb(hue, 255, 255);
        ofSetColor(col);
        
        ofNoFill();
        ofBeginShape();
        for (int i=0; i<points.size(); i++){
            ofVertex(points[i].x, points[i].y);
        }
        ofEndShape();
        
        ofFill();
        ofCircle(center.x, center.y, 4);
        
        ofDrawBitmapString(ofToString(uniqueID), center.x, center.y-5);
    }
};

#endif /* GameBlob_hpp */
