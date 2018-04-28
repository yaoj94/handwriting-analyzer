#include "classifier.h"
using namespace handwritinganalysis;

Classifier::Classifier() {};

void Classifier::Classify(uint words, uint letters) {
    num_words_ = words;
    num_letters_ = letters;
    SetBounds();
    for (auto factor : factors_.factors_array_) {
        factor->CalculateLevel();
    }
}

void Classifier::SetBounds() {
    factors_.pressure_.middle_bound_ = kPressureMid;
    factors_.pressure_.lower_bound_ = kPressureLow;
    factors_.size_.middle_bound_ = kSizeMid;
    factors_.size_.lower_bound_ = kSizeLow;
    factors_.speed_.middle_bound_ = kSpeedMid;
    factors_.speed_.lower_bound_ = kSpeedLow;
    factors_.connectedness_.middle_bound_ = num_letters_ / 1.2;
    factors_.connectedness_.lower_bound_ = num_words_ * 1.5;
    factors_.left_margin_.middle_bound_ = ofGetWindowWidth() / 10;
    factors_.left_margin_.lower_bound_ = ofGetWindowWidth() / 20;
    factors_.right_margin_.middle_bound_ = ofGetWindowWidth() / 10;
    factors_.right_margin_.lower_bound_ = ofGetWindowWidth() / 20;
}

HandwritingFactors& Classifier::GetFactors() {
    return factors_;
}
