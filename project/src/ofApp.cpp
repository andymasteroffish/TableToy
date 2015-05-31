#include "ofApp.h"



// comparison routine for sorting
bool ballSort(  Ball * a, Ball * b ) {
    return a->pos.x < b->pos.x;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofBackground(10);
    
    field.setupField(ofGetWidth(),ofGetHeight());
    
    ballRepulsionRange = 20;
    ballRepulsionMaxForce = 1;
    
    startStreamMode();
    
    showField = false;
    showDebugInfo = true;
    showFieldParticles = true;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
//clears everythign and gets the toy ready for a new mode
void ofApp::reset(){
    
    //kill all towers if there are any
    for (int i=0; i<towers.size(); i++){
        delete towers[i];
    }
    towers.clear();
    
    //kill all balls if there are any
    for (int i=0; i<balls.size(); i++){
        delete balls[i];
    }
    balls.clear();
    
}

//--------------------------------------------------------------
void ofApp:: startBallMode(){
    curMode = MODE_BALL;
    
    for (int i=0; i<20; i++){
        Ball * newBall = new Ball();
        newBall->setup();
        newBall->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        balls.push_back(newBall);
    }
    
    for (int i=0; i<5; i++){
        addCup();
    }
    
}

//--------------------------------------------------------------
void ofApp:: startStreamMode(){
    curMode = MODE_STREAM;
    
    for (int i=0; i<5; i++){
        addCup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofShowCursor(); //the mouse was being hidden for some reason
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    field.clear();
    
    if (curMode == MODE_STREAM){
        field.setStreamForce();
    }
    
    //sort the balls from left to right
    sort(balls.begin(), balls.end(), ballSort );
    
    //have the towers do their thing on the field
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->update();
    }
    
    //actually update the balls
    for (int i=balls.size()-1; i>=0; i--){
        //cout<<"ball "<<i<<" vel "<<balls[i].vel.x<<" , "<<balls[i].vel.y<<endl;
        
        //for each ball, get the repulsion form any nearby balls
        for (int j= i-1; j >= 0; j--){
            //stop chekcing if we're out of range
            if ( fabs(balls[j]->pos.x - balls[i]->pos.x) > ballRepulsionRange){
                break;
            }
            balls[i]->addRepulsionForce(balls[j], ballRepulsionRange, ballRepulsionMaxForce);
        }
        
        balls[i]->update(&field);
        
    }
    
    //update the field particles
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->update(deltaTime, &field);
        if (fieldParticles[i]->killFlag){
            delete fieldParticles[i];
            fieldParticles.erase( fieldParticles.begin() + i);
        }
    }
    
    
    //testing the particles
    makeFieldParticles();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(showField){
        ofSetColor(0,130,130, 200);
        field.debugDraw();
    }
    
    for (int i=towers.size()-1; i>=0; i--){
        towers[i]->draw();
    }
    
    //testing
    ofSetColor(198,123,233);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        ofCircle(balls[i]->pos, ballRepulsionRange/2);
        balls[i]->draw();
    }
    
    if (showFieldParticles){
        for (int i=fieldParticles.size()-1; i>=0; i--){
            fieldParticles[i]->draw();
        }
    }
    
    //draw balls
    ofSetColor(233,123,180);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        balls[i]->draw();
        ofDrawBitmapString(ofToString(i), balls[i]->pos.x, balls[i]->pos.y-8);
    }

    if(showDebugInfo){
        string modeName = "";
        if (curMode == MODE_BALL)   modeName = "ball";
        if (curMode == MODE_STREAM)   modeName = "stream";
        
        ofSetColor(255,0,0);
        string debugInfo =  "fps: "+ofToString(ofGetFrameRate());
        debugInfo +=        "\nmode: "+modeName;
        debugInfo +=        "\nf - toggle field";
        debugInfo +=        "\np - toggle particles";
        debugInfo +=        "\nh - toggle info";
        debugInfo +=        "\nm - toggle mode";
        debugInfo +=        "\na - add cup";
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
    
    if (key == 'a'){
        addCup();
    }
    
    if (key == 'm'){
        reset();
        
        curMode = (ModeType) ((curMode+1)%NUM_MODES);
        
        if (curMode == MODE_BALL)   startBallMode();
        if (curMode == MODE_STREAM) startStreamMode();
    }

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
    
    for (int i=0; i<towers.size(); i++){
        towers[i]->onMouseDrag(x, y, button);
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i=0; i<towers.size(); i++){
        towers[i]->onMouseDown(x, y, button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i=0; i<towers.size(); i++){
        towers[i]->onMouseRelease(x, y, button);
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
void ofApp::makeFieldParticles(){
    vector<ofVec2f> gridPosAffectedThisFrame;
    float minStrengthToCount = 0.01;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            if ( abs(field.field[x][y].x) > minStrengthToCount || abs(field.field[x][y].y > minStrengthToCount) ){
                gridPosAffectedThisFrame.push_back( field.getExternalPointFromInternal(x,y) );
            }
        }
    }
    
    
    for (int i=0; i<10; i++){
        ofVec2f thisPos = gridPosAffectedThisFrame[ ofRandom( (int)gridPosAffectedThisFrame.size() )];
        FieldParticle * newP = new FieldParticle( thisPos.x, thisPos.y );
        fieldParticles.push_back(newP);
    }
}

//--------------------------------------------------------------
void ofApp::addCup(){
    
    float startX = ofRandom(100, ofGetWidth()-100);
    float startY = ofRandom(100, ofGetHeight()-100);
    
    if (curMode == MODE_BALL){
        int rand = (int)ofRandom(2);
        
        if (rand == 0){
            CupRepeller * newTower = new CupRepeller();
            newTower->setup( startX, startY, &field);
            towers.push_back(newTower);
        }
        if (rand == 1) {
            CupFlow * newTower = new CupFlow();
            newTower->setup( startX, startY, &field);
            towers.push_back(newTower);
        }
    }
    
    if (curMode == MODE_STREAM){
        CupRock * newTower = new CupRock();
        newTower->setup( startX, startY, &field);
        towers.push_back(newTower);
    }
    
}










