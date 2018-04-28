#include "strokes.h"
using namespace handwritinganalysis;

// Constructor that initializes member variables
Strokes::Strokes() : perimeter_(0), total_time_millis_(0), reset_timer_(true), connected_points_(0),  leftmost_x_(ofGetWindowWidth()), rightmost_x_(0) {}

// This method is called when the user is drawing and a point needs to be added to the line.
// Private variables are updated to keep track of the timer, margins, and connectedness value.
// Input: ofPoint the point to add, float the pressure of the pen at that point
void Strokes::AddPoint(const ofPoint& point, const float& pressure) {
    curr_stroke_.lineTo(point);
    pen_pressures_.push_back(pressure);
    
    // reset timer at beginning of stroke
    if (reset_timer_) {
        ofResetElapsedTimeCounter();
        reset_timer_ = false;
    }
    
    // find leftmost and rightmost x coordinate for margins
    if (point.x < leftmost_x_) {
        leftmost_x_ = point.x;
    }
    if (point.x > rightmost_x_) {
        rightmost_x_ = point.x;
    }
    
    // check for connectedness
    if (prev_stroke_.size() > 0 && prev_stroke_.inside(point)) {
        connected_points_++;
        //std::cout << "bam" << std::endl;
    }
}

// This method is called when the user lifts the pen after each stroke. Member variables are updated accordingly.
void Strokes::EndStroke() {
    perimeter_ += curr_stroke_.getPerimeter();  // add to total length
    strokes_.push_back(curr_stroke_);           // store all previous strokes
    prev_stroke_ = curr_stroke_;                // save previous stroke
    curr_stroke_.clear();                       // clear current stroke for next stroke
    
    // update time variables
    total_time_millis_ += ofGetElapsedTimeMillis();
    reset_timer_ = true;
}

// This method resets all variables and is called when the user wants to start over
void Strokes::ResetStrokes() {
    strokes_.clear();
    curr_stroke_.clear();
    prev_stroke_.clear();
    
    pen_pressures_.clear();
    perimeter_ = 0;
    total_time_millis_ = 0;
    reset_timer_ = true;
    connected_points_ = 0;
    leftmost_x_ = ofGetWindowWidth();
    rightmost_x_ = 0;
}

// Method to calculate the average pressure from stored values
// Returns an unsigned integer ranging from 1 (light) to 100 (heavy)
uint Strokes::CalculateAveragePressure() {
    if (pen_pressures_.size() == 0) {
        return 0;
    }
    
    uint total_pressure = 0;
    for (float pressure : pen_pressures_) {
        total_pressure += pressure;
    }
    return total_pressure/pen_pressures_.size();
}

// Calculates average letter size from y values of each stroke
// Returns an unsigned int ranging from ~15 (small) to ~45 (large)
uint Strokes::CalculateAverageLetterSize() {
    double average = 0;
    
    // find average max y-coord and min y-coord
    for (auto stroke : strokes_) {
        double upper_y = 0;
        double lower_y = 0;
        
        // find upper and lower bounds
        double center_x = stroke.getPointAtPercent(0.5).x; //getCentroid2D().x;
        lower_y = stroke.getClosestPoint(ofPoint(center_x, 0)).y;
        upper_y = stroke.getClosestPoint(ofPoint(center_x, ofGetWindowHeight())).y;
        
        int difference = upper_y - lower_y;
        if (difference < 10) { // ignore small cases i.e. a really long horizontal line or dots
            continue;
        }
        if (average == 0) {
            average += difference;
        } else {
            average = (average + difference) / 2;
        }
    }
    
    return uint(average);
}

// Calculates average speed from total time and perimeter
// Returns an unsigned int ranging from around ~15 (slow) and ~45 (fast)
uint Strokes::CalculateAverageSpeed() {
    if (total_time_millis_ <= 0 || perimeter_ <= 0) {
        return 0;
    }
    
    double speed = perimeter_/total_time_millis_;
    return uint(speed * 100);
}

// Sets variables that store analysis data to be called when user is done writing
void Strokes::Analyze(HandwritingFactors& factors) {
    if (connected_points_ >= strokes_.size()) {
        factors.connectedness_.data_ = 1;
    } else {
        factors.connectedness_.data_ = strokes_.size() - connected_points_;
    }
    
    factors.pressure_.data_ = Strokes::CalculateAveragePressure();
    factors.size_.data_ = Strokes::CalculateAverageLetterSize();
    factors.speed_.data_ = Strokes::CalculateAverageSpeed();
    factors.left_margin_.data_ = leftmost_x_;
    factors.right_margin_.data_ = ofGetWindowWidth() - rightmost_x_;
}

uint Strokes::GetNumStrokes() {
    return strokes_.size();
}

// Testing method to make sure strokes are being stored correctly.
void Strokes::DrawStrokes() {
    for (auto stroke : strokes_) {
        stroke.draw();
    }
}
