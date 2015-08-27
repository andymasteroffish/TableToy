//
//  BallParticle.h
//  DrinkRink
//
//  Created by Andy Wallace on 8/27/15.
//
//

#ifndef DrinkRink_BallParticle_h
#define DrinkRink_BallParticle_h

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
    
    void setup(ofVec2f _pos, ofVec2f _targetPos, ofColor _col){
        timer = 0;
        timeBeforePullingIn = 0.3;
        timeToPullIn = 0.2;
        targetPos = _targetPos;
        
        pos = _pos;
        col = _col;
        
        col.r += ofRandom(-10,10);
        col.g += ofRandom(-10,10);
        col.b += ofRandom(-10,10);
        
        //cance of being black
        if (ofRandomuf() < 0.15){
            col = ofColor::black;
        }
        
        fric = 1.0-0.2;
        killTime = timeBeforePullingIn + timeToPullIn;
        
        float force = ofRandom(5,20);
        float startAngle = ofRandom(TWO_PI);
        vel.x = cos(startAngle)*force;
        vel.y = sin(startAngle)*force;
        cout<<"shet ip it dup"<<endl;
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
        ofSetCircleResolution(3);
        ofCircle(pos, 5);
        ofSetCircleResolution(20);
    }
    
};


#endif
