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
    std::string description_high;
    std::string description_med;
    std::string description_low;
};

struct Factor {
    Factor() {};
    
    uint middle_bound;
    uint lower_bound;
    uint data;
    
    Level level;
    Attribute attribute;
    
    void CalculateLevel();
    const std::string& GetAttribute();
};

struct HandwritingFactors {
    HandwritingFactors();
    
    // create array that points to all the factors to loop through
    std::array<Factor*, 6> factors_array;
    
    Factor pressure;       
    Factor size;           
    Factor speed;          
    Factor connectedness;  // ranges from number of words to number of letters
                                // there are 2 ways for handwriting to be connected
                                // 1. writing in cursive or with few lifts
                                // 2. writing so close together that the letters intersect
    Factor left_margin;
    Factor right_margin;
    
    void ClearData();
    void ReadAttributesFromFile(std::string filename);
};
    
} // namespace handwritinganalysis

#endif /* factors_h */
