#ifndef factors_h
#define factors_h

#include <stdio.h>
#include "ofMain.h"

namespace handwritinganalysis {

enum Level {
    LOW = 0,
    MED,
    HIGH
};
    
struct Attribute {
    Attribute() {};
    std::string description_high_;
    std::string description_med_;
    std::string description_low_;
};

struct Factor {
    Factor() {};
    
    uint middle_bound_;
    uint lower_bound_;
    uint data_;
    
    Level level_;
    Attribute attribute_;
    
    void CalculateLevel();
    std::string GetAttribute();
};

struct HandwritingFactors {
    HandwritingFactors();
    
    // create array that points to all the factors to loop through
    std::array<Factor*, 6> factors_array_;
    
    Factor pressure_;       
    Factor size_;           
    Factor speed_;          
    Factor connectedness_;  // ranges from number of words to number of letters
                                // there are 2 ways for handwriting to be connected
                                // 1. writing in cursive or with few lifts
                                // 2. writing so close together that the letters intersect
    Factor left_margin_;
    Factor right_margin_;
    
    void ClearData();
    void ReadAttributesFromFile(std::string filename);
};
    
    
    
} // namespace handwritinganalysis

#endif /* factors_h */
