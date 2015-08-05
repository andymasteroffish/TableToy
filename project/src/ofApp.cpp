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
    showPanel = true;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
    
    //testing
    for (int i=0; i<3; i++){
        cupTracker.debugAddCup(0);
    }
    for (int i=1; i<=2; i++){
        cupTracker.debugAddCup(i);
    }
    
    //panel.setup("settings", ofGetWidth()-310, -60, 300, 1000);
    panel.setup("settings", ofGetWidth()-310, -60, 300, 1000);
    
    panel.addPanel("Particle Settings", 1, false);
    panel.setWhichPanel("Particle Settings");
    panel.setWhichColumn(0);
    
    panel.addSlider("Friction", "PARTICLE_FRICTION", 0.2, 0, 1, false);
    panel.addSlider("Max Lifespan", "PARTICLE_KILL_TIME", 3, 0, 15, false);
    
    //panel.addLabel("Dot");
    panel.addToggle("Show Dot", "SHOW_DOT", true);
    panel.addToggle("Fill Dot", "FILL_DOT", true);
    panel.addSlider("Dot Size", "DOT_SIZE", 2, 0, 10, false);
   
    //panel.addLabel("Tail");
    panel.addToggle("Use Trail", "USE_TRAIL", false);
    panel.addSlider("Trail Length", "TRAIL_LENGTH", 40, 1, 100, true);
    panel.addSlider("Trail Start Thickness", "TRAIL_START_THICKNESS", 0.5, 0, 25, false);
    panel.addSlider("Trail End Thickness", "TRAIL_END_THICKNESS", 2.5, 0, 25, false);
    
    //panel.addLabel("Image");
    panel.addToggle("Use Pic", "USE_PIC", false);
    panel.addSlider("Pic Scale", "PIC_SCALE", 1, 0, 5, false);
    
    //panel.addLabel("Wiggle");
    panel.addToggle("Use Noise Wiggle", "USE_NOISE_WIGGLE", false);
    panel.addSlider("Wiggle Range", "NOISE_WIGGLE_RANGE", PI, 0, TWO_PI, false);
    panel.addSlider("Wiggle Power", "NOISE_WIGGLE_POWER", 0.2, 0, 0.75, false);
    panel.addSlider("Wiggle Noise Rate", "NOISE_WIGGLE_RATE", 3, 0, 5, false);
    
    
    
    panel.addPanel("Grid", 1, false);
    panel.setWhichPanel("Grid");
    panel.setWhichColumn(0);
    
    panel.addSlider("Grid Drawing Adjust", "GRID_DRAWING_ADJUST", 15, 0, 30, false);
    panel.addToggle("Show Vertical Grid", "SHOW_VERTICAL_GRID", false);
    panel.addToggle("Show Horizontal Grid", "SHOW_HORIZONTAL_GRID", false);
    panel.addToggle("Show Grid Fill", "SHOW_GRID_FILL", false);
    
    panel.addSlider("Grid Val Threshold", "GRID_VAL_THRESHOLD", 0.1, 0, 3, false);
    panel.addSlider("Grid Val Ceiling", "GRID_VAL_CEILING", 4, 0, 10, false);
    
    panel.addToggle("Use Grid Wiggle", "USE_GRID_WIGGLE", false);
    panel.addSlider("Grid Wiggle Speed", "GRID_WIGGLE_SPEED", 1, 0, 4, false);
    panel.addSlider("Grid Wiggle Strength", "GRID_WIGGLE_STRENGTH", 4, 0, 12, false);
    
    panel.addToggle("Use Line Fade", "USE_GRID_LINE_FADE", false);
    panel.addToggle("Use Varrying Line Widths", "USE_GRID_VARRYING_LINE_WIDTH", false);
    
    panel.addSlider("Min Line Width", "GRID_MIN_LINE_WIDTH", 0.5, 0, 6, false);
    panel.addSlider("Max Line Width", "GRID_MAX_LINE_WIDTH", 4, 0, 6, false);
    
    panel.addToggle("Show Vertical Grid Curved", "SHOW_VERTICAL_GRID_CURVED", false);
    panel.addToggle("Show Horizontal Grid Curved", "SHOW_HORIZONTAL_GRID_CURVED", false);
    
    
    panel.addPanel("Presets", 1, false);
    panel.setWhichPanel("Presets");
    panel.setWhichColumn(1);
    
    panel.addToggle("Preset 0", "PRESET_0", false);
    panel.addToggle("Preset 1", "PRESET_1", false);
    panel.addToggle("Preset 2", "PRESET_2", false);
    panel.addToggle("Preset 3", "PRESET_3", false);
    
    
    
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
    
    //update the panel
    panel.update();
    //check preset buttons
    for (int i=0; i<4; i++){
        if (panel.getValueB("PRESET_"+ofToString(i))){
            panel.setValueB("PRESET_"+ofToString(i), false);
            setPreset(i);
        }
    }
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    curScene->update(deltaTime, &panel);
    
    //if we have a scene fading out, keep updating it until it is done
    if (fadingScene != NULL){
        fadingScene->update(deltaTime, &panel);
        if (fadingScene->isDoneFading){
            fadingScene = NULL;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    curScene->draw();
    
    if(showField){
        ofSetColor(0,130,130, 200);
        curScene->field.debugDraw();
    }
    
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
        debugInfo +=        "\np - toggle panel";
        debugInfo +=        "\nleft & right - switch panel";
        debugInfo +=        "\nc - show cup tracker";
        debugInfo +=        "\nm - scroll mode";
        debugInfo +=        "\n0-9 - add cup";
        debugInfo +=        "\nr - randomize balls";
        debugInfo +=        "\nclick & drag to move";
        debugInfo +=        "\nDEL while draging to remove";
        debugInfo +=        "\nright click & drag to spin";
        ofDrawBitmapString(debugInfo, 10,15);
    }
    
    if (showPanel){
        ofSetColor(255);
        ofFill();
        //panel.setPosition( ofGetWidth()-310, 0 );
        panel.draw();
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
    if (key == 'p'){
        showPanel = !showPanel;
        if (!showPanel){
            panel.mouseReleased();
        }
    }
    
    if (key == OF_KEY_LEFT){
        panel.setSelectedPanel(0);
    }
    if (key == OF_KEY_RIGHT){
        panel.setSelectedPanel(1);
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
    
    if (showPanel){
        panel.mousePressed(x,y,button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    cupTracker.mouseDragged(x, y, button);
    
    if (showPanel){
        panel.mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    cupTracker.mouseReleased(x, y, button);
    
    if (showPanel){
        panel.mouseReleased();
    }
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



//--------------------------------------------------------------
void ofApp::setPreset(int idNum){
    cout<<"do something"<<endl;
}









