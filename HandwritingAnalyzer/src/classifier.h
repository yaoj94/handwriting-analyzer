#ifndef classifier_h
#define classifier_h

#include <stdio.h>
#include "factors.h"

namespace handwritinganalysis {
    
class Classifier {
private:
    // ranges from 1 - 100 but typical handwriting is probably from ~30 - 70
    const uint kPressureMid = 60;
    const uint kPressureLow = 45;

    // ranges from ~10 - 50
    const uint kSizeMid = 26;
    const uint kSizeLow = 18;
    
    // ranges from ~10 - 30
    const uint kSpeedMid = 25;
    const uint kSpeedLow = 15;
    
    const uint kMarginsMid = ofGetWindowWidth() / 8;
    const uint kMarginsLow = ofGetWindowWidth() / 20;
    
    HandwritingFactors factors_;
    uint num_words_;
    uint num_letters_;
    
public:
    Classifier();
    void Classify(uint words, uint letters);
    void SetBounds();
    HandwritingFactors& GetFactors();
};
    
} // namespace handwritinganalysis

#endif /* classifier_h */
