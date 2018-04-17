#include "strokes.h"

Strokes::Strokes() : total_time_millis_(0), perimeter_(0), reset_timer_(true) {

}

void Strokes::addPoint(const ofPoint& point, float& pressure) {
    currStroke_.lineTo(point);
    pen_pressures_.push_back(pressure);
    
    if (reset_timer_) {
        ofResetElapsedTimeCounter();
        reset_timer_ = false;
    }
}

void Strokes::endStroke() {
    perimeter_ += currStroke_.getPerimeter();
    strokes_.push_back(currStroke_);
    currStroke_.clear();
    total_time_millis_ += ofGetElapsedTimeMillis();
    reset_timer_ = true;
}

void Strokes::resetStrokes() {
    currStroke_.clear();
    strokes_.clear();
    pen_pressures_.clear();
    perimeter_ = 0;
    total_time_millis_ = 0;
    reset_timer_ = true;
}

void Strokes::drawStrokes() {
    for (auto stroke : strokes_) {
        stroke.draw();
    }
}

int Strokes::getLength() {
    return strokes_.size();
}

// returns a number ranging from around 15 for slow and 45 for fast
uint Strokes::getAverageSpeed() {
    if (total_time_millis_ <= 0 || perimeter_ <= 0) {
        return 0;
    }

    double speed = perimeter_/total_time_millis_;
    return int(speed * 100);
}

// returns number ranging from 1-33 for light, 33-66 for medium, 66-100 for heavy
uint Strokes::calculateAveragePressure() {
    uint total_pressure = 0;
    for (float pressure : pen_pressures_) {
        total_pressure += pressure;
    }
    return total_pressure/pen_pressures_.size();
}
