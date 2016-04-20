//
//  StreamBackgroundShape.h
//  DrinkRink
//
//  Created by Andrew Wallace on 1/10/16.
//
//

#ifndef DrinkRink_StreamBackgroundShape_h
#define DrinkRink_StreamBackgroundShape_h

#include "ofMain.h"

class StreamBackgroundShape{
public:
    
    ofVec2f pos;
    float speed;
    float angle;
    float rotSpeed;
    float size;
    int numPoints;
    ofColor col;
    float randVal;
    
    int gameWidth, gameHeight;
    
    void setup(int _gameWidth, int _gameHeight){
        gameWidth = _gameWidth;
        gameHeight = _gameHeight;
        reset();
        pos.x = ofRandom(-size, gameWidth+size);
    }
    
    void reset(){
        
        speed = ofRandom(70,120);
        
        angle = ofRandom(0,360);
        rotSpeed = ofRandom(1,40);
        
        size = ofRandom(200,400);
        pos.x = ofRandom(-size-200, -size);
        pos.y = ofRandom(0-size, gameHeight+size);
        
//        col.setHsb(0, 0, ofRandom(0,30));
//        col.a = ofRandom(155,255);
        
        int val = ofRandom(0,30);
        int alpha = 255;
        col.set(val, val, val, alpha);
        
        numPoints = (int)ofRandom(3,8);
        
        randVal = ofRandom(0,999);
        
    }
    
    void update(float deltaTime){
        pos.x += speed * deltaTime;
        angle += rotSpeed * deltaTime;
        
        if (pos.x > gameWidth+size+50){
            reset();
        }
    }
    
    void draw(float alphaVal){
        ofSetColor(col.r, col.g, col.b, col.a*alphaVal);
        ofSetCircleResolution(numPoints);
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(angle);
        ofCircle(0, 0, size);
        ofPopMatrix();
    }
    
};


#endif
