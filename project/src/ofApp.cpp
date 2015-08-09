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
    showDebugInfo = false;
    showCupDebug = false;
    showPanel = false;
    
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
    curPanel = 0;
    
    panel.addPanel("Presets", 1, false);
    panel.setWhichPanel("Presets");
    panel.setWhichColumn(0);
    
    panel.addLabel("PRESETS");
    
    panel.addToggle("Pastel", "PRESET_0", false);
    panel.addToggle("wiggler", "PRESET_1", false);
    panel.addToggle("Cyber Adventure", "PRESET_2", false);
    panel.addToggle("Blazing Suns", "PRESET_3", false);
    panel.addToggle("Desert", "PRESET_4", false);
    panel.addToggle("No Love/Deep Web", "PRESET_5", false);
    panel.addToggle("Blank", "PRESET_6", false);
    
    panel.addPanel("Particle Settings", 1, false);
    panel.setWhichPanel("Particle Settings");
    panel.setWhichColumn(0);
    
    panel.addLabel("PARTICLES");
    
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
    
    panel.addLabel("GRID");
    
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
    
    
    panel.addPanel("Colors", 1, false);
    panel.setWhichPanel("Colors");
    panel.setWhichColumn(0);
    
    panel.addLabel("COLORS");
    
    panel.addSlider("BG Hue",       "BG_HUE", 126, 0, 255, true);
    panel.addSlider("BG Saturation","BG_SAT", 7, 0, 255, true);
    panel.addSlider("BG Brightness","BG_BRI", 255, 0, 255, true);
    
    panel.addSlider("Ball Hue",       "BALL_HUE", 0, 0, 255, true);
    panel.addSlider("Ball Saturation","BALL_SAT", 178, 0, 255, true);
    panel.addSlider("Ball Brightness","BALL_BRI", 202, 0, 255, true);
    
    panel.addSlider("Grid Hue",       "GRID_HUE", 0, 0, 255, true);
    panel.addSlider("Grid Saturation","GRID_SAT", 0, 0, 255, true);
    panel.addSlider("Grid Brightness","GRID_BRI", 0, 0, 255, true);
    
    
    panel.addPanel("Particle Colors", 1, false);
    panel.setWhichPanel("Particle Colors");
    panel.setWhichColumn(0);
    
    panel.addLabel("PARTICLE COLORS");
    
    panel.addSlider("Particle Saturation","PARTICLE_SAT", 255, 0, 255, true);
    panel.addSlider("Particle Brightness","PARTICLE_BRI", 191, 0, 255, true);
    panel.addSlider("Particle Hue",     "PARTICLE_HUE_0", 42, 0, 255, true);
    panel.addSlider("Particle Hue",     "PARTICLE_HUE_1", 55, 0, 255, true);
    panel.addSlider("Particle Hue",     "PARTICLE_HUE_2", 131, 0, 255, true);
    panel.addSlider("Particle Hue",     "PARTICLE_HUE_3", 79, 0, 255, true);
    panel.addSlider("Particle Hue",     "PARTICLE_HUE_4", 195, 0, 255, true);
    
    
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
    for (int i=0; i<7; i++){
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
        ofSetColor(255);
        string panelInfo = ofToString(curPanel+1)+"/"+ofToString(panel.panels.size());
        ofDrawBitmapString(panelInfo, ofGetWidth()-50, ofGetHeight()-5);
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
        curPanel--;
        if (curPanel < 0){
            curPanel = panel.panels.size()-1;
        }
        
        panel.setSelectedPanel(curPanel);
    }
    if (key == OF_KEY_RIGHT){
        curPanel++;
        if (curPanel >= panel.panels.size()){
            curPanel = 0;
        }
        panel.setSelectedPanel(curPanel);
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
    
    cout<<"preset: "<<idNum<<endl;
    
    //set some base values
    
    //particles
    panel.setValueF("PARTICLE_FRICTION", 0.2);
    panel.setValueF("PARTICLE_KILL_TIME", 3);
    panel.setValueB("SHOW_DOT", true);
    panel.setValueB("FILL_DOT", true);
    panel.setValueF("DOT_SIZE", 2);
    panel.setValueB("USE_TRAIL", false);
    panel.setValueF("TRAIL_LENGTH", 40);
    panel.setValueF("TRAIL_START_THICKNESS", 0.5);
    panel.setValueF("TRAIL_END_THICKNESS", 2.5);
    panel.setValueB("USE_PIC", false);
    panel.setValueF("PIC_SCALE", 1);
    panel.setValueB("USE_NOISE_WIGGLE", false);
    panel.setValueF("NOISE_WIGGLE_RANGE", PI);
    panel.setValueF("NOISE_WIGGLE_POWER", 0.2);
    panel.setValueF("NOISE_WIGGLE_RATE", 3);
    
    //grid
    panel.setValueF("GRID_DRAWING_ADJUST", 15);
    panel.setValueB("SHOW_VERTICAL_GRID", false);
    panel.setValueB("SHOW_HORIZONTAL_GRID", false);
    panel.setValueB("SHOW_GRID_FILL", false);
    panel.setValueF("GRID_VAL_THRESHOLD", 0.1);
    panel.setValueF("GRID_VAL_CEILING", 4);
    panel.setValueB("USE_GRID_WIGGLE", false);
    panel.setValueF("GRID_WIGGLE_SPEED", 1);
    panel.setValueF("GRID_WIGGLE_STRENGTH", 4);
    panel.setValueB("USE_GRID_LINE_FADE", false);
    panel.setValueB("USE_GRID_VARRYING_LINE_WIDTH", false);
    panel.setValueF("GRID_MIN_LINE_WIDTH", 0.5);
    panel.setValueF("GRID_MAX_LINE_WIDTH", 4);
    panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
    panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
    
    //colors
    panel.setValueI("BG_HUE", 126);
    panel.setValueI("BG_SAT", 7);
    panel.setValueI("BG_BRI", 255);
    panel.setValueI("BALL_HUE", 0);
    panel.setValueI("BALL_SAT", 178);
    panel.setValueI("BALL_BRI", 202);
    panel.setValueI("GRID_HUE", 0);
    panel.setValueI("GRID_SAT", 0);
    panel.setValueI("GRID_BRI", 0);
    panel.setValueI("PARTICLE_SAT", 255);
    panel.setValueI("PARTICLE_BRI", 191);
    panel.setValueI("PARTICLE_HUE_0", 42);
    panel.setValueI("PARTICLE_HUE_1", 55);
    panel.setValueI("PARTICLE_HUE_2", 131);
    panel.setValueI("PARTICLE_HUE_3", 79);
    panel.setValueI("PARTICLE_HUE_4", 195);
    
    
    //pastels
    if (idNum == 0){
        //particles
        panel.setValueF("PARTICLE_FRICTION", 0.22);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", false);
        panel.setValueB("USE_TRAIL", false);
        panel.setValueB("USE_PIC", true);
        panel.setValueF("PIC_SCALE", 1.6);
        panel.setValueB("USE_NOISE_WIGGLE", false);
        
        //grid
        panel.setValueB("SHOW_VERTICAL_GRID", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID", false);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
        
        //colors
        panel.setValueI("BG_HUE", 43);
        panel.setValueI("BG_SAT", 25);
        panel.setValueI("BG_BRI", 255);
        panel.setValueI("BALL_HUE", 151);
        panel.setValueI("BALL_SAT", 164);
        panel.setValueI("BALL_BRI", 109);
        panel.setValueI("PARTICLE_SAT", 198);
        panel.setValueI("PARTICLE_BRI", 196);
        panel.setValueI("PARTICLE_HUE_0", 235);
        panel.setValueI("PARTICLE_HUE_1", 172);
        panel.setValueI("PARTICLE_HUE_2", 25);
        panel.setValueI("PARTICLE_HUE_3", 204);
        panel.setValueI("PARTICLE_HUE_4", 209);
    }
    
    //wiggler
    if (idNum == 1){
        //particles
        panel.setValueF("PARTICLE_FRICTION", 0.2);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", true);
        panel.setValueB("FILL_DOT", true);
        panel.setValueF("DOT_SIZE", 2);
        panel.setValueB("USE_TRAIL", true);
        panel.setValueF("TRAIL_LENGTH", 40);
        panel.setValueF("TRAIL_START_THICKNESS", 0.5);
        panel.setValueF("TRAIL_END_THICKNESS", 2.5);
        panel.setValueB("USE_PIC", false);
        panel.setValueF("PIC_SCALE", 1);
        panel.setValueB("USE_NOISE_WIGGLE", true);
        panel.setValueF("NOISE_WIGGLE_RANGE", PI);
        panel.setValueF("NOISE_WIGGLE_POWER", 0.2);
        panel.setValueF("NOISE_WIGGLE_RATE", 3);
        
        //grid
        panel.setValueB("SHOW_VERTICAL_GRID", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID", false);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
        
        //colors
        panel.setValueI("BG_HUE", 126);
        panel.setValueI("BG_SAT", 0);
        panel.setValueI("BG_BRI", 250);
        panel.setValueI("BALL_HUE", 212);
        panel.setValueI("BALL_SAT", 155);
        panel.setValueI("BALL_BRI", 128);
        panel.setValueI("GRID_HUE", 0);
        panel.setValueI("GRID_SAT", 0);
        panel.setValueI("GRID_BRI", 0);
        panel.setValueI("PARTICLE_SAT", 238);
        panel.setValueI("PARTICLE_BRI", 164);
        panel.setValueI("PARTICLE_HUE_0", 28);
        panel.setValueI("PARTICLE_HUE_1", 4);
        panel.setValueI("PARTICLE_HUE_2", 99);
        panel.setValueI("PARTICLE_HUE_3", 38);
        panel.setValueI("PARTICLE_HUE_4", 28);
    }
    
    //cyber adventure
    if (idNum == 2){
        //particles
        panel.setValueF("PARTICLE_FRICTION", 0.12);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", true);
        panel.setValueB("FILL_DOT", false);
        panel.setValueF("DOT_SIZE", 3);
        panel.setValueB("USE_TRAIL", true);
        panel.setValueF("TRAIL_LENGTH", 45);
        panel.setValueF("TRAIL_START_THICKNESS", 1);
        panel.setValueF("TRAIL_END_THICKNESS", 1);
        panel.setValueB("USE_PIC", false);
        panel.setValueB("USE_NOISE_WIGGLE", false);
        
        //grid
        panel.setValueF("GRID_DRAWING_ADJUST", 8.8);
        panel.setValueB("SHOW_VERTICAL_GRID", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID", false);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueF("GRID_VAL_THRESHOLD", 0.1);
        panel.setValueF("GRID_VAL_CEILING", 4);
        panel.setValueB("USE_GRID_WIGGLE", false);
        panel.setValueF("GRID_WIGGLE_SPEED", 1);
        panel.setValueF("GRID_WIGGLE_STRENGTH", 4);
        panel.setValueB("USE_GRID_LINE_FADE", false);
        panel.setValueB("USE_GRID_VARRYING_LINE_WIDTH", false);
        panel.setValueF("GRID_MIN_LINE_WIDTH", 0.5);
        panel.setValueF("GRID_MAX_LINE_WIDTH", 4);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", true);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", true);
        
        //colors
        panel.setValueI("BG_HUE", 185);
        panel.setValueI("BG_SAT", 41);
        panel.setValueI("BG_BRI", 22);
        panel.setValueI("BALL_HUE", 111);
        panel.setValueI("BALL_SAT", 226);
        panel.setValueI("BALL_BRI", 255);
        panel.setValueI("GRID_HUE", 48);
        panel.setValueI("GRID_SAT", 94);
        panel.setValueI("GRID_BRI", 48);
        panel.setValueI("PARTICLE_SAT", 34);
        panel.setValueI("PARTICLE_BRI", 191);
        panel.setValueI("PARTICLE_HUE_0", 255);
        panel.setValueI("PARTICLE_HUE_1", 255);
        panel.setValueI("PARTICLE_HUE_2", 255);
        panel.setValueI("PARTICLE_HUE_3", 255);
        panel.setValueI("PARTICLE_HUE_4", 255);
    }
    
    //suns
    if (idNum == 3){
        //particles
        panel.setValueF("PARTICLE_FRICTION", 0.2);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", false);
        panel.setValueB("USE_TRAIL", true);
        panel.setValueF("TRAIL_LENGTH", 40);
        panel.setValueF("TRAIL_START_THICKNESS", 25);
        panel.setValueF("TRAIL_END_THICKNESS", 2.5);
        panel.setValueB("USE_PIC", false);
        panel.setValueB("USE_NOISE_WIGGLE", true);
        panel.setValueF("NOISE_WIGGLE_RANGE", PI);
        panel.setValueF("NOISE_WIGGLE_POWER", 0.275);
        panel.setValueF("NOISE_WIGGLE_RATE", 2.65);
        
        //grid
        panel.setValueF("GRID_DRAWING_ADJUST", 15);
        panel.setValueB("SHOW_VERTICAL_GRID", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID", false);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
        
        //colors
        panel.setValueI("BG_HUE", 131);
        panel.setValueI("BG_SAT", 18);
        panel.setValueI("BG_BRI", 255);
        panel.setValueI("BALL_HUE", 0);
        panel.setValueI("BALL_SAT", 178);
        panel.setValueI("BALL_BRI", 202);
        panel.setValueI("GRID_HUE", 0);
        panel.setValueI("GRID_SAT", 0);
        panel.setValueI("GRID_BRI", 0);
        panel.setValueI("PARTICLE_SAT", 255);
        panel.setValueI("PARTICLE_BRI", 218);
        panel.setValueI("PARTICLE_HUE_0", 202);
        panel.setValueI("PARTICLE_HUE_1", 46);
        panel.setValueI("PARTICLE_HUE_2", 2);
        panel.setValueI("PARTICLE_HUE_3", 34);
        panel.setValueI("PARTICLE_HUE_4", 48);
    }
    
    //desert
    if (idNum == 4){
        panel.setValueF("PARTICLE_FRICTION", 0.2);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", true);
        panel.setValueB("FILL_DOT", false);
        panel.setValueF("DOT_SIZE", 1);
        panel.setValueB("USE_TRAIL", false);
        panel.setValueB("USE_PIC", false);
        panel.setValueB("USE_NOISE_WIGGLE", false);
        
        //grid
        panel.setValueF("GRID_DRAWING_ADJUST", 15);
        panel.setValueB("SHOW_VERTICAL_GRID", true);
        panel.setValueB("SHOW_HORIZONTAL_GRID", false);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueF("GRID_VAL_THRESHOLD", 0.0);
        panel.setValueF("GRID_VAL_CEILING", 1.2);
        panel.setValueB("USE_GRID_WIGGLE", true);
        panel.setValueF("GRID_WIGGLE_SPEED", 1);
        panel.setValueF("GRID_WIGGLE_STRENGTH", 4);
        panel.setValueB("USE_GRID_LINE_FADE", true);
        panel.setValueB("USE_GRID_VARRYING_LINE_WIDTH", false);
        panel.setValueF("GRID_MIN_LINE_WIDTH", 0.5);
        panel.setValueF("GRID_MAX_LINE_WIDTH", 1.3);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
        
        //colors
        panel.setValueI("BG_HUE", 18);
        panel.setValueI("BG_SAT", 12);
        panel.setValueI("BG_BRI", 255);
        panel.setValueI("BALL_HUE", 62);
        panel.setValueI("BALL_SAT", 178);
        panel.setValueI("BALL_BRI", 202);
        panel.setValueI("GRID_HUE", 0);
        panel.setValueI("GRID_SAT", 212);
        panel.setValueI("GRID_BRI", 196);
        panel.setValueI("PARTICLE_SAT", 36);
        panel.setValueI("PARTICLE_BRI", 160);
        panel.setValueI("PARTICLE_HUE_0", 42);
        panel.setValueI("PARTICLE_HUE_1", 55);
        panel.setValueI("PARTICLE_HUE_2", 131);
        panel.setValueI("PARTICLE_HUE_3", 79);
        panel.setValueI("PARTICLE_HUE_4", 195);
    }
    
    //deep web
    if (idNum == 5){
        //particles
        panel.setValueF("PARTICLE_FRICTION", 0.2);
        panel.setValueF("PARTICLE_KILL_TIME", 3);
        panel.setValueB("SHOW_DOT", false);
        panel.setValueB("USE_TRAIL", true);
        panel.setValueF("TRAIL_LENGTH", 40);
        panel.setValueF("TRAIL_START_THICKNESS", 0.5);
        panel.setValueF("TRAIL_END_THICKNESS", 2.5);
        panel.setValueB("USE_PIC", false);
        panel.setValueB("USE_NOISE_WIGGLE", false);
        
        //grid
        panel.setValueF("GRID_DRAWING_ADJUST", 13);
        panel.setValueB("SHOW_VERTICAL_GRID", true);
        panel.setValueB("SHOW_HORIZONTAL_GRID", true);
        panel.setValueB("SHOW_GRID_FILL", false);
        panel.setValueF("GRID_VAL_THRESHOLD", 0.1);
        panel.setValueF("GRID_VAL_CEILING", 1.9);
        panel.setValueB("USE_GRID_WIGGLE", true);
        panel.setValueF("GRID_WIGGLE_SPEED", 1);
        panel.setValueF("GRID_WIGGLE_STRENGTH", 4);
        panel.setValueB("USE_GRID_LINE_FADE", true);
        panel.setValueB("USE_GRID_VARRYING_LINE_WIDTH", true);
        panel.setValueF("GRID_MIN_LINE_WIDTH", 0);
        panel.setValueF("GRID_MAX_LINE_WIDTH", 2.87);
        panel.setValueB("SHOW_VERTICAL_GRID_CURVED", false);
        panel.setValueB("SHOW_HORIZONTAL_GRID_CURVED", false);
        
        //colors
        panel.setValueI("BG_HUE", 199);
        panel.setValueI("BG_SAT", 5);
        panel.setValueI("BG_BRI", 218);
        panel.setValueI("BALL_HUE", 209);
        panel.setValueI("BALL_SAT", 171);
        panel.setValueI("BALL_BRI", 140);
        panel.setValueI("GRID_HUE", 147);
        panel.setValueI("GRID_SAT", 204);
        panel.setValueI("GRID_BRI", 144);
        panel.setValueI("PARTICLE_SAT", 195);
        panel.setValueI("PARTICLE_BRI", 85);
        panel.setValueI("PARTICLE_HUE_0", 127);
        panel.setValueI("PARTICLE_HUE_1", 126);
        panel.setValueI("PARTICLE_HUE_2", 127);
        panel.setValueI("PARTICLE_HUE_3", 131);
        panel.setValueI("PARTICLE_HUE_4", 127);
    }
}









