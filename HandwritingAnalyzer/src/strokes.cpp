#include "strokes.h"

Strokes::Strokes() {}

void Strokes::addPoint(const ofPoint& point, float& pressure) {
    currStroke_.lineTo(point);
    pen_pressures_.push_back(pressure);
}

void Strokes::endStroke() {
    strokes_.push_back(currStroke_);
    currStroke_.clear();
}

void Strokes::clearStrokes() {
    currStroke_.clear();
    strokes_.clear();
}
