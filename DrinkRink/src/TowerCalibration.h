//
//  TowerCalibration.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/26/15.
//
//

#ifndef DrinkRink_TowerCalibration_h
#define DrinkRink_TowerCalibration_h

#include "ofMain.h"
#include "Tower.h"

class TowerCalibration : public Tower{
public:
    
    void customSetup(){
        //showDebugImage = false;
    }
    
    void customDraw(float alphaPrc){
        
        ofNoFill();
        int ringOffset = 5;
        for (int i=-2; i<=2; i++){
        
            if (i==0){
                ofSetColor(150,150,255, 255*alphaPrc);
            }else{
                ofSetColor(255,150,150, 255*alphaPrc);
            }
            
            ofCircle(pos.x, pos.y, towerSize + i*ringOffset);
        }
        
        //lines
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        
        ofRotate( -angle * RAD_TO_DEG );
        
        int linePadding = towerSize + 3*ringOffset;
        int lineNum = 8;
        for (int i=0; i<lineNum; i++){
            float thisAngle = (TWO_PI/(float)lineNum) * i;
            ofLine(0,0, cos(thisAngle)*linePadding, sin(thisAngle)*linePadding);
        }
        
        ofPopMatrix();
        
        ofSetColor(150,150,255, 255*alphaPrc);
        ofDrawBitmapString("#"+ofToString(uniqueID), pos.x, pos.y+linePadding+15);
        
    }
    
    
};

#endif
