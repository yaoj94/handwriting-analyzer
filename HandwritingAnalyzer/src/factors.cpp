#include "factors.h"

using namespace handwritinganalysis;

void Factor::CalculateLevel() {
    if (data_ >= middle_bound_) {
        level_ = HIGH;
    } else if (data_ >= lower_bound_) {
        level_ = MED;
    } else {
        level_ = LOW;
    }
}

void HandwritingFactors::ClearData() {
    pressure_.data_ = 0;
    size_.data_ = 0;
    speed_.data_ = 0;
    left_margin_.data_ = 0;
    right_margin_.data_ = 0;
}
