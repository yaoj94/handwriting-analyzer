#ifndef classifier_h
#define classifier_h

#include <stdio.h>
#include "strokes.h"
#include "factors.h"

namespace handwritinganalysis {
    
class Classifier {
    const uint kPressureMid = 60;
    const uint kPressureLow = 45;

    const uint kSizeMid = 38;
    const uint kSizeLow = 22;
    
    const uint kSpeedMid = 25;
    const uint kSpeedLow = 15;
    
    const uint kConnectednessMid = num_words_;
    const uint kConnectednessLow = num_words_ / 2;
    
    const uint kMarginsMid = ofGetWindowWidth() / 10;
    const uint kMarginsLow = ofGetWindowWidth() / 20;
    
    Strokes strokes_;
    HandwritingFactors factors_;
    uint num_words_;
    
public:
    Classifier(Strokes strokes, uint words);
};
    
} // namespace handwritinganalysis

#endif /* classifier_h */
