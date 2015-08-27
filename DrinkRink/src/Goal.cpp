
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
    
    showDebug = true;
    
    //range in pixels
    nearRange = 50;
    farRange = 160;
    //range in field units
    calculateFieldRange();
    
    //strength in field units
    nearFieldStrength = 1.5;
    farFieldStrength = 0.5;
    
    //killing
    killRange = nearRange / 2;
    
    //position this thing
    pos.y = ofGetHeight()/2;
    pos.x = isLeft ? 70 : ofGetWidth()-70;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    
    //some end game effects
    scoreBarWinEffectAlpha = 150;
    winTimeBeforeBarEffect = 1;
    winTimeBetweenBars = 0.1;
    
    goalShrinkTimeOnLoss = 5;
    
}


void Goal::reset(){
    score = 0;
    smoothScore = 0;
    
    hasWon = false;
    hasLost = false;
    gameOverTimer = 0;
    
    //testing
    score = ofRandom(scoreToWin*0.75, scoreToWin*0.99);
}

void Goal::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    if (hasWon || hasLost){
        gameOverTimer += deltaTime;
    }
    
    addInwardCircle(nearFieldStrength, nearFieldRange);
    addInwardCircle(farFieldStrength, farFieldRange);
    
    smoothScore = (1-smoothScoreXeno) * smoothScore + smoothScoreXeno * score;
    
    if (hasLost){
        float goalSizePrc = 1.0 - gameOverTimer/goalShrinkTimeOnLoss;
        goalSizePrc = MAX(0,goalSizePrc);
        if (farRange > 0){
            farRange = startingFarRange * goalSizePrc;
            nearRange = startingNearRange * goalSizePrc;
            calculateFieldRange();
        }
    }else{
        //just save these values for use later
        startingFarRange = farRange;
        startingNearRange = nearRange;
    }
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
    ofCircle(pos.x, pos.y, killRange);
    
    if (showDebug){
        ofNoFill();
        ofSetColor(10, 255*alphaPrc);
        ofCircle(pos.x, pos.y, killRange);
        ofCircle(pos.x, pos.y, nearRange);
        ofCircle(pos.x, pos.y, farRange);
    }
    
    
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
        
        float hue = baseHue +  (ofNoise(ofGetElapsedTimef()*scoreBarNoiseSpeed, i)-0.5) * scoreBarHueRange;
        if (hue < 0)    hue += 255;
        if (hue > 255)  hue -=255;
        ofColor thisCol;
        thisCol.setHsb(hue, baseSat, baseBri);
        thisCol.a = scoreBarAlpha*alphaPrc;
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
        bool doWinEffectForThisBar = hasWon && gameOverTimer > (float)i*winTimeBetweenBars + winTimeBeforeBarEffect;
        
        float hue = baseHue +  (ofNoise(ofGetElapsedTimef()*scoreBarNoiseSpeed, i)-0.5) * scoreBarHueRange;
        if (hue < 0)    hue += 255;
        if (hue > 255)  hue -=255;
        
        ofColor thisCol;
        thisCol.setHsb(hue, baseSat, baseBri);
        thisCol.a = scoreBarAlpha*alphaPrc;
        if (doWinEffectForThisBar){
            thisCol.a = scoreBarWinEffectAlpha*alphaPrc;
        }
        ofSetColor(thisCol);
        
        float width = boxSize;
        float winnerOffset = 0;
        if (doWinEffectForThisBar){
            winnerOffset = abs(sin(ofGetElapsedTimef()*5+(float)i*0.3) * 10);
            //float winnerOffset = abs(sin(ofGetElapsedTimef()*5+(float)i*PI*0.5) * 10);
        }
        
        if (i == numBoxes-1){
            width *= finalBoxPrc;
        }
        if (!isLeft){
            width *= -1;
            winnerOffset *= -1;
        }
        
        float xPos = i*boxSize;
        if (!isLeft){
            xPos = ofGetWidth()-i*boxSize;
        }
        
        
        ofRect(xPos-winnerOffset, 0, width+winnerOffset*2, ofGetHeight());
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
    if (score >= scoreToWin){
        score = scoreToWin; //no going higher
        hasWon = true;
    }
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

void Goal::calculateFieldRange(){
    
    nearFieldRange = (float)( (nearRange / (float)field->externalWidth) * field->fieldWidth);
    farFieldRange = (float)( (farRange / (float)field->externalWidth) * field->fieldWidth);
}


void Goal::checkPanelValues(ofxControlPanel * panel){
    
    if (hasWon || hasLost){
        return;
    }
    
    string sideName = isLeft ? "LEFT" : "RIGHT";
    
    //goal
    
    scoreToWin = panel->getValueI("GOAL_SCORE_TO_WIN");
    
    baseCol.setHsb( panel->getValueI("GOAL_HUE_"+sideName) , panel->getValueF("GOAL_SAT"), panel->getValueF("GOAL_BRI"));
    
    float xPadding = panel->getValueF("GOAL_X_DIST_FROM_EDGE");
    float yPadding = panel->getValueF("GOAL_Y_PRC_FROM_EDGE") * ofGetHeight();
    pos.x = isLeft ? xPadding : ofGetWidth()-xPadding;
    pos.y = isLeft ? ofGetHeight()-yPadding : yPadding;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    nearRange = panel->getValueF("GOAL_NEAR_RANGE");
    farRange = panel->getValueF("GOAL_FAR_RANGE");
    calculateFieldRange();
    
    nearFieldStrength = panel->getValueF("GOAL_NEAR_FIELD_STRENGTH");
    farFieldStrength = panel->getValueF("GOAL_FAR_FIELD_STRENGTH");
    
    killRange = panel->getValueF("GOAL_KILL_RANGE");
    
    showDebug = panel->getValueB("GOAL_SHOW_DEBUG");
    
    //score display
    
    useRadialScoreDisplay = panel->getValueB("GOAL_USE_RADIAL");
    
    scoreBarAlpha = panel->getValueF("GOAL_SCORE_BAR_ALPHA");
    scoreBarHueRange = panel->getValueF("GOAL_SCORE_BAR_HUE_RANGE");
    scoreBarNoiseSpeed = panel->getValueF("GOAL_SCORE_BAR_NOISE_SPEED");
    
    smoothScoreXeno = panel->getValueF("GOAL_SCORE_XENO");
    
    if (panel->getValueB("GOAL_ADD_SCORE_"+sideName)){
        markScore();
        panel->setValueB("GOAL_ADD_SCORE_"+sideName, false);
    }
    
    
    /*
    
    panel.addPanel("Goals Score Display", 1, false);
    panel.setWhichPanel("Goals Score Display");
    panel.setWhichColumn(0);
    
    panel.addToggle("Use Radial Score Display", "GOAL_USE_RADIAL", false);
    
    panel.addSlider("Score Bar Alpha", "GOAL_SCORE_BAR_ALPHA", 50, 0, 255, false);
    panel.addSlider("Score Bar Hue Range", "GOAL_SCORE_BAR_HUE_RANGE", 30, 0, 255, false);
    panel.addSlider("Score Bar Noise Speed", "GOAL_SCORE_BAR_NOISE_SPEED", 0.1, 0, 1, false);
    
    panel.addSlider("Score Smoothing Speed", "GOAL_SCORE_XENO", 0.25, 0, 1, false);
    
    panel.addToggle("Add Score Left", "GOAL_ADD_SCORE_LEFT", false);
    panel.addToggle("Add Score Left", "GOAL_ADD_SCORE_RIGHT", false);
     */
}

