#ifndef strokes_h
#define strokes_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "ofxTablet.h"

class Strokes {
private:
    // keep track of the strokes to draw
    std::vector<ofPolyline> strokes_;
    ofPolyline currStroke_;
    
    float curr_pressure_;
    std::vector<float> pen_pressures_;
    
public:
    Strokes();
    // add point
    void addPoint(const ofPoint& point, float& pressure);
    // end stroke (clear currStroke, add to vector)
    void endStroke();
    void clearStrokes();
};

#endif /* strokes_h */
