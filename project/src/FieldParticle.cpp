//
//  FieldParticle.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "FieldParticle.h"


FieldParticle::FieldParticle(float x,
                             float y, ofColor _col){
    setup(x,y, _col);
}

void FieldParticle::setup(float x, float y, ofColor _col){
    //killTime = 3;
    killVel = 0.01;
    
    velToStartFading = 1;
    pos.set(x,y);
    vel.set(0,0);
    //fric = 0.8;
    col.set( _col );
    
    timer = 0;
    
    killFlag = false;
    
    noiseSeed = ofRandom(99999);
    
    setAlpha();
    
    
    //testing effects
//    showDot = false;
//    dotSize = 2;
//    
//    useNoiseWiggle = false;
//    noiseWiggleRange = PI;
//    noiseWigglePower = 0.2f;
//    
//    useTrails = false;
//    numTrailPositions = 40;
//    trailStartWidth = 0.5;  //making either trail start or end very big is interesting
//    trailEndWidth = 2.5;
//    trailPos.clear();
//    
//    usePic = true;
//    picScale = 1;

}

void FieldParticle::update(float deltaTime, VectorField * field){
    vel += field->getForceFromPos(pos) * 0.5;
    vel *= fric;
    pos += vel;
    
    timer += deltaTime;
    if (timer > killTime || ( abs(vel.x) < killVel && abs(vel.y) < killVel) ){
        //cout<<"kill it at "<<timer<<endl;
        killFlag = true;
    }
    
    //testing - this does make a kind of good wiggle
    if (useNoiseWiggle){
        float curAngle = atan2(vel.y, vel.y);
        float power = vel.length() * noiseWigglePower;
        float newAngle = curAngle + ofMap( ofNoise( ofGetElapsedTimef()*3, noiseSeed), 0, 1, -noiseWiggleRange, noiseWiggleRange);
        vel.x += sin(newAngle) * power;
        vel.y += cos(newAngle) * power;
    }
    
    if (useTrails){
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
    
    if (usePic){
        ofSetColor(col.r, col.g, col.b, col.a * alphaPrc);
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(noiseSeed);
        ofScale(picScale, picScale);
        pic->draw(0,0, pic->width/2, pic->height/2);
        ofPopMatrix();
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

