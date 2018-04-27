//
//  EyeScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#include "EyeScene.hpp"


//--------------------------------------------------------------------------------------------
void EyeScene::setupCustom(){
    sceneName = "eye";
    
    bgCol.set(250, 248, 255);
    
    
    eyeShader.load("eye/shaders/shadersGL2/eye_shader");
    
    vid.loadMovie("eye/CumulusCloudsWebm.mp4");
    
    scanY = ofGetHeight()*0.35;
    scanH = 100;
    
    scanBaseW = 50;
    scanWSpeed = 2;
    
    scanYRange = 300;
    scanYSpeed = 1;
    scanYResetPrc = 0.005;
    scanWChangePrc = 0.02;
    
    curHue = ofRandom(255);
    curSat = ofRandom(255);
    hueDrunkRange = 1;//0.5;
    satDrunkRange = 5;
    
    baseScale = 1;
    
}

//--------------------------------------------------------------------------------------------
void EyeScene::setupPanelValues(ofxControlPanel * panel){
//    panel->addPanel(sceneName, 1, false);
//    panel->setWhichPanel(sceneName);
//    panel->setWhichColumn(0);
    
    
}

//--------------------------------------------------------------------------------------------
void EyeScene::resetCustom(){
    cupTracker->useCups = false;
    vid.play();

    
}

//--------------------------------------------------------------------------------------------
void EyeScene::checkPanelValuesCustom(ofxControlPanel * panel){
}

//--------------------------------------------------------------------------------------------
void EyeScene::updateCustom(){
    vid.update();
    
    scanY += scanYSpeed;
    
    if (scanY > gameHeight + scanYRange){
        scanY = -scanYRange;
    }
    if (scanY < -scanYRange){
        scanY = gameHeight + scanYRange;
    }
    
    if (ofRandomuf() < scanYResetPrc){
        //cout<<"reset"<<endl;
        scanY += ofRandom(-scanYRange, ofGetHeight()+scanYRange);
        scanYSpeed = ofRandom(0.3,4);
        if (ofRandomuf() < 0.2){
            scanYSpeed *= -1;
        }
        scanH = ofRandom(70, 250);
        
    }
    
    if (ofRandomuf() < scanWChangePrc){
        //cout<<"change w"<<endl;
        scanBaseW = ofRandom(30, 120);
    }
    
    scanW = scanBaseW + sin(ofGetElapsedTimef() * scanWSpeed) * 10;
    
    
    curHue += ofRandom(-hueDrunkRange, hueDrunkRange);
    if (curHue > 255){
        curHue -= 255;
    }
    if (curHue < 0){
        curHue += 255;
    }
    
    curSat += ofRandom(-satDrunkRange, satDrunkRange);
    if (curSat > 255){
        curSat = 255;
    }
    if (curSat < 160){
        curSat = 160;
    }
    //cout<<"curSat "<<curSat<<endl;
    
    float scaleRange = 0.2;
    float scaleMod = 1 + sin(ofGetElapsedTimef() * 0.3) * scaleRange;
    curScale = baseScale * scaleMod;
    
}


//--------------------------------------------------------------------------------------------
void EyeScene::drawCustom(){
    ofEnableDepthTest();
    ofSetLineWidth(2);
    
    //the video
    ofColor thisCol;
    thisCol.setHsb(curHue, curSat, 255);
    thisCol.a = 255 * alphaPrc;
    ofSetColor(thisCol);
    ofPushMatrix();
    ofTranslate(0, 0, -10);
    
    vid.draw(-10, -10, ofGetWidth()+20, ofGetHeight()+20);
    ofPopMatrix();
    
    
    
    float centerY = ofGetHeight() / 2.0f;
    
    eyeShader.begin();
    eyeShader.setUniform1f("scanlineY", centerY- scanY);
    eyeShader.setUniform1f("scanlineH", scanH);
    eyeShader.setUniform1f("scanlineMaxOffset", scanW);
    
    
    //the eye
    ofPushMatrix();
    ofTranslate(gameWidth*0.25, gameHeight/2);
    ofScale(curScale, curScale);
    drawEye(0,0, 120, ofGetElapsedTimef(), 0);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(gameWidth*0.75, gameHeight/2);
    ofScale(curScale, curScale);
    drawEye(0,0, 120, ofGetElapsedTimef(), 0);
    ofPopMatrix();
    
    
    eyeShader.end();
    
    
    ofDisableDepthTest();
    
}

//--------------------------------------------------------------
void EyeScene::drawEye(float xPos, float yPos, float size, float time, int depth){
    
    //draw more circles!
    if (size > 10){
        
        int numChildren = 6;
        float angleStep = TWO_PI/(float)numChildren;
        for (int i=0; i<numChildren; i++){
            
            float angle = angleStep * i + (time * (depth + 1))*0.2;
            if (depth % 2==0){
                angle *= -1;
            }
            
            float newSize = size*0.5;
            float newX = xPos + cos(angle)*(size+newSize);
            float newY = yPos + sin(angle)*(size+newSize);
            drawEye(newX, newY, newSize, time, depth+1);
        }
        
    }
    
    //actually draw the circles
    ofSetColor(253, 252, 255, 235 * alphaPrc);
    ofFill();
    ofCircle(xPos, yPos, -depth, size);
    
    ofSetColor(10, 255 * alphaPrc);
    ofNoFill();
    ofCircle(xPos, yPos, -depth, size);
    
    //and an inner circle
    float innerCircleSize = size * 0.2;
    float innerAngle = (time * (depth + 2));
    if (depth % 2==1){
        innerAngle *= -1;
    }
    float innerX = xPos + cos(innerAngle) * (size-innerCircleSize);
    float innerY = yPos + sin(innerAngle) * (size-innerCircleSize);
    
    //ofFill();
    ofCircle(innerX, innerY, -depth+0.1, innerCircleSize);
}

//--------------------------------------------------------------------------------------------
void EyeScene::keyPressed(int key){
    
}