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

class Goal{
public:
    
    void setup(bool _isLeft, VectorField * _field);
    void reset();
    
    void update(float _deltaTime);
    void draw(float alphaPrc);
    
    void addInwardCircle(float strength, float range);
    
    bool isLeft;
    int score;
    
    VectorField * field;
    float deltaTime;
    
    ofVec2f pos;
    GridPos fieldPos;
    
    float farRange, closeRange;
    float farFieldRange, closeFieldRange;
    float farFieldStrength, closeFieldStrength;
    
    ofColor baseCol;
    
};

#endif /* defined(__TabelToy__Goal__) */
