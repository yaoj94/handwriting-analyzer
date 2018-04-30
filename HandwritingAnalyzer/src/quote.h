#ifndef quote_h
#define quote_h

#include <stdio.h>
#include <string>
#include "ofMain.h"

namespace handwritinganalysis {

class Quote {
private:
    std::string quote_;
    uint num_words_;
    uint num_letters_;
    
public:
    Quote();
    
    // Setup method that initializes variables and counts number of words and letters
    void Setup(const std::string& quote);
    
    // Returns number of words in quote
    const uint& GetNumWords();
    
    // Returns number of letters in quote
    const uint& GetNumLetters();
    
    // Returns string quote
    const std::string& GetQuote();
};
    
}

#endif /* quote_h */
