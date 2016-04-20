//
//  FieldParticle.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "FieldParticle.h"

FieldParticle::FieldParticle(){
    setup(0,0);
}
FieldParticle::FieldParticle(float x, float y){
    setup(x,y);
}

void FieldParticle::setup(float x, float y){
    killVel = 0.01;
    
    velToStartFading = 1;
    pos.set(x,y);
    vel.set(0,0);
    
    timer = 0;
    
    killFlag = false;
    
    noiseSeed = ofRandom(99999);
    
    setAlpha();
    
}

void FieldParticle::update(float deltaTime, VectorField * field){
    if (field != NULL){
        vel += field->getForceFromPos(pos) * 0.5;
    }
    vel *= fric;
    pos += vel;
    
    timer += deltaTime;
    if (timer > killTime || ( abs(vel.x) < killVel && abs(vel.y) < killVel) ){
        //cout<<"kill it at "<<timer<<endl;
        killFlag = true;
    }
    
    if (useNoiseWiggle){
        float angleAdjust = ofMap( ofNoise( ofGetElapsedTimef()*noiseWiggleRate, noiseSeed), 0, 1, -noiseWiggleRange, noiseWiggleRange);
        vel *= 1+noiseWigglePower;
        vel.rotateRad( angleAdjust );
    }
    
    if (useTrails && ofGetFrameNum()%2==0){
        trailPos.push_back(pos);
        if (trailPos.size() > numTrailPositions){
            trailPos.erase(trailPos.begin());
        }
    }
    
    setAlpha();
    
}

void FieldParticle::draw(float alphaPrc){
    
    if (showDot){
        ofSetColor(col.r, col.g, col.b, col.a * alphaPrc);
        if (fillDot){
            ofFill();
        }else{
            ofNoFill();
        }
        ofCircle(pos, dotSize);
    }
    
    if (useTrails && trailPos.size() > 2){
        float fadeVal = (col.a * alphaPrc) / numTrailPositions;
        for (int i=trailPos.size()-1; i>=1; i--){
            ofSetColor(col.r, col.g, col.b, fadeVal*i);
            ofSetLineWidth( ofMap(i, 0, trailPos.size(), trailStartWidth, trailEndWidth));
            ofLine(trailPos[i], trailPos[i-1]);
        }
    }
}

void FieldParticle::setAlpha(){
    float maxVel = MAX( abs(vel.x), abs(vel.y) );
    if (maxVel < velToStartFading){
        float prct = maxVel/velToStartFading;
        col.a = prct * 255;
    }else{
        col.a = 255;
    }

    //also start to fade if it is running out of time
    float timeLeft = killTime-timer;
    float timeToFade = 0.4;
    if ( timeLeft < timeToFade ){
        float newAlpha = (timeLeft/timeToFade) * 255;
        col.a = MIN(newAlpha, col.a);
    }
    
}


void FieldParticle::setType(ParticleType type){
    if (type == PARTICLE_SPORT){
        fric = 1.0-0.2;
        killTime = 3;
        showDot = true;
        fillDot = true;
        dotSize = 2;
        useTrails = false;
        numTrailPositions = 10;
        trailStartWidth = 0.5;
        trailEndWidth = 2.5;
        useNoiseWiggle = true;
        noiseWiggleRange = 0.3;
        noiseWigglePower = 0.1;
        noiseWiggleRate = 2;
        
        float thisSat = 238;
        float thisBri = 164;
        float thisHue = 0;
        int hueID = (int)ofRandom(5);
        if (hueID == 0) thisHue = 28;
        if (hueID == 1) thisHue = 4;
        if (hueID == 2) thisHue = 99;
        if (hueID == 3) thisHue = 38;
        if (hueID == 4) thisHue = 28;
        
        col.setHsb(thisHue, thisSat, thisBri);
    }
    
    if (type == PARTICLE_GOAL_LEFT || type == PARTICLE_GOAL_RIGHT){
        setType(PARTICLE_SPORT);
        
        useNoiseWiggle = false;
        
        float thisSat = 238;
        float thisBri = 164;
        float thisHue =  type == PARTICLE_GOAL_LEFT ? 7 : 154;
        col.setHsb(thisHue, thisSat, thisBri);
    }
    
    if (type == PARTICLE_STREAM){
        
        fric = 0.84;
        killTime = ofRandom(2.5,4);
        showDot = true;
        fillDot = true;
        dotSize = ofRandom(1,4);
        useTrails =  ofRandomuf() > 0.9;
        numTrailPositions = ofRandom(5,14);
        trailStartWidth = ofRandom(0.5,2);
        trailEndWidth = ofRandom(0.5,2);
        useNoiseWiggle = ofRandomuf() > 0.97;
        noiseWiggleRange = 0.15;
        noiseWigglePower = 0.10;
        noiseWiggleRate = 1.3;
        
        col.setHsb(0, 0, ofRandom(50,255));
        
    }
}

