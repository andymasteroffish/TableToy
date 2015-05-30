//
//  GridPos.h
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#ifndef emptyExample_GridPos_h
#define emptyExample_GridPos_h

class GridPos{
public:
    int x, y;
    
    GridPos(){
        set(0,0);
    }
    
    GridPos(GridPos const &orig){
        set(orig.x, orig.y);
    }
    
    GridPos(int _x, int _y){
        set(_x, _y);
    }
    
    void set(int _x, int _y){
        x = _x;
        y = _y;
    }
    
    bool isInBounds(int boundsWidth, int boundsHeight){
        
        return x >= 0 && x < boundsWidth && y >= 0 && y < boundsHeight;
        
    }
};


#endif
