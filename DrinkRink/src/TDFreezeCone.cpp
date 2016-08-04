//
//  TDFreezeCone.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFreezeCone.h"



void TDFreezeCone::setup(Tower * _parentTower, ofImage * _pic, ofxControlPanel * panel){
    parentTower = _parentTower;
    pic = _pic;
    
    //dmg = 0.5;
    //freezeTime = 8;
    //killTime = 1.5;
    freezeTime = panel->getValueF("FREEZE_TOWER_DURATION");
    killTime = panel->getValueF("FREEZE_TOWER_ON_TIME");
    
    //spreadPrc = panel->getValueF("FREEZE_TOWER_SPREAD");
    //SETTING SPREAD PRC EVERY FRAME IN THE SCENE
    
    
    timer = killTime;
    
    col.set(20, 40, 240);
    
    //set the three points
    points.resize(4);
}

void TDFreezeCone::update(float deltaTime, vector<TDFoe> * foes){
    
    timer -= deltaTime;
    
    
    angle = parentTower->curAngle;
    pos = parentTower->pos;
    
    //starts at the tower
    //points[0].set(pos);
    
    float farRange = 440 * spreadPrc;
    float farDist = 160 * spreadPrc;
    
    float nearRange = 140 * spreadPrc;
    float nearDist = 35 * spreadPrc;
    
    ofVec2f farPoint(pos.x+cos(angle)*farRange, pos.y+sin(angle)*farRange);
    ofVec2f nearPoint(pos.x+cos(angle)*nearRange, pos.y+sin(angle)*nearRange);
    
    points[0].x = farPoint.x + cos(angle-PI/2) * farDist;
    points[0].y = farPoint.y + sin(angle-PI/2) * farDist;
    
    points[1].x = farPoint.x + cos(angle+PI/2) * farDist;
    points[1].y = farPoint.y + sin(angle+PI/2) * farDist;
    
    points[2].x = nearPoint.x + cos(angle+PI/2) * nearDist;
    points[2].y = nearPoint.y + sin(angle+PI/2) * nearDist;
    
    points[3].x = nearPoint.x + cos(angle-PI/2) * nearDist;
    points[3].y = nearPoint.y + sin(angle-PI/2) * nearDist;
    
    checkFoes(foes);
}


void TDFreezeCone::draw(float alphaPrc){
    
//    ofSetColor(0,255,0,200);
//    ofFill();    
//    //THIS WILL CRASH THE GAME. COMMENT IT OUT WHEN DONE TESTING
//    ofBeginShape();
//    for (int i=0; i<points.size(); i++){
//        ofVertex(points[i].x, points[i].y);
//    }
//    ofEndShape();
    
    //set the cone from the parent tower
    float offset = 140;
    ofVec2f drawPos;
    drawPos.x = parentTower->pos.x + cos(angle) * offset;
    drawPos.y = parentTower->pos.y + sin(angle) * offset;
    
    ofSetColor(255, 150*alphaPrc);
    ofPushMatrix();
    ofTranslate(drawPos.x, drawPos.y);
    ofRotate( ofRadToDeg(angle));
    pic->draw(0, -pic->getHeight()/2);
    ofPopMatrix();
    
    
    
    
}

void TDFreezeCone::checkFoes(vector<TDFoe> * foes){
    for (int i=0; i<foes->size(); i++){
        if (foes->at(i).delayTimer <= 0){
            if (isPointInCone(foes->at(i).pos)){
                foes->at(i).freeze(freezeTime);
            }
        }
    }
    
}

//this code from http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
bool TDFreezeCone::isPointInCone(ofVec2f point) {
    int i, j, nvert = points.size();
    bool c = false;
    
    for(i = 0, j = nvert - 1; i < nvert; j = i++) {
        if( ( (points[i].y >= point.y ) != (points[j].y >= point.y) ) &&
           (point.x <= (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
           )
            c = !c;
    }
    
    return c;
}
