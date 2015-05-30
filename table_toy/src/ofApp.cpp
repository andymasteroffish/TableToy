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
    
    //testing
    for (int i=0; i<20; i++){
        Ball * newBall = new Ball();
        newBall->setup();
        newBall->pos.set( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        balls.push_back(newBall);
    }
    
    for (int i=0; i<5; i++){
        CupTower * newTower = new CupTower();
        newTower->setup( 200+i*200, ofGetHeight()/2, &field);
        towers.push_back(newTower);
    }
    
    
    showField = false;
    showDebugInfo = true;
    
    deltaTime = 0;
    prevFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofShowCursor(); //the mouse was being hidden for some reason
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    field.clear();
    
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
    
    for (int i=fieldParticles.size()-1; i>=0; i--){
        fieldParticles[i]->draw();
    }
    
    //draw balls
    ofSetColor(233,123,180);
    ofFill();
    for (int i=0; i<balls.size(); i++){
        balls[i]->draw();
        ofDrawBitmapString(ofToString(i), balls[i]->pos.x, balls[i]->pos.y-8);
    }

    if(showDebugInfo){
        ofSetColor(255,0,0);
        string debugInfo =  "fps: "+ofToString(ofGetFrameRate());
        debugInfo +=        "\nf - toggle field";
        debugInfo +=        "\nh - toggle info";
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










