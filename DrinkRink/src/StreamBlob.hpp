//
//  StreamBlob.hpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#ifndef StreamBlob_hpp
#define StreamBlob_hpp

#include "ofMain.h"

class StreamBlob{
public:
    
    void draw();
    
    vector<ofVec2f> points;
    ofVec2f center;
    
};

#endif /* StreamBlob_hpp */
