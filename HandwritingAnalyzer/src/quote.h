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
    void Setup(const std::string& quote);
    const uint& GetNumWords();
    const uint& GetNumLetters();
    const std::string& GetQuote();
};
    
}

#endif /* quote_h */
