//
//  GridPos.h
//  emptyExample
//
//  Created by Andy Wallace on 5/16/15.
//
//

#ifndef emptyExample_GridPos_h
#define emptyExample_GridPos_h


#define DEFAULT_CIRCLE_RES 22

enum ParticleType{ PARTICLE_NO_TYPE, PARTICLE_SPORT, PARTICLE_GOAL_LEFT, PARTICLE_GOAL_RIGHT, PARTICLE_STREAM, NUM_PARTICLE_TYPES };


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


class Bounds{
public:
    GridPos topLeft, bottomRight;
};


#endif
