#include "ofMain.h"
#include "ofApp.h"


//ASPECT RATIO FOR THIS THING IS 1:3


//========================================================================
int main( ){
    
    ofSetupOpenGL(2560,800, OF_WINDOW);			// <-------- setup the GL context
    //ofSetupOpenGL(2720,768, OF_WINDOW);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());
    
}
