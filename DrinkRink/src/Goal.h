//
//  Goal.h
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#ifndef __TabelToy__Goal__
#define __TabelToy__Goal__

#include "ofMain.h"
#include "Utils.h"
#include "VectorField.h"
#include "Ball.h"

#include "ofxControlPanel.h"

class Goal{
public:
    
    void setup(bool _isLeft, VectorField * _field);
    void reset();
    
    void update(float _deltaTime);
    void draw(float alphaPrc);
    void drawRadialScore(float alphaPrc);
    void drawBoxScore(float alphaPrc);
    
    bool checkIsBallDead(Ball * ball);
    void markScore();
    
    void addInwardCircle(float strength, float range);
    
    void checkPanelValues(ofxControlPanel * panel);
    
    bool isLeft;
    int score;
    float smoothScore, smoothScoreXeno;
    int scoreToWin;
    
    
    VectorField * field;
    float deltaTime;
    
    ofVec2f pos;
    GridPos fieldPos;
    
    //affecting the field
    float farRange, nearRange;
    float farFieldRange, nearFieldRange;
    float farFieldStrength, nearFieldStrength;
    
    //killin' balls like it's murder christams
    float killRange;
    
    //display
    ofColor baseCol;
    bool showDebug;
    
    //score display
    bool useRadialScoreDisplay;
    float scoreBarAlpha;
    float scoreBarHueRange;
    float scoreBarNoiseSpeed;
    
};

#endif /* defined(__TabelToy__Goal__) */
