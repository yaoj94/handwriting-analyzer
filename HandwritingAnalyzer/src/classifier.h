#ifndef classifier_h
#define classifier_h

#include <stdio.h>
#include "strokes.h"
#include "factors.h"

namespace handwritinganalysis {
    
class Classifier {
    const uint kPressureMid = 60;
    const uint kPressureLow = 45;

    const uint kSizeMid = 26;
    const uint kSizeLow = 18;
    
    const uint kSpeedMid = 25;
    const uint kSpeedLow = 15;
    
    const uint kConnectednessMid = num_words_;
    const uint kConnectednessLow = num_words_ / 2;
    
    const uint kMarginsMid = ofGetWindowWidth() / 20;
    const uint kMarginsLow = ofGetWindowWidth() / 10;
    
    //Strokes& strokes_;
    HandwritingFactors factors_;
    uint num_words_;
    uint num_letters_;
    
public:
    Classifier();
    //Classifier(Strokes strokes, uint words);
    void Classify(uint words, uint letters);
    void SetBounds();
    //void Setup(HandwritingFactors& factors);
    HandwritingFactors& GetFactors();
};
    
} // namespace handwritinganalysis

#endif /* classifier_h */
