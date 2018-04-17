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
    
    std::vector<float> pen_pressures_;
    
    double perimeter_; // total length of the lines
    
    //total time - calculate speed by doing total time/ getPerimeter()
    uint total_time_millis_;
    
    bool reset_timer_; // flag to reset the timer
    
public:
    Strokes();
    // add point
    void addPoint(const ofPoint& point, float& pressure);
    // end stroke (clear currStroke, add to vector)
    void endStroke();
    // clears all data
    void resetStrokes();
    
    uint getAverageSpeed(); // this is uint because speed will always be positive or 0 and I only need an approximate number to characterize
    
    uint calculateAveragePressure();
    
    void drawStrokes(); //for testing purposes
    int getLength();
};

#endif /* strokes_h */
