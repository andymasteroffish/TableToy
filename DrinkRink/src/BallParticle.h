//
//  BallParticle.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/27/15.
//
//

#ifndef DrinkRink_BallParticle_h
#define DrinkRink_BallParticle_h

#include "Ball.h"

class BallParticle{
public:
    
    ofVec2f pos, vel;
    
    float timeBeforePullingIn;
    float timeToPullIn;
    float timer;
    ofVec2f targetPos;
    
    ofVec2f lastNaturalPos;
    
    ofColor col;
    float fric;
    float killTime;
    
    int resolution;
    float angle;
    
    void setup(Ball parentBall, ofVec2f _targetPos){
        timer = 0;
        timeBeforePullingIn = 0.3;
        timeToPullIn = 0.2;
        targetPos = _targetPos;
        
        pos = parentBall.pos;
        col = parentBall.col;
        
        col.r += ofRandom(-10,10);
        col.g += ofRandom(-10,10);
        col.b += ofRandom(-10,10);
        
        //chance of being black
        if (ofRandomuf() < 0.15){
            col = ofColor::black;
        }
        
        fric = 1.0-0.2;
        killTime = timeBeforePullingIn + timeToPullIn;
        
        float force = ofRandom(5,20);
        float startAngle = ofRandom(TWO_PI);
        vel.x = cos(startAngle)*force;
        vel.y = sin(startAngle)*force;
        
        resolution = ofRandom(3,6);
        angle = ofRandom(TWO_PI);
        
        //and move it out a bit
        float dist = ofRandom(1, parentBall.drawSize*0.8);
        pos.x += cos(angle) * dist;
        pos.y += sin(angle) * dist;
    }
    
    void update(float deltaTime){
        timer += deltaTime;
        
        vel *= fric;
        pos += vel;
        
        if (timer > timeBeforePullingIn){
            float prc = (timer-timeBeforePullingIn) / timeToPullIn;
            pos = prc * targetPos + (1-prc) * lastNaturalPos;
        }else{
            lastNaturalPos = pos;
        }
        //cout<<"fuck you im real"<<endl;
    }
    
    void draw(float alphaPrc){
        ofSetColor(col.r, col.g, col.b, col.a * alphaPrc);
        ofFill();
        ofSetCircleResolution(resolution);
        ofCircle(pos, 5);
    }
    
};


#endif
