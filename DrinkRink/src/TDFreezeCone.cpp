//
//  TDFreezeCone.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/19/15.
//
//

#include "TDFreezeCone.h"



void TDFreezeCone::setup(Tower * _parentTower, ofxControlPanel * panel){
    parentTower = _parentTower;
    
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
    points.resize(3);
}

void TDFreezeCone::update(float deltaTime, vector<TDFoe> * foes){
    
    timer -= deltaTime;
    
    //set the cone from the parent tower
    pos = parentTower->pos;
    
    float angle = parentTower->angle;
    
    //starts at the tower
    points[0].set(pos);
    
    float range = 350 * spreadPrc;
    float farDist = 150 * spreadPrc;
    
    ofVec2f farPoint(pos.x+cos(angle)*range, pos.y+sin(angle)*range);
    
    points[1].x = farPoint.x + cos(angle-PI/2) * farDist;
    points[1].y = farPoint.y + sin(angle-PI/2) * farDist;
    
    points[2].x = farPoint.x + cos(angle+PI/2) * farDist;
    points[2].y = farPoint.y + sin(angle+PI/2) * farDist;
    
    checkFoes(foes);
}


void TDFreezeCone::draw(float alphaPrc){
    
    ofSetColor(col.r, col.g, col.b, 200*alphaPrc);
    ofFill();

    ofTriangle(points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);
//    ofBeginShape();
//    for (int i=0; i<points.size(); i++){
//        ofVertex(points[i].x, points[i].y);
//    }
//    ofEndShape();
    
    
}

void TDFreezeCone::checkFoes(vector<TDFoe> * foes){
    for (int i=0; i<foes->size(); i++){
        if (isPointInCone(foes->at(i).pos)){
            foes->at(i).freeze(freezeTime);
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
