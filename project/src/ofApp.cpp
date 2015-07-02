#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofBackground(10);
    
    curScene = new SportsScene();
    curScene->setup();
    curScene->reset();
    
    showField = false;
    showDebugInfo = true;
    showFieldParticles = true;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
//clears everythign and gets the toy ready for a new mode
void ofApp::reset(){
    
    curScene->reset();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofShowCursor(); //the mouse was being hidden for some reason
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    curScene->update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(showField){
        ofSetColor(0,130,130, 200);
        curScene->field.debugDraw();
    }
    
    
    curScene->draw();
    
    
    
    if (showFieldParticles){
        for (int i=curScene->fieldParticles.size()-1; i>=0; i--){
            curScene->fieldParticles[i]->draw();
        }
    }
    
    

    if(showDebugInfo){
        string modeName = "";
        
        modeName = curScene->sceneName;
        
        ofSetColor(255,0,0);
        string debugInfo =  "fps: "+ofToString(ofGetFrameRate());
        debugInfo +=        "\nmode: "+modeName;
        debugInfo +=        "\nf - toggle field";
        debugInfo +=        "\np - toggle particles";
        debugInfo +=        "\nh - toggle info";
        debugInfo +=        "\nm - toggle mode";
        debugInfo +=        "\na - add cup";
        debugInfo +=        "\nr - randomize balls";
        debugInfo +=        "\nclick & drag to move";
        debugInfo +=        "\nright click & drag to spin";
        ofDrawBitmapString(debugInfo, 10,15);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 'f'){
        showField = !showField;
    }
    if (key == 'p'){
        showFieldParticles = !showFieldParticles;
    }
    if (key == 'h'){
        showDebugInfo = !showDebugInfo;
    }
    
    /*
    if (key == 'a'){
        addCup();
    }
    
    if (key == 'm'){
        reset();
        
        curMode = (ModeType) ((curMode+1)%NUM_MODES);
        
        if (curMode == MODE_BALL)   startBallMode();
        if (curMode == MODE_STREAM) startStreamMode();
    }
    
    if (key == 'r'){
        for (int i=0; i<balls.size(); i++){
            balls[i]->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        }
    }
     */

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    //field.addOutwardCircle((float)x, (float)y, 100, 1);
//    
//    for (int i=0; i<towers.size(); i++){
//        towers[i]->onMouseDrag(x, y, button);
//    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    for (int i=0; i<towers.size(); i++){
//        towers[i]->onMouseDown(x, y, button);
//    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    for (int i=0; i<towers.size(); i++){
//        towers[i]->onMouseRelease(x, y, button);
//    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}












