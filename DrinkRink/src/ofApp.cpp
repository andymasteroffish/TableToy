#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofBackground(200,200,255);
    
    ofHideCursor();
    
    
    gameWidth =  2560;//2720;//1770;//1500;
    gameHeight = 800;// 768;//500;//420;//500;
    
    fbo.allocate(gameWidth, gameHeight);
    
    usingDebugCupTracker = USE_DEBUG_CUP_TRACKER;
    
    if (usingDebugCupTracker){
        cupTracker = new CupTrackerDebug();
    }else{
        cupTracker = new CupTrackerCam();
    }
    
    cupTracker->setup(gameWidth, gameHeight);
    scenes[SCENE_CALIBRATION]   = new CalibrationScene();
    scenes[SCENE_TITLE_CARD]    = new TitleCardScene();
    scenes[SCENE_SPORTS]        = new SportsScene();
    scenes[SCENE_STREAM]        = new StreamScene();
    scenes[SCENE_TOWER_DEFENSE] = new TowerDefenseScene();
    scenes[SCENE_BEAM]          = new BeamScene();
    //scenes[SCENE_FLYERS] = new FlyersScene();
    
    for (int i=0; i<NUM_SCENES; i++){
        scenes[i]->setup(cupTracker, gameWidth, gameHeight);
        if (usingDebugCupTracker){
            scenes[i]->showCupDebug = false;
        }
    }
    
    curSceneID = -100;
    setScene(SCENE_CALIBRATION);
    if (usingDebugCupTracker){
        setScene(SCENE_TOWER_DEFENSE);
    }
    
    setupPanel();
    
    //on the actual table, make sure you default to using the full scale
    if (!usingDebugCupTracker){
        panel.setValueF("DISPLAY_SCALE", 1.0);
    }
    
    showField = false;
    showDebugInfo = false;
    showCupDebug = false;
    showPanel = true;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
    
    
}
//--------------------------------------------------------------
void ofApp::setupPanel(){
    panel.setup("settings", ofGetWidth()-310, 0, 300, ofGetHeight());
    curPanel = 0;
    
    
    panel.addPanel("Cam Setup", 1, false);
    panel.setWhichPanel("Cam Setup");
    panel.setWhichColumn(0);
    
    panel.addSlider("display scale", "DISPLAY_SCALE", 1, 0.5, 10, false);
    panel.addSlider("display adjust x", "DISPLAY_ADJUST_X", 0, -300, 300, false);
    panel.addSlider("display adjust y", "DISPLAY_ADJUST_Y", 0, -300, 300, false);
    
    
    panel.addToggle("Take BG pic", "CAM_TAKE_BG_PIC", false);
    panel.addToggle("Use Auto Threshold (ARToolKit)", "CAM_AUTO_THRESHOLD", false);
    panel.addSlider("X Offset", "CAM_X_OFFSET", 0, -100, 100, false);
    panel.addSlider("Y Offset", "CAM_Y_OFFSET", 0, -100, 100, false);
    
    panel.addSlider("Frames before killing cup", "FRAMES_WITH_NO_CUP", 30, 1, 100, true);
    
    //the 4 warp points
//    for (int i=0; i<4; i++){
//        if (i==0) panel.addLabel("Top Left Warp");
//        if (i==1) panel.addLabel("Top Right Warp");
//        if (i==2) panel.addLabel("Bottom Right Warp");
//        if (i==3) panel.addLabel("Bottom Left Warp");
//        float xVal = i==0 || i==3 ? 0 : 1;
//        float yVal = i<2 ? 0 : 1;
//        panel.addSlider("X Prc", "CAM_WARP_X_"+ofToString(i), xVal, 0, 1, false);
//        panel.addSlider("Y Prc", "CAM_WARP_Y_"+ofToString(i), yVal, 0, 1, false);
//    }
    
    
    
    panel.addPanel("Cam Position", 1, false);
    panel.setWhichPanel("Cam Position");
    panel.setWhichColumn(0);
    
    panel.addSlider("Threshold", "CAM_THRESHOLD", 31, 0, 255, true);
    panel.addToggle("cam 0 on left", "CAM_0_ON_LEFT", true);
    panel.addToggle("flip cams Horizontal", "CAMS_FLIP_HORZ", true);
    panel.addToggle("flip cams Vertical", "CAMS_FLIP_VERT", false);
    panel.addSlider("left cam rotate", "CAM_LEFT_ROT", 0, -5, 5, false);
    panel.addSlider("right cam rotate", "CAM_RIGHT_ROT", 0, -5, 5, false);
    panel.addSlider("cam 0 x adjust", "CAM_0_X", 8.9, -100, 100, false);
    panel.addSlider("cam 0 y adjust", "CAM_0_Y", -5, -100, 100, false);
    panel.addSlider("cam 1 x adjust", "CAM_1_X", -7.3, -100, 100, false);
    panel.addSlider("cam 1 y adjust", "CAM_1_Y", 5.4, -100, 100, false);
    panel.addToggle("flip cam adjusts", "CAM_FLIP_ADJUSTS", false);
    
    //calibrating the cups
    panel.addSlider("cup left X", "CUPS_LEFT_X", 195.6, -100, gameWidth, false);
    panel.addSlider("cup right X", "CUPS_RIGHT_X", 2453.1, 0, gameWidth+100, false);
    panel.addSlider("cup top Y", "CUPS_TOP_Y", -80, -100, gameHeight, false);
    panel.addSlider("cup bottom Y", "CUPS_BOTTOM_Y", 810, 0, gameHeight+100, false);
    
    
    panel.addSlider("cup x adjust left", "CUPS_ADJUST_X_LEFT", 53.3, -300, 300, false);
    panel.addSlider("cup top y adjust left", "CUPS_ADJUST_Y_TOP_LEFT", 33.3, -300, 300, false);
    panel.addSlider("cup bot y adjust left", "CUPS_ADJUST_Y_BOT_LEFT", -30, -300, 300, false);
    panel.addSlider("cup x adjust right", "CUPS_ADJUST_X_RIGHT", 63.3, -300, 300, false);
    panel.addSlider("cup top y adjust right", "CUPS_ADJUST_Y_TOP_RIGHT", 10, -300, 300, false);
    panel.addSlider("cup bot y adjust right", "CUPS_ADJUST_Y_BOT_RIGHT", -60, -300, 300, false);
    
    //Thresholding
    panel.addPanel("Threshold Zone Top", 1, false);
    panel.setWhichPanel("Threshold Zone Top");
    panel.setWhichColumn(0);
    
    panel.addToggle("show threshold lines", "SHOW_THRESH_LINES", true);
    
    for (int i=0; i<12; i++){
        panel.addSlider("threshold slider "+ofToString(i), "THRESH_ZONE_"+ofToString(i), 28, 0, 255, true);
    }
    
    panel.addPanel("Threshold Zone Bottom", 1, false);
    panel.setWhichPanel("Threshold Zone Bottom");
    panel.setWhichColumn(0);
    for (int i=12; i<24; i++){
        panel.addSlider("threshold slider "+ofToString(i), "THRESH_ZONE_"+ofToString(i), 28, 0, 255, true);
    }
    
    //fucksing with the right screen
    panel.addPanel("Screen Adjust", 1, false);
    panel.setWhichPanel("Screen Adjust");
    panel.setWhichColumn(0);
    
    panel.addSlider("left screen x adjust", "LEFT_SCREEN_X_ADJUST", -4.5, -100, 100, false);
    panel.addSlider("left screen y adjust", "LEFT_SCREEN_Y_ADJUST", 6.7, -100, 100, false);
    panel.addSlider("left screen rotation", "LEFT_SCREEN_ROTATION", 0.1, -15, 15, false);
    
    panel.addSlider("right screen x adjust", "RIGHT_SCREEN_X_ADJUST", -4.5, -100, 100, false);
    panel.addSlider("right screen y adjust", "RIGHT_SCREEN_Y_ADJUST", 6.7, -100, 100, false);
    panel.addSlider("right screen rotation", "RIGHT_SCREEN_ROTATION", 0.1, -15, 15, false);
    
    //throwing idle settings onto this screen too
    panel.addLabel("");
    panel.addLabel("idle settings");
    
    panel.addSlider("min cup move", "IDLE_MOVE_THRESH", 2, 1, 25, false);
    panel.addSlider("min cup rotate", "IDLE_ROTATE_THRESH", 0.2, 0.1, PI, false);
    
    //Some generic sldiers to hook into while testing
    panel.addPanel("Generic Testing", 1, false);
    panel.setWhichPanel("Generic Testing");
    panel.setWhichColumn(0);
    
    
    for (int i=0; i<10; i++){
        panel.addSlider("test slder "+ofToString(i), "TEST_SLIDER_"+ofToString(i), 0.5, 0, 1, false);
    }
    
    
    //go through each scene and allow them to add their own panel things
    for (int i=0; i<NUM_SCENES; i++){
        scenes[i]->setupPanelValues(&panel);
    }
    
    curPanel = 1;
    panel.setSelectedPanel(curPanel);
    
    //set the game to be at 50% display scale if we're using the debugger tracker because that means it's on a laptop and won't be two screens wide
    if (usingDebugCupTracker){
        panel.setValueF("DISPLAY_SCALE", 0.5);
        
        panel.setValueF("RIGHT_SCREEN_X_ADJUST", 0);
        panel.setValueF("RIGHT_SCREEN_Y_ADJUST", 0);
        panel.setValueF("RIGHT_SCREEN_ROTATION", 0);
    }
    
    panel.loadSettings("controlPanelSettings.xml");
}

//--------------------------------------------------------------
void ofApp::scrollScenes(){
    
    //if the order list is empty, repopulate it
    if (sceneOrder.size() == 0){
        randomizeSceneOrder();
        
        //make sure that the first scene is not the one we just came from
        while (sceneOrder[0] == curSceneID){
            randomizeSceneOrder();
        }
    }
    
    //if we were not on the title card, go there,
    if (curSceneID != SCENE_TITLE_CARD){
        setScene(SCENE_TITLE_CARD);
        return;
    }
    
    //otherwise, go to the next main scene
    int thisSceneID = sceneOrder[0];
    sceneOrder.erase(sceneOrder.begin());
    setScene(thisSceneID);
}

//--------------------------------------------------------------
void ofApp::randomizeSceneOrder(){
    //first add all of the scenes in order
    sceneOrder.push_back( (int)SCENE_SPORTS);
    sceneOrder.push_back( (int)SCENE_STREAM);
    sceneOrder.push_back( (int)SCENE_TOWER_DEFENSE);
    sceneOrder.push_back( (int)SCENE_BEAM);
    
    //randomize that shit
    for (int i=0; i<sceneOrder.size()*100; i++){
        int a = (int)ofRandom(sceneOrder.size());
        int b = (int)ofRandom(sceneOrder.size());
        int temp = sceneOrder[a];
        sceneOrder[a] = sceneOrder[b];
        sceneOrder[b] = temp;
    }
}

//--------------------------------------------------------------
void ofApp::setScene(int sceneID){
    if (sceneID == curSceneID){
        cout<<"CAN'T CHANGE SCENE TO ITSELF"<<endl;
        return;
    }
    if (sceneID < 0 || sceneID >= NUM_SCENES){
        cout<<"SCENE ID OUT OF RANGE"<<endl;
        return;
    }
    
    if (curSceneID >= 0 && curSceneID <= NUM_SCENES){
        fadingScene = scenes[curSceneID];
        fadingScene->startFade();
    }else{
        fadingScene = NULL;
    }
    
    curSceneID = sceneID;
    
    curScene = scenes[curSceneID];
    curScene->reset();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofShowCursor(); //the mouse was being hidden for some reason
    
    cupTracker->update();
    if (cupTracker->overrideSceneSwicth){
        cupTracker->overrideSceneSwicth = false;
        scrollScenes();
    }
    
    //update the panel
    panel.update();
    
    //check the game scale
    displayScale = panel.getValueF("DISPLAY_SCALE");
    cupTracker->debugDisplayScale = displayScale;
    displayAdjust.x = panel.getValueF("DISPLAY_ADJUST_X");
    displayAdjust.y = panel.getValueF("DISPLAY_ADJUST_Y");
    
    //get info about the seperate screens
    rightScreenOffset.x = panel.getValueF("RIGHT_SCREEN_X_ADJUST");
    rightScreenOffset.y = panel.getValueF("RIGHT_SCREEN_Y_ADJUST");
    rightScreenRotate = panel.getValueF("RIGHT_SCREEN_ROTATION");
    
    leftScreenOffset.x = panel.getValueF("LEFT_SCREEN_X_ADJUST");
    leftScreenOffset.y = panel.getValueF("LEFT_SCREEN_Y_ADJUST");
    leftScreenRotate = panel.getValueF("LEFT_SCREEN_ROTATION");
    
    //pass the info to the cup tracker
    cupTracker->updateFromPanel(&panel);
    
    //main update
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    if (curScene->switchScenesFlag){
        scrollScenes();
    }
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
    ofBackground(curScene->bgCol);
    
    fbo.begin();
    ofClear(255);
    curScene->draw();
    
    if(showField){
        ofSetColor(0,130,130, 200);
        curScene->field.debugDraw();
    }
    
    if (fadingScene != NULL){
        fadingScene->draw();
    }
    
    
    if (showCupDebug){
        cupTracker->draw();
    }
    fbo.end();
    
    ofPushMatrix();
    ofTranslate(displayAdjust.x, displayAdjust.y);
    ofScale(displayScale, displayScale);
    
    ofSetColor(255);
    
    //draw left side
    ofPushMatrix();
    ofTranslate(gameWidth*0.25, gameHeight/2);
    ofRotate(leftScreenRotate);
    //fbo.getTextureReference().drawSubsection(0, 0, gameWidth/2, gameHeight, 0, 0, gameWidth/2, gameHeight);
    fbo.getTextureReference().drawSubsection(-gameWidth/4,-gameHeight/2, gameWidth/2, gameHeight,leftScreenOffset.x, 0+leftScreenOffset.y, gameWidth/2, gameHeight);
    ofPopMatrix();
    
    //draw right side
    ofPushMatrix();
    ofTranslate(gameWidth*0.75, gameHeight/2);
    ofRotate(rightScreenRotate);
    fbo.getTextureReference().drawSubsection(-gameWidth/4,-gameHeight/2, gameWidth/2, gameHeight, gameWidth/2+rightScreenOffset.x, 0+rightScreenOffset.y, gameWidth/2, gameHeight);
    ofPopMatrix();
    
    ofPopMatrix();
    
    
    if(showDebugInfo){
        string modeName = "";
        
        modeName = curScene->sceneName;
        
        ofSetColor(255,0,0);
        string debugInfo =  "fps: "+ofToString(ofGetFrameRate());
        debugInfo +=        "\nscreen: "+ofToString(ofGetWidth())+" x "+ofToString(ofGetHeight());
        debugInfo +=        "\ngame: "+ofToString(gameWidth)+" x "+ofToString(gameHeight);
        debugInfo +=        "\nmode: "+modeName;
        debugInfo +=        "\nf - toggle field";
        debugInfo +=        "\nh - toggle info";
        debugInfo +=        "\np - toggle panel";
        debugInfo +=        "\nleft & right - switch panel";
        debugInfo +=        "\nc - show cup tracker";
        debugInfo +=        "\ns - show cup debug outline";
        debugInfo +=        "\nv - play/pause debug cup vid. Double tap to rewind";
        debugInfo +=        "\nm - scroll mode";
        debugInfo +=        "\n0-9 - add cup";
        debugInfo +=        "\nr - randomize balls";
        debugInfo +=        "\nclick & drag to move";
        debugInfo +=        "\nDEL while draging to remove";
        debugInfo +=        "\nright click & drag to spin";
        ofDrawBitmapString(debugInfo, 10,15);
        //cout<<"draw my child "<<ofGetFrameNum()<<endl;
    }
    
    if (showPanel){
        ofSetColor(255);
        ofSetLineWidth(1);
        ofFill();
        panel.draw();
        ofSetColor(255);
        string panelInfo = ofToString(curPanel+1)+"/"+ofToString(panel.panels.size());
        ofDrawBitmapString(panelInfo, ofGetWidth()-50, ofGetHeight()-5);
        
        //show the mouse because it goes away some times what the hell even
        ofSetColor(200,10,10);
        ofCircle(mouseX, mouseY, 4);
        ofSetColor(ofColor::yellow);
        ofCircle(mouseX, mouseY, 2);
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
        scrollScenes();
    }
    if (key == 'p'){
        showPanel = !showPanel;
        if (!showPanel){
            panel.mouseReleased();
        }
    }
    
    if (key == 's'){
        curScene->showCupDebug = !curScene->showCupDebug;
    }
    
    if (key == '/' || key == '?'){
        setScene(SCENE_CALIBRATION);
    }
   
    
//    if (key == 'f'){
//        ofToggleFullscreen();
//    }
    
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
    
    if (key == ' '){
        panel.setValueB("CAM_TAKE_BG_PIC", true);
    }
    
    cupTracker->keyPressed(key);
    
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
    
    cupTracker->mousePressed(x, y, button);
    curScene->mousePressed(x, y, button);
    
    if (showPanel){
        panel.mousePressed(x,y,button);
    }
    
    //cout<<".set("<<x/displayScale<<","<<y/displayScale<<");"<<endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    cupTracker->mouseDragged(x, y, button);
    curScene->mouseDragged(x, y, button);
    
    if (showPanel){
        panel.mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    cupTracker->mouseReleased(x, y, button);
    curScene->mouseReleased(x, y, button);
    
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








