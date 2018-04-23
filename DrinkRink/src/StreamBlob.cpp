//
//  StreamBlob.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#include "StreamBlob.hpp"

void StreamBlob::draw(){
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