#include "strokes.h"

Strokes::Strokes() : total_time_millis_(0), perimeter_(0), reset_timer_(true), left_margin_(0), right_margin_(0), letter_size_(0), leftmost_x_(ofGetWindowWidth()), rightmost_x_(0), connectedness_(0), connected_points_(0) {
}

void Strokes::AddPoint(const ofPoint& point, float& pressure) {
    curr_stroke_.lineTo(point);
    pen_pressures_.push_back(pressure);
    
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

void Strokes::EndStroke() {
    perimeter_ += curr_stroke_.getPerimeter();
    strokes_.push_back(curr_stroke_);
    prev_stroke_ = curr_stroke_;
    curr_stroke_.clear();
    total_time_millis_ += ofGetElapsedTimeMillis();
    reset_timer_ = true;
    
}

void Strokes::ResetStrokes() {
    curr_stroke_.clear();
    prev_stroke_.clear();
    strokes_.clear();
    pen_pressures_.clear();
    
    perimeter_ = 0;
    
    total_time_millis_ = 0;
    reset_timer_ = true;
    
    leftmost_x_ = ofGetWindowWidth();
    rightmost_x_ = 0;
    left_margin_ = 0;
    right_margin_ = 0;
    
    letter_size_ = 0;
    
    connectedness_ = 0;
    connected_points_ = 0;
    
    speed_ = 0;
    avg_pressure_ = 0;
}

void Strokes::DrawStrokes() {
    for (auto stroke : strokes_) {
        stroke.draw();
    }
}

// returns a number ranging from around 15 for slow and 45 for fast
uint Strokes::CalculateAverageSpeed() {
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

uint Strokes::CalculateAverageLetterSize() {
    double average = 0;
    // find AVERAGE max y-coord and min y-coord
    for (auto stroke : strokes_) {
        double upper_y = 0;
        double lower_y = 0;
        
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
    
    return (uint) average;
}

void Strokes::Analyze() {
    letter_size_ = Strokes::CalculateAverageLetterSize();
    
    left_margin_ = leftmost_x_;
    right_margin_ = ofGetWindowWidth() - rightmost_x_;
    
    connectedness_ = strokes_.size() - connected_points_;
    
    avg_pressure_ = Strokes::CalculateAveragePressure();
    speed_ = Strokes::CalculateAverageSpeed();
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

int Strokes::GetConnectedness() {
    return connectedness_;
}

uint Strokes::GetSpeed() {
    return speed_;
}

uint Strokes::GetPressure() {
    return avg_pressure_;
}

int Strokes::GetLength() {
    return strokes_.size();
}
