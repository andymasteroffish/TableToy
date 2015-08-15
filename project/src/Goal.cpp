
//
//  Goal.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "Goal.h"


void Goal::setup(bool _isLeft, VectorField * _field){
    
    field = _field;
    
    isLeft = _isLeft;
    
    if (isLeft){
        baseCol = ofColor::red;
    }else{
        baseCol = ofColor::blue;
    }
    
    scoreToWin = 40;
    
    smoothScoreXeno = 0.25;
    
    useRadialScoreDisplay = false;
    
    //range in pixels
    closeRange = 50;
    farRange = 160;
    //range in field units
    closeFieldRange = (float)( (closeRange / (float)field->externalWidth) * field->fieldWidth);
    farFieldRange = (float)( (farRange / (float)field->externalWidth) * field->fieldWidth);
    
    //strength in field units
    closeFieldStrength = 1.5;
    farFieldStrength = 0.5;
    
    //killing
    killRange = closeRange / 2;
    
    //position this thing
    pos.y = ofGetHeight()/2;
    pos.x = isLeft ? 70 : ofGetWidth()-70;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
}


void Goal::reset(){
    score = 0;
    smoothScore = 0;
    
    //testing
    score = ofRandom(scoreToWin*0.25, scoreToWin*0.75);
}

void Goal::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    addInwardCircle(closeFieldStrength, closeFieldRange);
    addInwardCircle(farFieldStrength, farFieldRange);
    
    smoothScore = (1-smoothScoreXeno) * smoothScore + smoothScoreXeno * score;
}

void Goal::draw(float alphaPrc){
    
    if (useRadialScoreDisplay){
        drawRadialScore(alphaPrc);
    }else{
        drawBoxScore(alphaPrc);
    }
    
    
    //show the center
    ofFill();
    ofSetColor(baseCol, 100*alphaPrc);
    ofCircle(pos.x, pos.y, closeRange);
    ofNoFill();
    ofSetColor(10, 255*alphaPrc);
    ofCircle(pos.x, pos.y, closeRange);
    
    
    ofSetColor(0);
    ofDrawBitmapString(ofToString(score), pos.x, pos.y);
    
}


void Goal::drawRadialScore(float alphaPrc){
    //outline
    ofNoFill();
    ofSetColor(10, 255*alphaPrc);
    ofCircle(pos.x, pos.y, farRange);
    
    float curScale = smoothScore/(float)scoreToWin;
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(curScale, curScale);
    
    ofFill();
    int rings = 10;
    float baseHue = baseCol.getHue();
    float baseSat = baseCol.getSaturation();
    float baseBri = baseCol.getBrightness();
    for (int i=0; i<rings; i++){
        float prc = 1 - ( (float)i/(float)rings);
        float size = farRange * prc;
        float hue = baseHue +  ofNoise(ofGetElapsedTimef()*0.1, i) * 30;
        ofColor thisCol;
        thisCol.setHsb(hue, baseSat, baseBri);
        thisCol.a = 150*alphaPrc;
        ofSetColor(thisCol);
        ofCircle(0, 0, size);
    }
    
    ofPopMatrix();
}

void Goal::drawBoxScore(float alphaPrc){
    
    float boxSize = (ofGetWidth()/2)/ (float)scoreToWin;
    
    int numBoxes = ceil(smoothScore);
    float finalBoxPrc = 1 - ((float)numBoxes - smoothScore);
    
    float baseHue = baseCol.getHue();
    float baseSat = baseCol.getSaturation();
    float baseBri = baseCol.getBrightness();
    
    ofFill();
    
    for (int i=0; i<numBoxes; i++){
        float hue = baseHue +  ofNoise(ofGetElapsedTimef()*0.1, i) * 30;
        ofColor thisCol;
        thisCol.setHsb(hue, baseSat, baseBri);
        thisCol.a = 50*alphaPrc;
        ofSetColor(thisCol);
        
        float width = boxSize;
        if (i == numBoxes-1){
            width *= finalBoxPrc;
        }
        if (!isLeft){
            width*=-1;
        }
        
        float xPos = i*boxSize;
        if (!isLeft){
            xPos = ofGetWidth()-i*boxSize;
        }
        
        ofRect(xPos, 0, width, ofGetHeight());
    }
    
    //draw a dividing line
    ofSetColor(baseCol, 100*alphaPrc);
    float lineWidth = 2 * (isLeft ? -1 : 1);
    ofRect(ofGetWidth()/2, 0, lineWidth, ofGetHeight());
}


bool Goal::checkIsBallDead(Ball * ball){
    
    float distSq = ofDistSquared(ball->pos.x, ball->pos.y, pos.x, pos.y);
    
    if (distSq < powf(killRange,2)){
        markScore();
        return true;
    }
    
    return false;
    
}

void Goal::markScore(){
    score++;
}


void Goal::addInwardCircle(float strength, float range){
    Bounds bounds = field->getFieldBounds(fieldPos, range);
    
    for (int x=bounds.topLeft.x; x <= bounds.bottomRight.x; x++){
        for (int y=bounds.topLeft.y; y  <= bounds.bottomRight.y; y++){
            
            float distance = ofDist(fieldPos.x, fieldPos.y, x, y);
            //no divide by 0, pls
            if (distance < 0.0001)  distance = 0.0001;
            
            if (distance < range){
                float prct = 1.0f - (distance / range);
                
                ofVec2f dif;
                dif.x = (x - fieldPos.x);
                dif.y = (y - fieldPos.y);
                dif.normalize();
                
                field->field[x][y] -= dif * strength * prct;
            }
        }
    }
}