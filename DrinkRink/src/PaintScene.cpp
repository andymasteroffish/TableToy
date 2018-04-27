//
//  PaintScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/27/18.
//
//

#include "PaintScene.hpp"

//--------------------------------------------------------------------------------------------
void PaintScene::setupCustom(){
    sceneName = "paint";
    
    fbo.allocate(gameWidth, gameHeight);
    
    paperPic.loadImage("paint/paper.jpg");
    paperFadePic.loadImage("paint/paper_fade_trans.png");
    
    brushes.resize(4);
    for (int i=0; i<brushes.size(); i++){
        brushes[i].loadImage("paint/brush"+ofToString(i)+".png");
    }
    
}

//--------------------------------------------------------------------------------------------
void PaintScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    panel->addSlider("bg fade", "PAINT_BG_FADE", 1, 0, 100, true);
    
    
    panel->addSlider("saturation", "PAINT_SAT", 255, 0, 255, true);
    panel->addSlider("brightness", "PAINT_BRI", 225, 0, 255, true);
    
    panel->addSlider("paint chance", "PAINT_CHANCE", 0.2, 0, 1, false);
    
    panel->addSlider("min scale", "PAINT_MIN_SCALE", 0.2, 0, 2, false);
    panel->addSlider("max scale", "PAINT_MAX_SCALE", 1.2, 0, 2, false);
    
    

}

//--------------------------------------------------------------------------------------------
void PaintScene::resetCustom(){
    cupTracker->useCups = false;
    
    fbo.begin();
    ofClear(249, 247, 217);
    
//    ofSetColor(255);
//    for (int x=0; x<gameWidth; x+=paperPic.getWidth()){
//        paperPic.draw(x,0);
//    }
    fbo.end();
}

//--------------------------------------------------------------------------------------------
void PaintScene::checkPanelValuesCustom(ofxControlPanel * panel){
    
    bgFade              = panel->getValueI("PAINT_BG_FADE");
    
    saturaiton          = panel->getValueI("PAINT_SAT");
    brightness          = panel->getValueI("PAINT_BRI");
    
    chanceToDrawPoint   = panel->getValueF("PAINT_CHANCE");
    
    minScale            = panel->getValueF("PAINT_MIN_SCALE");
    maxScale            = panel->getValueF("PAINT_MAX_SCALE");
    
    
}

//--------------------------------------------------------------------------------------------
void PaintScene::updateCustom(){
    
    fbo.begin();
    
    //fade
//    if (ofGetFrameNum() % 5 == 0){
//        ofSetColor(255, bgFade);
//        for (int x=0; x<gameWidth; x+=paperPic.getWidth()){
//            paperPic.draw(x,0);
//        }
//    }

    ofSetColor(249, 247, 217, bgFade);
    ofFill();
    ofRect(0, 0, gameWidth, gameHeight);
    
    //paint!
    for (int b=0; b<cupTracker->blobs.size(); b++){
        ofColor col;
        col.setHsb((int)cupTracker->blobs[b].randVal%255, saturaiton, brightness);
        ofSetColor(col);
        for (int i=0; i<cupTracker->blobs[b].points.size(); i++){
            if (ofRandomuf() < chanceToDrawPoint){
                int idNum = ofRandom(brushes.size());
                
                ofPushMatrix();
                ofTranslate(cupTracker->blobs[b].points[i].x, cupTracker->blobs[b].points[i].y);
                
                ofRotate(ofRandom(260));
                
                float scale = ofRandom(minScale, maxScale);
                ofScale(scale, scale);
                
                brushes[idNum].draw( -brushes[idNum].getWidth()/2, -brushes[idNum].getHeight()/2);
                
                ofPopMatrix();
            }
        }
    }
    
    fbo.end();
    
    
    
}

//--------------------------------------------------------------------------------------------
void PaintScene::drawBackgroundCustom(){
    
}

//--------------------------------------------------------------------------------------------
void PaintScene::drawCustom(){
    
    ofSetColor(255, 255*alphaPrc);
    fbo.draw(0,0);
    
    
    
    
    
}

//--------------------------------------------------------------------------------------------
void PaintScene::keyPressed(int key){
    
}