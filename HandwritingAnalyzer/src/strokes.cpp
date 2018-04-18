#include "strokes.h"

Strokes::Strokes() : total_time_millis_(0), perimeter_(0), reset_timer_(true), left_margin_(0), right_margin_(0), letter_size_(0), leftmost_x(ofGetWindowWidth()), rightmost_x(0) {
}

void Strokes::AddPoint(const ofPoint& point, float& pressure) {
    curr_stroke_.lineTo(point);
    pen_pressures_.push_back(pressure);
    
    if (reset_timer_) {
        ofResetElapsedTimeCounter();
        reset_timer_ = false;
    }
    
    // find leftmost and rightmost x coordinate for margins
    if (point.x < leftmost_x) {
        leftmost_x = point.x;
    }
    if (point.x > rightmost_x) {
        rightmost_x = point.x;
    }
}

void Strokes::EndStroke() {
    perimeter_ += curr_stroke_.getPerimeter();
    strokes_.push_back(curr_stroke_);
    curr_stroke_.clear();
    total_time_millis_ += ofGetElapsedTimeMillis();
    reset_timer_ = true;
}

void Strokes::ResetStrokes() {
    curr_stroke_.clear();
    strokes_.clear();
    pen_pressures_.clear();
    perimeter_ = 0;
    total_time_millis_ = 0;
    reset_timer_ = true;
    leftmost_x = ofGetWindowWidth();
    rightmost_x = 0;
    left_margin_ = 0;
    right_margin_ = 0;
    letter_size_ = 0;
    connectedness_ = 0;
}

void Strokes::DrawStrokes() {
    for (auto stroke : strokes_) {
        stroke.draw();
    }
}

int Strokes::GetLength() {
    return strokes_.size();
}

// returns a number ranging from around 15 for slow and 45 for fast
uint Strokes::GetAverageSpeed() {
    if (total_time_millis_ <= 0 || perimeter_ <= 0) {
        return 0;
    }

    double speed = perimeter_/total_time_millis_;
    return int(speed * 100);
}

// returns number ranging from 1-33 for light, 33-66 for medium, 66-100 for heavy
uint Strokes::CalculateAveragePressure() {
    uint total_pressure = 0;
    for (float pressure : pen_pressures_) {
        total_pressure += pressure;
    }
    return total_pressure/pen_pressures_.size();
}

void Strokes::Analyze() {
    int average = 0;
    // find AVERAGE max y-coord and min y-coord
    for (auto stroke : strokes_) {
        int upper_y = 0;
        int lower_y = 0;
        if (stroke.getPerimeter() >= 50) {
            int center_x = stroke.getPointAtPercent(.5).x;
            lower_y = stroke.getClosestPoint(ofPoint(center_x, 0)).y;
            upper_y = stroke.getClosestPoint(ofPoint(center_x, ofGetWindowHeight())).y;
        }
        
        int difference = upper_y - lower_y;
        if (average == 0) {
            average += difference;
        } else {
            average = (average + difference) / 2;
        }
    }
    
    letter_size_ = average;
    
    left_margin_ = leftmost_x;
    right_margin_ = ofGetWindowWidth() - rightmost_x;
}

int Strokes::GetLetterSize() {
    return letter_size_;
}

int Strokes::GetLeftMargin() {
    return left_margin_;
}

int Strokes::GetRightMargin() {
    return right_margin_;
}

