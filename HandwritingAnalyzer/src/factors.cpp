#include "factors.h"
#include <fstream>
#include <iostream>

using namespace handwritinganalysis;

void Factor::CalculateLevel() {
    if (data_ >= middle_bound_) {
        level_ = HIGH;
    } else if (data_ >= lower_bound_) {
        level_ = MED;
    } else {
        level_ = LOW;
    }
}

std::string Factor::GetAttribute() {
    if (level_ == LOW) {
        return attribute_.description_low_;
    } else if (level_ == MED) {
        return attribute_.description_med_;
    } else {
        return attribute_.description_high_;
    }
}

HandwritingFactors::HandwritingFactors() {
    factors_array_[0] = &pressure_;
    factors_array_[1] = &size_;
    factors_array_[2] = &speed_;
    factors_array_[3] = &connectedness_;
    factors_array_[4] = &left_margin_;
    factors_array_[5] = &right_margin_;
}

void HandwritingFactors::ClearData() {
    for (auto factor : factors_array_) {
        factor->data_ = 0;
    }
}

// read in data from file and store in Attributes
void HandwritingFactors::ReadAttributesFromFile(std::string filename) {
    std::ifstream attributes("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/bin/data/" + filename);
    
    if (!attributes) {
        std::cout << "Attributes file not found." << std::endl;
        exit (1);
    }
    
    int next_level;
    attributes >> next_level;
    
    for (auto factor : factors_array_) {
        // low
        if (next_level == LOW) {
            std::getline(attributes, factor->attribute_.description_low_, '\n');
            attributes >> next_level;
        }
        
        // med
        if (next_level == MED) {
            std::getline(attributes, factor->attribute_.description_med_, '\n');
            attributes >> next_level;
        }
        
        // high
        if (next_level == HIGH) {
            std::getline(attributes, factor->attribute_.description_high_, '\n');
            attributes >> next_level;
        }
    }
    
    attributes.close();
}
