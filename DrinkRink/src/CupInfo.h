//
//  CupInfo.h
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#ifndef emptyExample_CupInfo_h
#define emptyExample_CupInfo_h

class CupInfo{
public:
    //int typeID; //KILL THIS
    int uniqueID;
    ofVec2f pos;
    ofVec2f camPos;
    float angle;
    float startTime;
    
    int framesWithoutUpdate;
};


#endif
