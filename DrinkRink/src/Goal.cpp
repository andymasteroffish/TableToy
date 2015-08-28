
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
    gameWidth = field->gameWidth;
    gameHeight = field->gameHeight;
    
    isLeft = _isLeft;
    
    if (isLeft){
        baseCol = ofColor::red;
    }else{
        baseCol = ofColor::blue;
    }
    
    scoreToWin = 40;
    
    smoothScoreXeno = 0.25;
    
    showDebug = false;
    
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
    pos.y = gameHeight/2;
    pos.x = isLeft ? 70 : gameWidth-70;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    //showing the score bars
    scoreBarAlpha = 50;
    scoreBarHueRange = 30;
    scoreBarNoiseSpeed = 0.1;
    smoothScoreXeno = 0.25;
    
    //effects
    goalBorderJumpTime = 0.3;
    goalBorderJumpRange = 20;
    
    
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
    //score = ofRandom(scoreToWin*0.6, scoreToWin*0.8);
}

void Goal::update(float _deltaTime){
    deltaTime = _deltaTime;
    
    goalBorderJumpTimer += deltaTime;
    
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
    
    drawBoxScore(alphaPrc);
    
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
    
    //show a hash line
    int numPoints = 16;
    float angleChunk = TWO_PI/(float)numPoints;
    float bonusDist = 0;
    if (goalBorderJumpTimer < goalBorderJumpTime){
        float prc = 1.0 - goalBorderJumpTimer / goalBorderJumpTime;
        bonusDist = goalBorderJumpRange * prc;
    }
    ofSetLineWidth(3);
    for (int i=0; i<numPoints-1; i+=2){
        float angle1 = angleChunk * i + ofGetElapsedTimef();
        float angle2 = angle1 - angleChunk;
        ofPoint pnt1(pos.x + cos(angle1)*(nearRange+bonusDist) , pos.y + sin(angle1)*(nearRange+bonusDist));
        ofPoint pnt2(pos.x + cos(angle2)*(nearRange+bonusDist) , pos.y + sin(angle2)*(nearRange+bonusDist));
        
        float transitionRange = 0.4;
        float colorPrc = ofMap( sin(ofGetElapsedTimef()), -transitionRange, transitionRange, 0, 1, true);
        if (i%4 == 0){
            colorPrc = 1-colorPrc;
        }
        
        ofSetColor(baseCol.r*colorPrc, baseCol.g*colorPrc, baseCol.b*colorPrc, 200*alphaPrc);
        ofLine(pnt1, pnt2);
    }
    
    
//    ofSetColor(0);
//    ofDrawBitmapString(ofToString(score), pos.x, pos.y);
    
}



void Goal::drawBoxScore(float alphaPrc){
    
    float boxSize = (gameWidth/2)/ (float)scoreToWin;
    
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
            xPos = gameWidth-i*boxSize;
        }
        
        
        ofRect(xPos-winnerOffset, 0, width+winnerOffset*2, gameHeight);
    }
    
    //draw a dividing line
    ofSetColor(baseCol, 100*alphaPrc);
    float lineWidth = 2 * (isLeft ? -1 : 1);
    ofRect(gameWidth/2, 0, lineWidth, gameHeight);
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
    goalBorderJumpTimer = 0;
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
                
                field->field[x][y].vel -= dif * strength * prct;
                
                field->field[x][y].addPotentialParticleType( isLeft ? PARTICLE_GOAL_LEFT : PARTICLE_GOAL_RIGHT , 1);
            }
        }
    }
}

void Goal::calculateFieldRange(){
    nearFieldRange = (float)( (nearRange / (float)field->gameWidth) * field->fieldWidth);
    farFieldRange = (float)( (farRange / (float)field->gameWidth) * field->fieldWidth);
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
    float yPadding = panel->getValueF("GOAL_Y_PRC_FROM_EDGE") * gameHeight;
    pos.x = isLeft ? xPadding : gameWidth-xPadding;
    pos.y = isLeft ? gameHeight-yPadding : yPadding;
    fieldPos = field->getInternalPointFromExternal(pos.x, pos.y);
    
    nearRange = panel->getValueF("GOAL_NEAR_RANGE");
    farRange = panel->getValueF("GOAL_FAR_RANGE");
    calculateFieldRange();
    
    nearFieldStrength = panel->getValueF("GOAL_NEAR_FIELD_STRENGTH");
    farFieldStrength = panel->getValueF("GOAL_FAR_FIELD_STRENGTH");
    
    killRange = panel->getValueF("GOAL_KILL_RANGE");
    
    showDebug = panel->getValueB("GOAL_SHOW_DEBUG");
    
    //score display
    
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

