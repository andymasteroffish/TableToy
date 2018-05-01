//
//  WigglerBGShape.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 5/1/18.
//
//

#include "WigglerBGShape.hpp"

void WigglerBGShape::setup(int _gameWidth, int _gameHeight){
    gameWidth = _gameWidth;
    gameHeight = _gameHeight;
    reset();
    
    
    timer = ofRandom(0, shrinkTime);
}

void WigglerBGShape::reset(){
    
    pos.x = ofRandom(0, gameWidth);
    pos.y = ofRandom(0, gameHeight);
    
    timer = 0;
    
    rotSpeed = 1;
    
    fullSize = ofRandom(80,120);
    overShootSize = fullSize * 1.2;
    
    float timeMod = 3;
    growTime = 0.4 * timeMod;
    overShootTime = growTime + 0.1 * timeMod;
    pauseTime = overShootTime + 1.5 * timeMod;
    overShootTime2 = pauseTime + 0.1 * timeMod;
    shrinkTime = overShootTime2 + 0.3 * timeMod;
    
    mainCol = ofRandom(0,40);
    mainAlpha = ofRandom(20, 70);
    
    outlineCol = ofRandom(0, 40);
    outlineAlpha = ofRandom(90, 130);
    
}

void WigglerBGShape::update(float deltaTime){
    timer += deltaTime;
    
    
    
}

void WigglerBGShape::draw(float alphaPrc){
    
    float thisSize = 0;
    
    if (timer < growTime){
        float prc = timer/growTime;
        thisSize = prc * overShootSize;
    }
    else if (timer < overShootTime){
        float prc = (timer-growTime)/(overShootTime-growTime);
        thisSize = (1.0-prc)*overShootSize + prc * fullSize;
    }
    else if (timer < pauseTime){
        float prc = (timer-overShootTime)/(pauseTime-overShootTime);
        float ang = prc * TWO_PI;
        thisSize = fullSize + sin(ang) * 10;
    }
    else if (timer < overShootTime2){
        float prc = (timer-pauseTime)/(overShootTime2-pauseTime);
        thisSize = (1.0-prc)*fullSize + prc * overShootSize;
    }
    else if (timer < shrinkTime){
        float prc = (timer-overShootTime2)/(shrinkTime-overShootTime2);
        thisSize = (1.0-prc) * fullSize;
    }else{
        reset();
    }
    
    
    float innerSize = thisSize*0.8;
    float outterSize = thisSize*1.1;
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    ofSetColor(mainCol, mainAlpha * alphaPrc);
    ofCircle(0, 0, innerSize);
    
    //draw the ring
    ofSetLineWidth(2);
    ofSetColor(outlineCol, outlineAlpha * alphaPrc);
    int numPoints = 20;
    float angleStep = TWO_PI/(float)numPoints;
    float startAngle = ofGetElapsedTimef() * rotSpeed;
    for (int i=0; i<numPoints; i+=2){
        float angleA = i*angleStep + startAngle;
        float angleB = (i+1)*angleStep + startAngle;
        ofPoint pntA( cos(angleA) * outterSize, sin(angleA) * outterSize);
        ofPoint pntB( cos(angleB) * outterSize, sin(angleB) * outterSize);
        ofLine(pntA, pntB);
    }
    
    
    ofPopMatrix();
}