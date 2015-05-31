//
//  CupRepeller.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/30/15.
//
//

#include "CupRepeller.h"

void CupRepeller::customSetup(){
    range = 100;
    debugColor.set(0, 230, 80, 220);
}

void CupRepeller::customUpdate(){
    float testStrength = 4;
    //cout<<"testo "<<field->externalWidth<<endl;
    field->addOutwardCircle(pos.x, pos.y, range, testStrength);
}

