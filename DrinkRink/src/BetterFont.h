//
//  BetterFont.h
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#ifndef __emptyExample__BetterFont__
#define __emptyExample__BetterFont__

#include "ofMain.h"

class BetterFont{
public:
   
    void loadFont(string filename, int fontSize);
    
    void drawString(string s, float x, float y);
    void drawStringCentered(string s, float x, float y);
    void drawStringRightAligned(string s, float x, float y);
    
    ofTrueTypeFont font;
    
    
    
};

#endif /* defined(__emptyExample__BetterFont__) */
