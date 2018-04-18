#ifndef strokes_h
#define strokes_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "ofxTablet.h"

class Strokes {
private:
    // keep track of the strokes to draw
    std::vector<ofPolyline> strokes_; // length ~ connectedness
    ofPolyline curr_stroke_;
    
    std::vector<float> pen_pressures_;
    
    double perimeter_; // total length of the lines
    
    //total time - calculate speed by doing total time/ getPerimeter()
    uint total_time_millis_;
    bool reset_timer_; // flag to reset the timer
    
    // space of margins
    int left_margin_;
    int right_margin_;
    int leftmost_x;
    int rightmost_x;
    
    double letter_size_; // ranges from ~5 for small and ~35 for large
    
    int connectedness_;
    
public:
    Strokes();
    // add point
    void AddPoint(const ofPoint& point, float& pressure);
    // end stroke (clear currStroke, add to vector)
    void EndStroke();
    // clears all data
    void ResetStrokes();
    
    uint GetAverageSpeed(); // this is uint because speed will always be positive or 0 and I only need an approximate number to characterize
    
    uint CalculateAveragePressure();
    
    void Analyze();
    
    void DrawStrokes(); //for testing purposes
    int GetLength();
    
    int GetLetterSize();
    
    int GetLeftMargin();
    int GetRightMargin();
};

#endif /* strokes_h */
