//
//  CupTrackerCam.cpp
//  DrinkRink
//
//  Created by Andy Wallace on 8/18/15.
//
//

#include "CupTrackerCam.h"

//--------------------------------------------------------------
void CupTrackerCam::setupCustom(){
    
    imgWidth = 1280 ;
    imgHeight = 480 ;
    
    //working with threshold sections
    useThreshMap = true;    //this should be in panel
    grayImageThresh.allocate(imgWidth, imgHeight);
    for (int i=0; i<24; i++){
        thresholdSections[i] = ofMap(i, 0, 24, 10, 240);
    }
    

#ifdef USE_VIDEO
    ofVideoPlayer * thisGrabber = new ofVideoPlayer();
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->loadMovie("/Users/awallace/Documents/projects/drink_rink/test_vids/ar_split.mp4");
    vidGrabber[0]->play();
    takeBGImageOnStart = false;
    
#elif defined(USE_WEBCAM)
    ofVideoGrabber * thisGrabber = new ofVideoGrabber();
    
    vidGrabber.push_back(thisGrabber);
    vidGrabber[0]->initGrabber(imgWidth/2,imgHeight);
    takeBGImageOnStart = false;
#else
    for (int i = 0; i < deviceList.size(); i++) {
        ofxMacamPs3Eye * camera = new ofxMacamPs3Eye();
        camera->setDeviceID(deviceList[i]->id);
        camera->initGrabber(imgWidth/2, imgHeight);
        vidGrabber.push_back(camera);
    }
    takeBGImageOnStart = true;
#endif
    
    cam0onLeft = true;
    flipHorz = true;
    flipVert = false;
    for (int i=0; i<2; i++){
        camPosAdjust[i].set(0,0);
    }
    
    cupLeftX  = 0;
    cupRightX = gameWidth;
    cupTopY = 0;
    cupBottomY = gameHeight;
    //cupAdjust.set(0,0);
    
    fbo.allocate(imgWidth, imgHeight, GL_RGB);
    pix.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    
    fullImg.allocate(imgWidth, imgHeight);
    colorImg.allocate(imgWidth, imgHeight);
    grayImageNoThresh.allocate(imgWidth, imgHeight);
    grayBGImage.allocate(imgWidth, imgHeight);
    grayImageDemo.allocate(imgWidth, imgHeight);
    
    //start the warp points to include the whole camera(s) image(s)
//    warpPoints[0].set(0, 0);
//    warpPoints[1].set(imgWidth, 0);
//    warpPoints[2].set(imgWidth, imgHeight);
//    warpPoints[3].set(0, imgHeight);
//    
//    //warp end points don't change
//    warpEndPoints[0].set(0,0);
//    warpEndPoints[1].set(colorImg.width,0);
//    warpEndPoints[2].set(colorImg.width, colorImg.height);
//    warpEndPoints[3].set(0,colorImg.height);
    
    
    threshold = 128; //fuck it. why not this value?
    
    //framesBeforeKillingCup = 30;
    
    ARKit.setup(imgWidth, imgHeight);
    ARKit.setThreshold(threshold);
    
    
    timeForDoubleKeyPress = 0.2;
    lastKeyPressTime = -1000;
    
    cupOffset.set(0,0);
    
    takeBGImage = false;
    
    isDebug = false;
    
    overrideSceneSwicth = false;
    
    //setting up threshold cycling
    for (int i=0; i<24; i++){
        zoneHasCup[i] = false;
        
        int thisX = i%12;
        int thisY = i/12;
        threshZoneBorders[i].width = imgWidth/12;
        threshZoneBorders[i].height = imgHeight/2;
        threshZoneBorders[i].x = threshZoneBorders[i].width * thisX;
        threshZoneBorders[i].y = threshZoneBorders[i].height * thisY;
    }
}

//--------------------------------------------------------------
void CupTrackerCam::updateFromPanel(ofxControlPanel * panel){
    bool useAutoThreshold = panel->getValueB("CAM_AUTO_THRESHOLD");
    ARKit.activateAutoThreshold(useAutoThreshold);
    if (!useAutoThreshold){
        threshold = panel->getValueI("CAM_THRESHOLD");
        if (!useThreshMap){
            ARKit.setThreshold(threshold);
        }
    }else{
        threshold = ARKit.getThreshold();
    }
    
    if (panel->getValueB("CAM_TAKE_BG_PIC")){
        takeBGImage = true;
        panel->setValueB("CAM_TAKE_BG_PIC", false);
    }
    //ARKit.setThreshold(threshold);    //WHY WOULD WE SET THIS THRESHOLD AGAIN WHEN WE ARE ALREADY THRESHOLDING OUR IMAGE??? MAKES NO SENSE, EVEN THOUGH THE EXAMPLE PROJECT DOES JUST THIS. I'M COMMENTING THIS OUT AND JUST LETTING IT KEEP THE STARTING THRESHOLD VALUE.
    
    cupOffset.x = panel->getValueF("CAM_X_OFFSET");
    cupOffset.y = panel->getValueF("CAM_Y_OFFSET");
//    for (int i=0; i<4; i++){
//        warpPoints[i].x = panel->getValueF("CAM_WARP_X_"+ofToString(i)) * fullImg.width;
//        warpPoints[i].y = panel->getValueF("CAM_WARP_Y_"+ofToString(i)) * fullImg.height;
//    }
    
    cam0onLeft = panel->getValueB("CAM_0_ON_LEFT");
    flipHorz = panel->getValueB("CAMS_FLIP_HORZ");
    flipVert = panel->getValueB("CAMS_FLIP_VERT");
    camPosAdjust[0].x =panel->getValueF("CAM_0_X");
    camPosAdjust[0].y =panel->getValueF("CAM_0_Y");
    camPosAdjust[1].x =panel->getValueF("CAM_1_X");
    camPosAdjust[1].y =panel->getValueF("CAM_1_Y");
    
    camLeftRotateVal = panel->getValueF("CAM_LEFT_ROT");
    camRightRotateVal = panel->getValueF("CAM_RIGHT_ROT");
    
    framesBeforeKillingCup = panel->getValueI("FRAMES_WITH_NO_CUP");
    
    if (panel->getValueB("CAM_FLIP_ADJUSTS")){
        panel->setValueF("CAM_0_X", camPosAdjust[1].x);
        panel->setValueF("CAM_0_Y", camPosAdjust[1].y);
        panel->setValueF("CAM_1_X", camPosAdjust[0].x);
        panel->setValueF("CAM_1_Y", camPosAdjust[0].y);
        panel->setValueB("CAM_FLIP_ADJUSTS", false);
    }
    
    cupLeftX    = panel->getValueF("CUPS_LEFT_X");
    cupRightX   = panel->getValueF("CUPS_RIGHT_X");
    cupTopY     = panel->getValueF("CUPS_TOP_Y");
    cupBottomY  = panel->getValueF("CUPS_BOTTOM_Y");
    
    cupAdjustLeftX = panel->getValueF("CUPS_ADJUST_X_LEFT");
    cupAdjustRightX = panel->getValueF("CUPS_ADJUST_X_RIGHT");
    
    cupAdjustLeftYtop = panel->getValueF("CUPS_ADJUST_Y_TOP_LEFT");
    cupAdjustLeftYbot = panel->getValueF("CUPS_ADJUST_Y_BOT_LEFT");
    
    cupAdjustRightYtop = panel->getValueF("CUPS_ADJUST_Y_TOP_RIGHT");
    cupAdjustRightYbot = panel->getValueF("CUPS_ADJUST_Y_BOT_RIGHT");
    
    if (!doingThresholdCycling){
        for (int i=0; i<24; i++){
            thresholdSections[i] = panel->getValueI("THRESH_ZONE_"+ofToString(i));
        }
    }else{
        for (int i=0; i<24; i++){
            panel->setValueI("THRESH_ZONE_"+ofToString(i), thresholdSections[i]);
        }
    }
    
    invertGreyImage = panel->getValueB("CAM_INVERT_GREY");
    
    doingThresholdCycling = panel->getValueB("CAM_THRESHOLD_CYCLE");
    thresholdCyclingPaddingDist = panel->getValueF("CAM_THRESHOLD_CYCLE_PADDING");
    
    thresholdCyclingMinVal = panel->getValueI("MIN_THRESHOLD_CYCLE");
    thresholdCyclingMaxVal = panel->getValueI("MAX_THRESHOLD_CYCLE");
    thresholdCyclingSpeed = panel->getValueI("THRESHOLD_CYCLE_SPEED");

    
//    cupAdjustLeftSide.x = panel->getValueF("CUPS_ADJUST_X_LEFT");
//    cupAdjustLeftSide.y = panel->getValueF("CUPS_ADJUST_Y_LEFT");
//    cupAdjustRightSide.x = panel->getValueF("CUPS_ADJUST_X_RIGHT");
//    cupAdjustRightSide.y = panel->getValueF("CUPS_ADJUST_Y_RIGHT");
}

//--------------------------------------------------------------
void CupTrackerCam::update(){
    
    ofSetColor(255);
    
    for (int i = 0; i < vidGrabber.size(); i++) {
        vidGrabber[i]->update();
    }
    
    if (vidGrabber[0]->isFrameNew()){
        
        fbo.begin();
        ofSetColor(0);
        ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
        
        ofVec2f vidPos[2];
        vidPos[0].x = cam0onLeft ? 0 : fbo.getWidth()/2;;
        vidPos[0].y = 0;
        vidPos[1].x = cam0onLeft ? fbo.getWidth()/2 : 0;
        vidPos[1].y = 0;
        
        ofSetColor(255);
        
        for (int i=0; i<MIN(vidGrabber.size(), 2); i++){
            ofPushMatrix();
            ofTranslate(camPosAdjust[i].x, camPosAdjust[i].y);
            ofTranslate(vidPos[i].x + vidGrabber[i]->getWidth()/2, vidPos[i].y + vidGrabber[i]->getHeight()/2);
            ofScale(flipHorz ? -1 : 1, flipVert ? -1 : 1);
            
            if (i== cam0onLeft ? 0 : 1){
                ofRotate(camLeftRotateVal);
            }else{
                ofRotate(camRightRotateVal);
            }
            
            vidGrabber[i]->draw(-vidGrabber[i]->getWidth()/2, -vidGrabber[i]->getHeight()/2);
            ofPopMatrix();
        }
        
        
        fbo.end();
        
        fbo.readToPixels(pix);
        
        fullImg.setFromPixels(pix);
        
        //colorImg.warpIntoMe(fullImg, warpPoints, warpEndPoints);
        colorImg = fullImg;
        grayImageNoThresh = colorImg;
        
        if (takeBGImage || (ofGetFrameNum() == 10 && takeBGImageOnStart)){
            grayBGImage = grayImageNoThresh;
            takeBGImage = false;
        }
        
        grayImageNoThresh.absDiff(grayBGImage);
        
        if (invertGreyImage){
            grayImageNoThresh.invert();
        }
        
        
        if(useThreshMap){
            grayImagePixels = grayImageNoThresh.getPixelsRef();
            
            for(int i=0;i<grayImagePixels.size();i++){
                int pixX = i % imgWidth;
                int pixY = i / imgWidth;
                
                int threshX = pixX / (imgWidth/12);
                int threshY = pixY / (imgHeight/2);
                
                //Thresh offset set here
                if(grayImagePixels[i] <= thresholdSections[threshX + threshY*12]){
                    grayImagePixels[i] = 0;
                }
                else{
                    grayImagePixels[i] = 255;
                }
            }
            
            grayImageThresh.setFromPixels(grayImagePixels);
            grayImageDemo = grayImageThresh;
            
            //if we are flipping the image,w e need to unflip it before passing it to the ARKit
            if (flipHorz || flipVert){
                grayImageThresh.mirror(flipVert, flipHorz);
            }
            
            ARKit.update(grayImageThresh.getPixels());
            
        }
        else{

            grayImageDemo = grayImageNoThresh;
            grayImageDemo.threshold(threshold); //THIS IS REALLY JUST FOR DEMO SO WE CAN SEE IT
            
            //if we are flipping the image,w e need to unflip it before passing it to the ARKit
            if (flipHorz || flipVert){
                grayImageNoThresh.mirror(flipVert, flipHorz);
            }
            ARKit.update(grayImageNoThresh.getPixels());
            
        }
        
        
        //threhsold cyclinging refresh
        if (doingThresholdCycling){
            for (int i=0; i<24; i++){
                zoneHasCup[i] = false;
            }
        }
        
        //update our info
        for (int i=0; i<ARKit.getNumDetectedMarkers(); i++){
            checkARTag(i);
        }
        
        //go through and check for cups that have been removed
        for (int i=activeCups.size()-1; i>=0 ; i--){
            activeCups[i].framesWithoutUpdate++;
            if (activeCups[i].framesWithoutUpdate > framesBeforeKillingCup){
                activeCups.erase( activeCups.begin()+i );
            }
        }
        
    }
    
    if (doingThresholdCycling){
        for (int i=0; i<24; i++){
            if (!zoneHasCup[i]){
                thresholdSections[i] += thresholdCyclingSpeed;
                if (thresholdSections[i] >= thresholdCyclingMaxVal){
                    thresholdSections[i] = thresholdCyclingMinVal;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void CupTrackerCam::draw(){
    
    //WE MOSTLY JUST USE THE CALIBRAITON SCREEN!
    
    ofSetColor(255, 200);
    
    fbo.draw(0,0);
    //fullImg.draw(20,20);
    
    ofVec2f drawStart(100,0);
    
    colorImg.draw(drawStart.x,drawStart.y);
    grayImageDemo.draw(drawStart.x,drawStart.y+5+fullImg.getHeight());
    
    //drawFiducials(drawStart.x, drawStart.y);
    drawARTags(drawStart.x, drawStart.y);
}

//--------------------------------------------------------------
void CupTrackerCam::drawARTags(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (int i=0; i<ARKit.getNumDetectedMarkers(); i++){
        
        ofPoint thisPos = ARKit.getDetectedMarkerCenter(i);
        
        if (flipHorz)   thisPos.x = imgWidth - thisPos.x;
        if (flipVert)   thisPos.y = imgHeight - thisPos.y;
        
        vector<ofPoint> corners;
        ARKit.getDetectedMarkerCorners(i, corners);
        
        int dir = ARKit.getDetectedMarkerDirection(i);
        
        int cornerToUse = 2-dir;
        if (cornerToUse < 0)    cornerToUse+=4;
        ofLine(thisPos.x, thisPos.y, corners[cornerToUse].x, corners[cornerToUse].y);
        
        float angle = atan2(thisPos.y-corners[cornerToUse].y, thisPos.x-corners[cornerToUse].x);
        
        ofPushMatrix();
        
        ofTranslate(thisPos.x, thisPos.y);
        ofRotate(angle*RAD_TO_DEG);
        
        ofNoFill();
        ofSetColor( ofColor::orange );
        float circleSize = 30;
        float lineDist = circleSize + 5;
        ofCircle(0, 0, 30);
        ofLine(-lineDist, 0, lineDist, 0);
        ofLine(0, -lineDist, 0, lineDist);
        
        ofPopMatrix();
        
        ofFill();
        ofSetColor(0,100);
        ofRect(thisPos.x-20, thisPos.y-60, 60, 25);
        ofSetColor( ofColor::yellow );
        ofDrawBitmapString(ofToString(ARKit.getMarkerID(i)), thisPos.x-15, thisPos.y-38);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void CupTrackerCam::keyPressed(int key){
    if( key == '-' ) {
        threshold = MAX( 0, threshold-1 );
    } else if( key == '+' || key == '=' ) {
        threshold = MIN( 255, threshold+1 );
    }
    
    
#ifdef USE_VIDEO
    if (key == 'v'){
        bool isDouble = ofGetElapsedTimef() - lastKeyPressTime < timeForDoubleKeyPress;
        lastKeyPressTime = ofGetElapsedTimef();
        if (isDouble){
            vidGrabber[0]->setFrame(0);
            vidGrabber[0]->play();
        }else{
            if (vidGrabber[0]->isPlaying()){
                vidGrabber[0]->stop();
            }else{
                vidGrabber[0]->play();
            }
        }
    }
#endif
}


//--------------------------------------------------------------
void CupTrackerCam::checkARTag(int idNum){
    
    //get some info about this bad boy
    int tagID = ARKit.getMarkerID(idNum);
    //cout<<"TAG ID "<<tagID<<endl;
    ofPoint tagPos = ARKit.getDetectedMarkerCenter(idNum);
    
    //adjust the image to fit the screen
    float xAdjust = (float)gameWidth / (float)imgWidth;
    float yAdjust = (float)gameHeight / (float)imgHeight;
    
    float gameWorldX = tagPos.x * xAdjust + cupOffset.x;
    float gameWorldY = tagPos.y * yAdjust + cupOffset.y;
    
    if (flipHorz)   gameWorldX = gameWidth-gameWorldX;
    if (flipVert)   gameWorldY = gameHeight-gameWorldY;
    
    //take the gutter on the left and right into account
    gameWorldX = ofMap(gameWorldX, 0, gameWidth, cupLeftX, cupRightX);// + cupAdjust.x;
    gameWorldY = ofMap(gameWorldY, 0, gameHeight, cupTopY, cupBottomY);// + cupAdjust.y;
    
    //once we get the tag, if it is on the left or right side of the screen, we may need addditional adjustments
    float yPrcAwayFromTop = gameWorldY/(gameHeight/2) - 1;
    if (gameWorldX < gameWidth/2){
        float xPrcAwayFromCenter = gameWorldX/(gameWidth/2);
        gameWorldX += cupAdjustLeftX * xPrcAwayFromCenter;
        gameWorldY += (yPrcAwayFromTop < 0 ? cupAdjustLeftYtop : cupAdjustLeftYbot) * yPrcAwayFromTop;
    }else{
        float xPrcAwayFromCenter = 1-(gameWorldX-gameWidth/2)/(gameWidth/2);
        gameWorldX += cupAdjustRightX * xPrcAwayFromCenter;
        gameWorldY += (yPrcAwayFromTop < 0 ? cupAdjustRightYtop : cupAdjustRightYbot) * yPrcAwayFromTop;
    }
    
    //cout<<"putting "<<idNum<<" at "<<gameWorldX<<" , "<<gameWorldY<<endl;
    //cout<<"tag pos "<<tagPos.x<<" , "<<tagPos.y<<endl;
    
    //getting the angle isn't so bad
    ofQuaternion q = ARKit.getOrientationQuaternion(idNum);
    
    float tagAngle = atan2(2*(q.x()*q.y()+q.w()*q.z()),q.w()*q.w()+q.x()*q.x()-q.y()*q.y()-q.z()*q.z());
    
    //angle needs to be flipped if image s flipped
    if (flipHorz){
        tagAngle *= -1;
    }
    
    //if doing threshold cycling, update the map so that this cup's zone(s) is not cycled until this cup leaves
    if (doingThresholdCycling){
        
        if (flipHorz)   tagPos.x = imgWidth-tagPos.x;
        if (flipVert)   tagPos.y = imgHeight-tagPos.y;
        
        for (int i=0; i<24; i++){
            
            if ( tagPos.x + thresholdCyclingPaddingDist > threshZoneBorders[i].x &&
                tagPos.x - thresholdCyclingPaddingDist < threshZoneBorders[i].x+threshZoneBorders[i].width &&
                tagPos.y + thresholdCyclingPaddingDist > threshZoneBorders[i].y &&
                tagPos.y - thresholdCyclingPaddingDist < threshZoneBorders[i].y+threshZoneBorders[i].height){
                
                zoneHasCup[i] = true;
                //cout<<"zone "<<i<<" is true af"<<endl;
            }
            
        }
    }
    
    //does a cup with this ID exist in the list? If so, update the info
    for (int i=0; i<activeCups.size(); i++){
        if (activeCups[i].uniqueID == tagID){
            //if we found it update it
            activeCups[i].pos.set( gameWorldX, gameWorldY );
            activeCups[i].angle = tagAngle;
            //and don't let it die
            activeCups[i].framesWithoutUpdate = 0;
            return;
        }
    }
    
    //if there was nothing, we need to make a new cup
    CupInfo thisCupInfo;
    
    thisCupInfo.uniqueID = tagID;
    thisCupInfo.pos.set( gameWorldX, gameWorldY );
    thisCupInfo.angle = tagAngle;
    thisCupInfo.framesWithoutUpdate = 0;
    thisCupInfo.startTime = ofGetElapsedTimef();
    
    if (tagID == OVERRIDE_CUP_ID){
        overrideSceneSwicth = true;
    }
    
    activeCups.push_back(thisCupInfo);
    
}



