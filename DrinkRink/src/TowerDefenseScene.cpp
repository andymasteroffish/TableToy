//
//  TowerDefenseScene.cpp
//  TabelToy
//
//  Created by Andy Wallace on 8/9/15.
//
//

#include "TowerDefenseScene.h"



//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setupCustom(){
    sceneName = "tower defense";
    
    pauseBetweenWaves = 3;
    pauseBeforeFirstFoeEachWave = 1.5;
    
    curWave = 0;
    curPath = 0;
    
    messageDisplayTime  = pauseBetweenWaves;
    curMessage = "";
    messageTimer = 0;
    
    towerPics[0].loadImage("pic/td/tower_shooter.png");
    towerPics[1].loadImage("pic/td/tower_ice.png");
    towerPics[2].loadImage("pic/td/tower_fire.png");
    
    anims.setup();
    
    fontBig.loadFont("frabk.ttf", 80);
    
    bgPics.resize(3);
    for (int i=0; i<bgPics.size(); i++){
        bgPics[i].loadImage("td_paths/path"+ofToString(i)+".png");
    }
    
    //gameW 2560
    //gameH 800
    
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setupPanelValues(ofxControlPanel * panel){
    panel->addPanel(sceneName, 1, false);
    panel->setWhichPanel(sceneName);
    panel->setWhichColumn(0);
    
    //basic shit
    panel->addToggle("Reset", "TD_RESET", false);
    panel->addToggle("Invincible", "TD_INVINC", false);
    panel->addToggle("Fast forward", "TD_FAST_FORWARD", false);
    panel->addToggle("Show Path", "TD_SHOW_PATH", false);
    panel->addToggle("Skip Wave", "TD_SKIP_WAVE", false);
    
    //towers
    panel->addLabel("");
    panel->addLabel("Shoot Tower");
    panel->addSlider("Shoot Tower Spawn Rate", "SHOOT_TOWER_SPAWN", 6, 0, 15, true);
    panel->addSlider("Shoot Tower Time", "SHOOT_TOWER_TIME", 0.6, 0.1, 7, false);
    panel->addSlider("Shoot Tower Bullet Speed", "SHOOT_TOWER_BULLET_SPEED", 350, 1, 1000, false);
    panel->addSlider("Shoot Tower Damage", "SHOOT_TOWER_DAMAGE", 0.75, 0, 5, false);
    
    panel->addLabel("");
    panel->addLabel("Bomb Tower");
    panel->addSlider("Bomb Tower Spawn Rate", "BOMB_TOWER_SPAWN", 4, 0, 15, true);
    panel->addSlider("Bomb Tower Time", "BOMB_TOWER_TIME", 3, 0.1, 7, false);
    panel->addSlider("Bomb Tower Bullet Speed", "BOMB_TOWER_BULLET_SPEED", 300, 1, 1000, false);
    panel->addSlider("Bomb Tower Bomb Size", "BOMB_TOWER_BOMB_SIZE", 250, 10, 500, false);
    panel->addSlider("Bomb Tower Damage", "BOMB_TOWER_DAMAGE", 3, 0, 5, false);
    
    panel->addLabel("");
    panel->addLabel("Freeze Tower");
    panel->addSlider("Freeze Tower Spawn Rate", "FREEZE_TOWER_SPAWN", 2, 0, 15, true);
    panel->addSlider("Freeze Tower Time", "FREEZE_TOWER_TIME", 5, 0.1, 7, false);
    panel->addSlider("Freeze Tower On Time", "FREEZE_TOWER_ON_TIME", 1.5, 0.1, 3, false);
    panel->addSlider("Freeze Tower Spread", "FREEZE_TOWER_SPREAD", 1, 0, 2, false);
    panel->addSlider("Freeze Time", "FREEZE_TOWER_DURATION", 8, 1, 20, false);
    panel->addSlider("Freeze Speed Reduction", "FREEZE_TOWER_SPEED_REDUCTION", 0.25, 0, 1, false);
    
    
    panel->addPanel(sceneName+"2", 1, false);
    panel->setWhichPanel(sceneName+"2");
    panel->setWhichColumn(0);
    
    //foes
    panel->addSlider("Foe Hit Circle Size", "FOE_HIT_CIRCLE", 40, 5, 100, false);
    
    panel->addLabel("");
    panel->addLabel("Dumb Foe");
    panel->addSlider("Dumb Foe HP", "DUMB_FOE_HP", 3, 0.5, 10, false);
    panel->addSlider("Dumb Foe Speed", "DUMB_FOE_SPEED", 100, 10, 800, false);
    
    panel->addLabel("Strong Foe");
    panel->addSlider("Strong Foe HP", "STRONG_FOE_HP", 5, 0.5, 10, false);
    panel->addSlider("Strong Foe Speed", "STRONG_FOE_SPEED", 50, 10, 800, false);
    panel->addSlider("Num Babies", "STRONG_FOE_BABY_NUM", 2, 1, 5, true);
    
    panel->addLabel("Fast Foe");
    panel->addSlider("Fast Foe HP", "FAST_FOE_HP", 2, 0.5, 10, false);
    panel->addSlider("Fast Foe Speed", "FAST_FOE_SPEED", 175, 10, 800, false);
    
    panel->addLabel("Ignore Foe");
    panel->addSlider("Ignore Foe HP", "IGNORE_FOE_HP", 3, 0.5, 10, false);
    panel->addSlider("Ignore Foe Speed", "IGNORE_FOE_SPEED", 100, 10, 800, false);
    panel->addSlider("Ignore Speed increase", "IGNORE_FOE_SPEED_INCREASE", 1.5, 1, 3, false);
    
    panel->addLabel("Wave Foe - NOT USED");
    panel->addSlider("Wave Foe HP", "WAVE_FOE_HP", 4, 0.5, 10, false);
    panel->addSlider("Wave Foe Speed", "WAVE_FOE_SPEED", 74, 10, 800, false);
    panel->addSlider("Wave Dist", "WAVE_FOE_WAVE_DIST", 100, 10, 200, false);
    panel->addSlider("Wave Period", "WAVE_FOE_WAVE_PERIOD", 2, 0.1, 4, false);
    
    myPanel = panel;
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::checkPanelValuesCustom(ofxControlPanel *panel){
    if (panel->getValueB("TD_RESET")){
        panel->setValueB("TD_RESET", false);
        resetCustom();
    }
    
    if (panel->getValueB("TD_SKIP_WAVE")){
        panel->setValueB("TD_SKIP_WAVE", false);
        foes.clear();
    }
    
    //set the liklihood of each tower
    towerSpawnRates[TD_SHOOTER] = panel->getValueI("SHOOT_TOWER_SPAWN");
    towerSpawnRates[TD_FIRE] = panel->getValueI("BOMB_TOWER_SPAWN");
    towerSpawnRates[TD_ICE] = panel->getValueI("FREEZE_TOWER_SPAWN");
    
    //go through and set fire times
    for (int i=0; i<towers.size(); i++){
        if (towers[i]->towerType == "tower_defense"){
            TowerTD * thisTower = (TowerTD *)towers[i];
            if (thisTower->tdType == TD_SHOOTER){
                thisTower->timeBetweenShots = panel->getValueF("SHOOT_TOWER_TIME");
            }
            if (thisTower->tdType == TD_FIRE){
                thisTower->timeBetweenShots = panel->getValueF("BOMB_TOWER_TIME");
            }
            if (thisTower->tdType == TD_ICE){
                thisTower->timeBetweenShots = panel->getValueF("FREEZE_TOWER_TIME");
            }
        }
    }
    
    //go through and set the freeze rays
    for (int i=0; i<freezeCones.size(); i++){
        freezeCones[i].spreadPrc = panel->getValueF("FREEZE_TOWER_SPREAD");
    }
    
    //go through the foes
    for (int i=0; i<foes.size(); i++){
        foes[i].freezeSpeedReduction = panel->getValueF("FREEZE_TOWER_SPEED_REDUCTION");
    }
    
    debugFastForward = panel->getValueB("TD_FAST_FORWARD");
    debugShowPath = panel->getValueB("TD_SHOW_PATH");
    debugInvincible = panel->getValueB("TD_INVINC");
    
    numStrongBabies = panel->getValueI("STRONG_FOE_BABY_NUM");
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::resetCustom(){
    
    playerHealth = 3;
    
    setWavesFromFile("tower_defense_waves.txt");
    curWave = -1;
    
    //clear out any old foes
    foes.clear();
    
    //clear out bullets
    bullets.clear();
    fireballs.clear();
    freezeCones.clear();
    

    
    //startNextWave();
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::startNextWave(){
    curWave++;
    
    setPath(curWave);
    
    //cout<<"start wave "<<curWave<<endl;
    
    foes.clear();
    
    bool canSwitchPaths = path[1].size() > 0;
    
    for (int i=0; i<waves[curWave].foes.size(); i++){
        TDFoe newFoe;
        FoeType type = waves[curWave].foes[i];
        int thisPath = canSwitchPaths ? i%2 : 0;
        newFoe.setup(type, &anims, &path[thisPath], pauseBeforeFirstFoeEachWave + i*waves[curWave].timeBetweenFoes, myPanel);
        foes.push_back(newFoe);
    }
    
    pauseBetweenWavesTimer = pauseBetweenWaves;
    
    setMessage("BEGIN WAVE "+ofToString(curWave+1), messageDisplayTime);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::updateCustom(){
    
    //if the game just started, the first update is used to spawn waves and not do anything else
    //this is to make sure the game has a reference to the control panel before it creates any foes
    if (curWave == -1){
        startNextWave();
        return;
    }
    
    int numCycles = debugFastForward ? 5 : 1;
    
    for (int cycles=0; cycles<numCycles; cycles++){
    
        //check all towers to see if they are doing thangs (like Big Bear)
        for (int i=0; i<towers.size(); i++){
            if (towers[i]->towerType == "tower_defense"){
                TowerTD * thisTower = (TowerTD *)towers[i];
                if (thisTower->spawnShot){
                    
                    thisTower->spawnShot = false;
                    
                    if (thisTower->tdType == TD_SHOOTER || thisTower->tdType == TD_FIRE){
                        spawnShot(thisTower);
                    }
                    if (thisTower->tdType == TD_ICE){
                        spawnFreezeCone(towers[i]);
                    }
                }
            }
        }
        
        //update the bullets
        for (int i=bullets.size()-1; i>=0; i--){
            bullets[i].update(deltaTime);
            
            //if it out of bounds?
            float padding = bullets[i].size*2;
            if (bullets[i].pos.x < -padding || bullets[i].pos.x > gameWidth+padding || bullets[i].pos.y < -padding || bullets[i].pos.y > gameHeight+padding){
                bullets.erase(bullets.begin()+i);
            }
            
            //check all foes to see if it hit any
            else{
                for (int f=0; f<foes.size(); f++){
                    float minDistSq = powf( (foes[f].hitCircleSize + bullets[i].size), 2);
                    if ( ofDistSquared(foes[f].pos.x, foes[f].pos.y,  bullets[i].pos.x,  bullets[i].pos.y) < minDistSq){
                        foes[f].takeDamage(bullets[i].dmg);
                        if (bullets[i].isFire){
                            spawnFireball(bullets[i].pos);
                        }
                        bullets.erase(bullets.begin()+i);
                    }
                }
            }
        }
        
        //update fireballs
        for (int i=fireballs.size()-1; i>=0; i--){
            fireballs[i].update(deltaTime);
            if (fireballs[i].timer < 0){
                fireballs.erase(fireballs.begin() + i);
            }
        }
        
        //update freeze cones
        for (int i=freezeCones.size()-1; i>=0; i--){
            freezeCones[i].update(deltaTime, &foes);
            if (freezeCones[i].timer < 0){
                freezeCones.erase(freezeCones.begin()+i);
            }
        }
        
        
        //update foes
        for (int i=foes.size()-1; i>=0; i--){
            foes[i].update(deltaTime);
            
            if (foes[i].reachedTheEnd){
                takeDamage();
                foes.erase( foes.begin()+i );
            }
            //check if the foe died
            else if (foes[i].killMe){
                if (foes[i].type == FOE_STRONG){
                    spawnStrongBabies(foes[i]);
                }
                //spawn a dead foe animation
                TDFoeDeath deadGuy;
                deadGuy.steup(&foes[i]);
                deadFoes.push_back(deadGuy);
                //erase it
                foes.erase( foes.begin()+i );
            }
        }
        
        //and the dead ones
        for (int i=deadFoes.size()-1; i>=0; i--){
            deadFoes[i].update(deltaTime);
            if (deadFoes[i].killMe){
                deadFoes.erase(deadFoes.begin()+i);
            }
        }
        
        //home getting hit animation
        for (int i=homeHits.size()-1; i>=0; i--){
            homeHits[i].update(deltaTime);
            if (homeHits[i].killMe){
                homeHits.erase(homeHits.begin()+i);
            }
        }
        
        //if there are no foes and the player is alive, the wave is over
        if (foes.size() == 0 && playerHealth > 0){
            pauseBetweenWavesTimer -= deltaTime;
            setMessage("WAVE COMPLETE", 1); //keep this message on screen until next wave starts
            if (pauseBetweenWavesTimer < 0){
                if (curWave < waves.size()-1){
                    startNextWave();
                }else{
                    setMessage("YOU WIN!", 1);
                }
            }
        }
        
        //is the player dead?
        if (playerHealth <= 0){
            setMessage("YOU DEAD!!!", 1);
        }
        
        //check the message
        messageTimer -= deltaTime;
    }
    
    //cout<<"num foes: "<<foes.size()<<endl;
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::drawBackgroundCustom(){
    ofSetColor(255, 255*alphaPrc);
    bgPics[curPath].draw(0, 0);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::drawCustom(){
    
    
    //draw the home
    ofFill();
    float homeSize = 60;
    ofSetColor(ofColor::purple);
    ofVec2f homePos = path[0][path[0].size()-1];
    ofCircle(homePos.x, homePos.y, homeSize);
    
    //show damage effects
    for (int i=0; i<homeHits.size(); i++){
        homeHits[i].draw(alphaPrc);
    }
    
    //show the player health around if
    float angleSpacing = TWO_PI/playerHealth;
    float heartSize = 20;
    float heartDist = heartSize + homeSize + 15;
    for (int i=0; i<playerHealth; i++){
        ofFill();
        ofSetColor(ofColor::pink);
        float thisAngle = angleSpacing*i + ofGetElapsedTimef()*0.5;
        float xPos = homePos.x + cos(thisAngle) * heartDist;
        float yPos = homePos.y + sin(thisAngle) * heartDist;
        ofCircle(xPos, yPos, heartSize);
    }
    
    
    //debug draw the path
    if (debugShowPath){
        ofSetColor(20);
        for (int k=0; k<2; k++){
            for (int i=0; i<path[k].size(); i++){
                if (i>0){
                    ofLine(path[k][i], path[k][i-1]);
                }
                ofCircle(path[k][i].x, path[k][i].y, 10);
            }
        }
    }
    
    
    //draw the dead foes
    for (int i=0; i<deadFoes.size(); i++){
        deadFoes[i].draw(alphaPrc);
    }
    
    //draw the foes
    for (int i=0; i<foes.size(); i++){
        foes[i].draw(alphaPrc);
    }
    
    //draw freeze cones
    for (int i=0; i<freezeCones.size(); i++){
        freezeCones[i].draw(alphaPrc);
    }
    
    //draw the bullets
    for (int i=0; i<bullets.size(); i++){
        bullets[i].draw(alphaPrc);
    }
    
    //draw fireballs
    for (int i=0; i<fireballs.size(); i++){
        fireballs[i].draw(alphaPrc);
    }
    
    //is the player dead?
    if (playerHealth <= 0){
        ofSetColor(255,0,0);
        
        for (int i=0; i<30; i++){
            ofDrawBitmapString("YOU DEAD", gameWidth * ofNoise(ofGetElapsedTimef()*0.2, i), gameHeight * ofNoise(ofGetElapsedTimef()*0.1, i, 10));
        }
    }
    
    //do we have a message to draw?
    if (messageTimer > 0){
        ofSetColor( ofColor::darkBlue );
        fontBig.drawStringCentered(curMessage, gameWidth/2, gameHeight/2);
    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::keyPressed(int key){
    //takeDamage();
}


//--------------------------------------------------------------------------------------------
void TowerDefenseScene::addTower(CupInfo thisCup){
    
    int totalTickets = 0;
    for (int i=0; i<TD_NUM_TOWERS; i++){
        totalTickets += towerSpawnRates[i];
    }
    int thisTcket = thisCup.uniqueID % totalTickets;

    
    for (int i=0; i<TD_NUM_TOWERS; i++){
        thisTcket -= towerSpawnRates[i];
        if (thisTcket < 0){
            TowerTD * newTower = new TowerTD();
            newTower->setup( thisCup, &field);
            newTower->setupTowerDefense((TD_TOWER_TYPE)i, &towerPics[i]);
            towers.push_back(newTower);
            return;
        }
    }
    
    cout<<"What the fuck?"<<endl;
    
    
//    TowerTD * newTower = new TowerTD();
//    newTower->setup( thisCup, &field);
//    if (thisCup.uniqueID % 3 == 0){
//        newTower->setupTowerDefense(TD_SHOOTER, &towerPics[TD_SHOOTER]);
//    }
//    if (thisCup.uniqueID % 3 == 1){
//        newTower->setupTowerDefense(TD_ICE, &towerPics[TD_ICE]);
//    }
//    if (thisCup.uniqueID % 3 == 2){
//        newTower->setupTowerDefense(TD_FIRE, &towerPics[TD_FIRE]);
//    }
    
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::removingTowerCustom(Tower * towerBeingRemoved){
    //check if any freeze cones are using this tower
    if (towerBeingRemoved->towerType == "tower_defense"){
        for (int i=0; i<freezeCones.size(); i++){
            if (freezeCones[i].parentTower == towerBeingRemoved){
                freezeCones.erase(freezeCones.begin() + i);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::takeDamage(){
    
    TDHomeHit newHit;
    newHit.setup(path[0][path[0].size()-1]);
    homeHits.push_back(newHit);
    
    if (debugInvincible){
        return;
    }
    playerHealth--;
    
    setMessage("Ouch! Health Left: "+ofToString(playerHealth), messageDisplayTime/2);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::spawnShot(TowerTD * source){
    TDBullet newBullet;
    newBullet.setup(source->pos, source->curAngle, source->towerSize, source->tdType == TD_FIRE, myPanel);
    bullets.push_back(newBullet);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::spawnFreezeCone(Tower * source){
    TDFreezeCone newCone;
    newCone.setup(source, myPanel);
    freezeCones.push_back(newCone);
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::spawnFireball(ofVec2f pos){
    //create a fireball
    TDFireball fireball;
    fireball.setup(pos, myPanel);
    fireballs.push_back(fireball);
    
    //damage all foes in the radius
    //right now, the center of the foe must be in the blast
    for (int i=0; i<foes.size(); i++){
        float distSq = ofDistSquared(foes[i].pos.x, foes[i].pos.y, pos.x, pos.y);
        if (distSq < fireball.startSize*fireball.startSize){
            foes[i].takeDamage(fireball.dmg);
        }
    }
}

//--------------------------------------------------------------------------------------------
//the strong foe spawns two normal foes when it dies
void TowerDefenseScene::spawnStrongBabies(TDFoe parent){
    float angle = ofRandom(TWO_PI);
    float dist = 50;
    for (int i=0; i<numStrongBabies; i++){
        
        ofVec2f newPos;
        newPos.x = parent.pos.x + cos(angle) * dist;
        newPos.y = parent.pos.y + sin(angle) * dist;
        angle +=  TWO_PI/numStrongBabies;
        
        TDFoe newFoe;
        newFoe.setup(FOE_DUMB, &anims, parent.path, 0, myPanel);
        newFoe.setPos(newPos, parent.nextNodeID);
        foes.push_back(newFoe);
    }
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setMessage(string newMessage, float displayTime){
    messageTimer = displayTime;
    curMessage = newMessage;
}

//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setWavesFromFile(string fileName){
    ofFile file(fileName);
    ofBuffer buffer(file);
    
    TDWaveInfo thisWave;
    bool nextLineIsTimeInfo = false;
    
    while(!buffer.isLastLine()){
        string line = buffer.getNextLine();
        if (line.size() > 0){
            //semicolon means comment
            if (line[0] != ';'){
                
                //"WAVE" means a new wave
                if (line.find("WAVE") == 0){
                    //if there is existing info, add it to the vector
                    if(thisWave.foes.size() > 0){
                        waves.push_back(thisWave);
                    }
                    //clear it out
                    thisWave.foes.clear();
                    thisWave.timeBetweenFoes = 0;
                    
                    //mark that the next line should be parsed for time
                    nextLineIsTimeInfo = true;;
                }
                
                else if (nextLineIsTimeInfo){
                    int millis = std::atoi(line.c_str());
                    thisWave.timeBetweenFoes = (float)millis/1000.0;
                    nextLineIsTimeInfo = false;
                }
                
                //anything else should just be a list of chars for enemies to spawn
                else{
                    for (int i=0; i<line.size(); i++){
                        if (line[i] == 'D')     thisWave.foes.push_back((FOE_DUMB));
                        if (line[i] == 'S')     thisWave.foes.push_back((FOE_STRONG));
                        if (line[i] == 'F')     thisWave.foes.push_back((FOE_FAST));
                        if (line[i] == 'W')     thisWave.foes.push_back((FOE_WAVE));    //WAVE IS DEFUNCT!
                        if (line[i] == 'I')     thisWave.foes.push_back((FOE_IGNORE));
                    }
                }
                
            }
        }
    }
    
    //add the last wave
    if(thisWave.foes.size() > 0){
        waves.push_back(thisWave);
    }
    
//    for(int i=0; i<waves.size(); i++){
//        cout<<"wave "<<i<<"   time: "<<waves[i].timeBetweenFoes<<"  foes: "<<waves[i].foes.size()<<endl;
//    }
    
    
}



//--------------------------------------------------------------------------------------------
void TowerDefenseScene::setPath(int curWave){
    
    curPath ++;
    if (curPath >= bgPics.size()){
        curPath = 0;
    }
    
    path[0].clear();
    path[1].clear();
    
    ofBuffer buffer = ofBufferFromFile("td_paths/path"+ofToString(curPath)+".txt");
    
    int curPath = 0;
    
    if (buffer.size()){
        while(!buffer.isLastLine()){
            string line = buffer.getNextLine();
            string xString = "";
            string yString = "";
            bool hitComma = false;
            if (line == "------"){
                curPath++;
            }
            else if (line.length() >= 3){
                for (int i=0; i<line.length(); i++){
                    if (line[i] == ','){
                        hitComma = true;
                    }
                    else if (hitComma == false){
                        xString += line[i];
                    }else{
                        yString += line[i];
                    }
                }
                
                ofVec2f newPos;
                newPos.x = std::atof(xString.c_str());
                newPos.y = std::atof(yString.c_str());
                path[curPath].push_back(newPos);
            }
        }
        
    }else{
        cout<<"you done fucked up that file, brah"<<endl;
    }
//    
//    if (curWave%2 == 0){
//        path.resize(8);
//        path[0].set(100,200);
//        path[1].set(500,200);
//        path[2].set(500,600);
//        path[3].set(1110,600);
//        path[4].set(1110,250);
//        path[5].set(1800,250);
//        path[6].set(1800,400);
//        path[7].set(2200,400);
//    }
//    
//    else{
//        path.resize(10);
//        path[0].set(92,428);
//        path[1].set(496,98);
//        path[2].set(848,100);
//        path[3].set(844,408);
//        path[4].set(516,444);
//        path[5].set(508,688);
//        path[6].set(1320,684);
//        path[7].set(1626,102);
//        path[8].set(1930,646);
//        path[9].set(2344,398);
//    }
}
