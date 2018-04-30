#ifndef strokes_h
#define strokes_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "ofxTablet.h"
#include "factors.h"

namespace handwritinganalysis {

class Strokes {
private:
    // keep track of the strokes
    std::vector<ofPolyline> strokes_; // length ~ connectedness
    ofPolyline curr_stroke_;
    ofPolyline prev_stroke_;
    
    // helper variables
    std::vector<float> pen_pressures_;
    double perimeter_;      // total length of the lines
    uint total_time_millis_;// keep track of total time in milliseconds
    bool reset_timer_;      // flag to reset the timer every stroke
    uint connected_points_; // count number of connected points
    uint leftmost_x_;       // keep track of margins
    uint rightmost_x_;
    
    // Helper methods to calculate data
    
    // Method to calculate the average pressure from stored values
    // Returns an unsigned integer ranging from 1 (light) to 100 (heavy)
    uint CalculateAveragePressure();
    
    // Calculates average letter size from y values of each stroke
    // Returns an unsigned int ranging from ~15 (small) to ~45 (large)
    uint CalculateAverageLetterSize();
    
    // Calculates average speed from total time and perimeter
    // Returns an unsigned int ranging from around ~15 (slow) and ~45 (fast)
    uint CalculateAverageSpeed();
    
public:
    Strokes();
        
    // This method is called when the user is drawing and a point needs to be added to the line.
    // Private variables are updated to keep track of the timer, margins, and connectedness value.
    // Input: ofPoint the point to add, float the pressure of the pen at that point
    void AddPoint(const ofPoint& point, const float& pressure);
    
    // This method is called when the user lifts the pen after each stroke. Member variables are updated accordingly.
    void EndStroke();
    
    // This method resets all variables and is called when the user wants to start over
    void ResetStrokes();
    
    // Sets variables that store analysis data to be called when user is done writing
    void Analyze(HandwritingFactors& factors);
    
    // Returns size of strokes_
    uint GetNumStrokes();

    // Draws strokes used for testing purposes
    void DrawStrokes();
};
} // namespace handwritinganalysis

#endif /* strokes_h */
