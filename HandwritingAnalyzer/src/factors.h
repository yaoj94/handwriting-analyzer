#ifndef factors_h
#define factors_h

#include <stdio.h>
#include "ofMain.h"

namespace handwritinganalysis {

// Variables to classify level of factor
enum Level {
    LOW = 0,
    MED,
    HIGH
};

// Stores descriptions for attribute
struct Attribute {
    Attribute() {};
    std::string description_high;
    std::string description_med;
    std::string description_low;
};

// Stores data and attribute
struct Factor {
    Factor() {};
    
    uint middle_bound;
    uint lower_bound;
    uint data;
    ofColor color;
    
    Level level;
    Attribute attribute;
    
    // This method calculates factor level based on bounds and data.
    void CalculateLevel();
    
    // Returns attribute description based on level
    const std::string& GetAttribute();
};

// Stores info for Display state background
struct FactorBubble {
    int x;
    int y;
    int radius;
    ofColor color;
};

// Stores all factors for handwriting analysis
struct HandwritingFactors {
    HandwritingFactors();
    
    // create array that points to all the factors to loop through
    std::array<Factor*, 6> factors_array;
    
    // handwriting factors
    Factor pressure;       
    Factor size;           
    Factor speed;          
    Factor connectedness;  
    Factor left_margin;
    Factor right_margin;
    
    // This method clears the data from factors.
    void ClearData();
    
    // This method reads in data from file and store in Attributes.
    void ReadAttributesFromFile(std::string filename);
};
    
    
} // namespace handwritinganalysis

#endif /* factors_h */
