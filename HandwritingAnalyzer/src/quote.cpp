#include "quote.h"
using namespace handwritinganalysis;

Quote::Quote() : num_words_(0), num_letters_(0) { }

void Quote::Setup(const std::string& quote) {
    quote_ = quote;
    num_words_ = 0;
    num_letters_ = 0;
    
    // Code below derived from: https://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
    if (isalnum(quote_[0])) {
        num_words_++;
        num_letters_++;
    }
    
    for (int i = 1; i < quote_.length(); i++) {
        if (isalnum(quote_[i])) {
            num_letters_++;
            if (iswspace(quote_[i-1])) {
                num_words_++;
            }
        }
    }
}

const uint& Quote::GetNumWords() {
    return num_words_;
}

const uint& Quote::GetNumLetters() {
    return num_letters_;
}

const std::string& Quote::GetQuote() {
    return quote_;
}
