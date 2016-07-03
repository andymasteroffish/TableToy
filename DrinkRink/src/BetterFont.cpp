//
//  BetterFont.cpp
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#include "BetterFont.h"



void BetterFont::loadFont(string filename, int fontSize){
    
    font.loadFont(filename, fontSize);
    
}

void BetterFont::drawString(string s, float x, float y){
    font.drawString(s, x, y);
}

void BetterFont::drawStringCentered(string s, float x, float y){
    ofRectangle box = font.getStringBoundingBox(s, 0, 0);
    font.drawString(s, x-box.width/2, y+box.height/2);
    
}

void BetterFont::drawStringRightAligned(string s, float x, float y){
    float w = font.stringWidth(s);
    font.drawString(s, x-w, y);
}