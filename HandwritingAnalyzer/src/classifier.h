#ifndef classifier_h
#define classifier_h

#include <stdio.h>
#include "factors.h"
#include "quote.h"

#define MARGINMIDFACTOR 0.125
#define MARGINLOWFACTOR 0.05

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
    
    const uint kMarginsMid = ofGetWindowWidth() * MARGINMIDFACTOR;
    const uint kMarginsLow = ofGetWindowWidth() * MARGINLOWFACTOR;
    
    HandwritingFactors factors_;
    
public:
    Classifier();
    
    // This method classifies factors based on bounds and data collected. It calls calculate level for each factor.
    void Classify(Quote& quote);
    
    // This method sets bounds for all Factors in factors_
    void SetBounds(Quote& quote);
    
    // Returns HandwritingFactors reference
    HandwritingFactors& GetFactors();
};
    
} // namespace handwritinganalysis

#endif /* classifier_h */
