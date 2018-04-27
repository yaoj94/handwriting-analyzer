#ifndef factors_h
#define factors_h

#include <stdio.h>
#include "ofMain.h"

namespace handwritinganalysis {

enum Level {
    LOW,
    MED,
    HIGH
};

struct Factor {
    Factor() {}
    
    uint middle_bound_;
    uint lower_bound_;
    uint data_;
    
    Level level_;
    
    void CalculateLevel();
};

struct HandwritingFactors {
    HandwritingFactors() {};
    
    Factor pressure_;       // ranges from 1 - 100 but typical handwriting is probably from ~30 - 70
    Factor size_;           // ranges from ~10 - 50
    Factor speed_;          // ranges from ~10 - 30
    Factor connectedness_;  // ranges from number of words to number of letters
                                // there are 2 ways for handwriting to be connected
                                // 1. writing in cursive or with few lifts
                                // 2. writing so close together that the letters intersect
    Factor left_margin_;
    Factor right_margin_;
    
    void ClearData();
};
    
} // namespace handwritinganalysis

#endif /* factors_h */
