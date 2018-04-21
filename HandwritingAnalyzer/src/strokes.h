#ifndef strokes_h
#define strokes_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "ofxTablet.h"

class Strokes {
private:
    // keep track of the strokes
    std::vector<ofPolyline> strokes_; // length ~ connectedness
    ofPolyline curr_stroke_;
    ofPolyline prev_stroke_;
    
    // variables to store data for analysis
    uint avg_pressure_;
    uint speed_;
    int left_margin_;
    int right_margin_;
    uint letter_size_; // ranges from ~15 for small and ~45 for large
    int connectedness_; // stores number of disconnected strokes, should range from number of words to number of letters
    
    // helper variables
    std::vector<float> pen_pressures_;
    
    // total length of the lines
    double perimeter_;
    
    //total time - calculate speed by doing total time/ getPerimeter()
    uint total_time_millis_;
    // flag to reset the timer
    bool reset_timer_;
    
    // space of margins
    int leftmost_x_;
    int rightmost_x_;
    
    // there are 2 ways for handwriting to be connected
    // 1. writing in cursive or with few lifts
    // 2. writing so close together that the letters intersect
    int connected_points_;
    
    // helper methods to calculate data
    uint CalculateAverageSpeed(); // this is uint because speed will always be positive or 0 and I only need an approximate number to characterize
    uint CalculateAveragePressure();
    uint CalculateAverageLetterSize();
    
public:
    Strokes();
    // add point
    void AddPoint(const ofPoint& point, float& pressure);
    // end stroke (clear currStroke, add to vector)
    void EndStroke();
    // clears all data
    void ResetStrokes();
    
    void Analyze();
    
    void DrawStrokes(); //for testing purposes
    int GetLength();
    
    int GetLetterSize();
    
    int GetLeftMargin();
    int GetRightMargin();
    
    int GetConnectedness();
    
    uint GetSpeed();
    uint GetPressure();
};

#endif /* strokes_h */
