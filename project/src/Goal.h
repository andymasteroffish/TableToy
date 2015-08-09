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

class Goal{
public:
    
    void setup(bool _isLeft, VectorField * _field);
    void reset();
    
    void update(float _deltaTime);
    void draw(float alphaPrc);
    
    bool checkIsBallDead(Ball * ball);
    void markScore();
    
    void addInwardCircle(float strength, float range);
    
    bool isLeft;
    int score;
    float smoothScore, smoothScoreXeno;
    int scoreToWin;
    
    VectorField * field;
    float deltaTime;
    
    ofVec2f pos;
    GridPos fieldPos;
    
    //affecting the field
    float farRange, closeRange;
    float farFieldRange, closeFieldRange;
    float farFieldStrength, closeFieldStrength;
    
    //killin' balls like it's murder christams
    float killRange;
    
    //display
    ofColor baseCol;
    
};

#endif /* defined(__TabelToy__Goal__) */
