#include "classifier.h"
using namespace handwritinganalysis;

Classifier::Classifier(Strokes strokes, uint words) : strokes_(strokes), factors_(strokes.GetFactors()),
                                                      num_words_(words) {
    factors_.pressure_.middle_bound_ = kPressureMid;
    factors_.pressure_.lower_bound_ = kPressureLow;
    factors_.size_.middle_bound_ = kSizeMid;
    factors_.size_.lower_bound_ = kSizeLow;
    factors_.speed_.middle_bound_ = kSpeedMid;
    factors_.speed_.lower_bound_ = kSpeedLow;
    factors_.connectedness_.middle_bound_ = kConnectednessMid;
    factors_.connectedness_.lower_bound_ = kConnectednessLow;
    factors_.left_margin_.middle_bound_ = kMarginsMid;
    factors_.left_margin_.lower_bound_ = kMarginsLow;
    factors_.right_margin_.middle_bound_ = kMarginsMid;
    factors_.right_margin_.lower_bound_ = kMarginsLow;
}

