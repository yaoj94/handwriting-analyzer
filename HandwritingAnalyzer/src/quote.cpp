#include "quote.h"
using namespace handwritinganalysis;

// Constructor
Quote::Quote() : num_words_(0), num_letters_(0) { }

// Setup method that initializes variables and counts number of words and letters
void Quote::Setup(const std::string& quote) {
    quote_ = quote;
    
    // Reset variables in case method is called multiple times
    num_words_ = 0;
    num_letters_ = 0;
    
    // Count number of words and letters. Code below derived from:
    // https://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
    if (isalnum(quote_[0])) {
        num_words_++;
        num_letters_++;
    }
    
    for (int i = 1; i < quote_.length(); i++) {
        if (isalnum(quote_[i])) {           // Current character is letter or number
            num_letters_++;
            if (iswspace(quote_[i-1])) {    // Previous character is whitespace
                num_words_++;
            }
        }
    }
}

// Returns number of words in quote
const uint& Quote::GetNumWords() {
    return num_words_;
}

// Returns number of letters in quote
const uint& Quote::GetNumLetters() {
    return num_letters_;
}

// Returns string quote
const std::string& Quote::GetQuote() {
    return quote_;
}
