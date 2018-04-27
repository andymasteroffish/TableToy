//
//  StreamBlobScene.cpp
//  DrinkRink
//
//  Created by Andrew Wallace on 4/23/18.
//
//

#include "StreamBlobScene.hpp"



//--------------------------------------------------------------------------------------------
void StreamBlobScene::setupCustom(){
    sceneName = "stream_blob";
    
    defaultParticleType =  PARTICLE_STREAM;
    bgCol.set(ofRandom(10),ofRandom(10),ofRandom(10));
    
    numFieldParticlesPerFrame = 25;
    
    //give us some bg shapes
    for (int i=0; i<25; i++){
        StreamBackgroundShape bgShape;
        bgShape.setup(gameWidth, gameHeight);
        bgShapes.push_back(bgShape);
    }
    
    drawDebugBobs = false;
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    panel->addSlider("blob force", "STREAM_BLOB_FORCE", 0.4, 0, 2, false);
    panel->addToggle("show contours", "STREAM_SHOW_BLOBS", false);
    
    panel->addSlider("blob Hue", "STREAM_BLOB_HUE", 250, 0, 255, true);
    panel->addSlider("blob Saturation", "STREAM_BLOB_SAT", 196, 0, 255, true);
    panel->addSlider("blob Brightness", "STREAM_BLOB_BRI", 107, 0, 255, true);
    panel->addSlider("blob Base Alpha", "STREAM_BLOB_ALPHA", 75, 0, 255, true);
    
    panel->addSlider("alpha pulse range", "STREAM_BLOB_ALPHA_RANGE", 40, 0, 255, false);
    panel->addSlider("alpha pulse speed", "STREAM_BLOB_ALPHA_SPEED", 0.3, 0.0001, 1.5, false);
    
    panel->addToggle("use noise", "STREAM_BLOB_USE_NOISE", true);
    panel->addSlider("noise speed", "STREAM_BLOB_NOISE_SPEED", 1, 0, 3, false);
    panel->addSlider("noise range", "STREAM_BLOB_NOISE_RANGE", 20, 0, 100, false);
    
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::resetCustom(){
    cupTracker->useCups = false;
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::checkPanelValuesCustom(ofxControlPanel * panel){
    blobForce = panel->getValueF("STREAM_BLOB_FORCE");
    drawDebugBobs = panel->getValueB("STREAM_SHOW_BLOBS");
    
    blobCol.setHsb(panel->getValueI("STREAM_BLOB_HUE"), panel->getValueI("STREAM_BLOB_SAT"), panel->getValueI("STREAM_BLOB_BRI"));
    blobCol.a = panel->getValueI("STREAM_BLOB_ALPHA");
    
    alphaPulseRange = panel->getValueF("STREAM_BLOB_ALPHA_RANGE");
    alphaPulseSpeed = panel->getValueF("STREAM_BLOB_ALPHA_SPEED");
    
    useNoiseForBlobs = panel->getValueB("STREAM_BLOB_USE_NOISE");
    blobNoiseSpeed = panel->getValueF("STREAM_BLOB_NOISE_SPEED");
    blobNoiseRange = panel->getValueF("STREAM_BLOB_NOISE_RANGE");
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::updateCustom(){
    setStreamForceOnField();
    
    for (int i=0; i<cupTracker->blobs.size(); i++){
        
        for (int k=0; k<cupTracker->blobs[i].points.size(); k++){
            ofVec2f pnt;
            pnt.x =  cupTracker->blobs[i].points[k].x;
            pnt.y =  cupTracker->blobs[i].points[k].y;
            
            //for each of these points, calculate the field position
            float xPrc = pnt.x / (float)gameWidth;
            float yPrc = pnt.y / (float)gameHeight;
            
            //get the X and Y of the field
            int fieldX = field.fieldWidth * xPrc;
            int fieldY = field.fieldHeight * yPrc;
            
            //cout<<"field size "<<field.fieldWidth<<","<<field.fieldHeight<<endl;
            //cout<<"field pos "<<fieldX<<","<<fieldY<<endl;
            
            ofVec2f normalized = pnt - cupTracker->blobs[i].center;
            normalized.normalize();
            
            //ofVec2f force(0,1);
            field.field[fieldX][fieldY].vel += normalized * blobForce;;
        }

    }
    
    
    //background
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].update(deltaTime);
    }
    
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::setStreamForceOnField(){
    float minX = 0.1;
    float maxX = 3;
    
    float yRange = 1;
    
    float noiseScale = 0.5;
    float noiseSpeed = 0.2;
    
    for (int x=0; x<FIELD_WIDTH; x++){
        for (int y=0; y<FIELD_HEIGHT; y++){
            ofVec2f thisForce;
            
            float xPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed );
            thisForce.x =  xPrc * maxX + (1-xPrc) * minX;
            
            float yPrc = ofNoise( x*noiseScale, y*noiseScale, ofGetElapsedTimef() * noiseSpeed, 1000 );
            thisForce.y = yPrc * yRange + (1-yPrc) * (-yRange);
            
            field.field[x][y].vel += thisForce;
        }
    }
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::drawBackgroundCustom(){
    for (int i=0; i<bgShapes.size(); i++){
        bgShapes[i].draw(alphaPrc);
    }
    ofSetCircleResolution(22);  //return it to default
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::drawCustom(){
    
    if (drawDebugBobs){
        for (int i=0; i<cupTracker->blobs.size(); i++){

            cupTracker->blobs[i].draw();
        }
    }
    
    
    //styalized blobs
    float alpha = blobCol.a + sin(ofGetElapsedTimef() * alphaPulseSpeed) * alphaPulseRange;
    alpha = CLAMP(alpha, 0, 255);
    ofSetColor(blobCol, alpha * alphaPrc);
    
    
    for (int i=0; i<cupTracker->blobs.size(); i++){
        
        ofFill();
        ofBeginShape();
        for (int p=0; p<cupTracker->blobs[i].points.size(); p++){
            float thisX = cupTracker->blobs[i].points[p].x;
            float thisY = cupTracker->blobs[i].points[p].y;
            
            
            float xNoise = 0;
            float yNoise = 0;
            if (useNoiseForBlobs){
                xNoise = ofSignedNoise(thisX, thisY, ofGetElapsedTimef()*blobNoiseSpeed, 100) * blobNoiseRange;
                yNoise =ofSignedNoise(thisX, thisY, ofGetElapsedTimef()*blobNoiseSpeed) * blobNoiseRange;
            }
            ofVertex(thisX + xNoise, thisY + yNoise);
        }
        ofEndShape();
        
        
    }
    
    
}

//--------------------------------------------------------------------------------------------
void StreamBlobScene::keyPressed(int key){
    
}
