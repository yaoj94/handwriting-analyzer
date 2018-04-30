#include "classifier.h"
using namespace handwritinganalysis;

#define WORDSFACTOR 1.5
#define LETTERSFACTOR 0.8

// Constructor
Classifier::Classifier() {};

// This method classifies factors based on bounds and data collected. It calls calculate level for each factor.
// Input: Quote object to set bounds with
void Classifier::Classify(Quote& quote) {
    SetBounds(quote);
    for (auto factor : factors_.factors_array) {
        factor->CalculateLevel();
    }
}

// This method sets bounds for all Factors in factors_
// Input: Quote object to extract data from
void Classifier::SetBounds(Quote& quote) {
    factors_.pressure.middle_bound = kPressureMid;
    factors_.pressure.lower_bound = kPressureLow;
    factors_.size.middle_bound = kSizeMid;
    factors_.size.lower_bound = kSizeLow;
    factors_.speed.middle_bound = kSpeedMid;
    factors_.speed.lower_bound = kSpeedLow;
    factors_.connectedness.middle_bound = uint(quote.GetNumLetters() * LETTERSFACTOR);
    factors_.connectedness.lower_bound = uint(quote.GetNumWords() * WORDSFACTOR);
    factors_.left_margin.middle_bound = kMarginsMid;
    factors_.left_margin.lower_bound = kMarginsLow;
    factors_.right_margin.middle_bound = kMarginsMid;
    factors_.right_margin.lower_bound = kMarginsLow;
}

// Returns HandwritingFactors reference
HandwritingFactors& Classifier::GetFactors() {
    return factors_;
}
