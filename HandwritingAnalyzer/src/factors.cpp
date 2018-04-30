#include "factors.h"
#include <fstream>
#include <iostream>

using namespace handwritinganalysis;

// This method calculates factor level based on bounds and data.
void Factor::CalculateLevel() {
    if (data >= middle_bound) {
        level = HIGH;
    } else if (data >= lower_bound) {
        level = MED;
    } else {
        level = LOW;
    }
}

// Returns attribute description based on level
const std::string& Factor::GetAttribute() {
    if (level == LOW) {
        return attribute.description_low;
    } else if (level == MED) {
        return attribute.description_med;
    } else {
        return attribute.description_high;
    }
}

// Constructor sets factors_array
HandwritingFactors::HandwritingFactors() {
    factors_array[0] = &pressure;
    factors_array[1] = &size;
    factors_array[2] = &speed;
    factors_array[3] = &connectedness;
    factors_array[4] = &left_margin;
    factors_array[5] = &right_margin;
}

// This method clears the data from factors.
void HandwritingFactors::ClearData() {
    for (auto factor : factors_array) {
        factor->data = 0;
    }
}

// This method reads in data from file and store in Attributes.
// Input: string name of file to extract data from
void HandwritingFactors::ReadAttributesFromFile(std::string filename) {
    std::ifstream attributes("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/bin/data/" + filename);
    
    if (!attributes) {
        std::cout << "Attributes file not found." << std::endl;
        exit (1);
    }
    
    int next_level;
    attributes >> next_level;
    
    for (auto factor : factors_array) {
        if (next_level == LOW) {
            std::getline(attributes, factor->attribute.description_low, '\n');
            attributes >> next_level;
        }
        
        if (next_level == MED) {
            std::getline(attributes, factor->attribute.description_med, '\n');
            attributes >> next_level;
        }
        
        if (next_level == HIGH) {
            std::getline(attributes, factor->attribute.description_high, '\n');
            attributes >> next_level;
        }
    }
    
    attributes.close();
}
