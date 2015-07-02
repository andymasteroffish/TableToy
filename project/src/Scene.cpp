//
//  Sceen.cpp
//  emptyExample
//
//  Created by Andy Wallace on 6/27/15.
//
//

#include "Scene.h"

void Scene::setup(){
    setupCustom();
}
void Scene::reset(){
    resetCustom();
}
void Scene::update(float _deltaTime){
    deltaTime = _deltaTime;
    updateCustom();
}
void Scene::draw(){
    drawCustom();
}

