#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofBackground(10);
    
    cupTracker.setup();
    
    scenes[0] = new SportsScene();
    scenes[1] = new StreamScene();
    
    for (int i=0; i<NUM_SCENES; i++){
        scenes[i]->setup(&cupTracker);
    }
    
    curSceneID = -1;
    scrollModes();
    
    
    showField = false;
    showDebugInfo = true;
    showCupDebug = false;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
//clears everythign and gets the toy ready for a new mode
void ofApp::scrollModes(){
    
    if (curSceneID >= 0 && curSceneID <= NUM_SCENES){
        fadingScene = scenes[curSceneID];
        fadingScene->startFade();
    }else{
        fadingScene = NULL;
    }
    
    curSceneID++;
    if (curSceneID >= NUM_SCENES){
        curSceneID = 0;
    }
    
    curScene = scenes[curSceneID];
    curScene->reset();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofShowCursor(); //the mouse was being hidden for some reason
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    curScene->update(deltaTime);
    
    //if we have a scene fading out, keep updating it until it is done
    if (fadingScene != NULL){
        fadingScene->update(deltaTime);
        if (fadingScene->isDoneFading){
            fadingScene = NULL;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(showField){
        ofSetColor(0,130,130, 200);
        curScene->field.debugDraw();
    }
    
    
    curScene->draw();
    
    if (fadingScene != NULL){
        fadingScene->draw();
    }
    
    
    if (showCupDebug){
        cupTracker.debugDraw();
    }
    

    if(showDebugInfo){
        string modeName = "";
        
        modeName = curScene->sceneName;
        
        ofSetColor(255,0,0);
        string debugInfo =  "fps: "+ofToString(ofGetFrameRate());
        debugInfo +=        "\nmode: "+modeName;
        debugInfo +=        "\nf - toggle field";
        debugInfo +=        "\nh - toggle info";
        debugInfo +=        "\nc - show cup tracker";
        debugInfo +=        "\nm - scroll mode";
        debugInfo +=        "\n0-9 - add cup";
        debugInfo +=        "\nr - randomize balls";
        debugInfo +=        "\nclick & drag to move";
        debugInfo +=        "\nDEL while draging to remove";
        debugInfo +=        "\nright click & drag to spin";
        ofDrawBitmapString(debugInfo, 10,15);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 'f'){
        showField = !showField;
    }
    if (key == 'h'){
        showDebugInfo = !showDebugInfo;
    }
    if (key == 'c'){
        showCupDebug = !showCupDebug;
    }
    if (key == 'm'){
        scrollModes();
    }
    
    cupTracker.keyPressed(key);
    
    curScene->keyPressed(key);
    
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    cupTracker.mousePressed(x, y, button);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    cupTracker.mouseDragged(x, y, button);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    cupTracker.mouseReleased(x, y, button);
    
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












