#ifndef tests_h
#define tests_h

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "classifier.h"
#include "factors.h"
#include "quote.h"

const std::string kPressureDescriptionLow = "are empathetic and sensitive";
const std::string kPressureDescriptionMed = "are committed to what they do and take things seriously";
const std::string kPressureDescriptionHigh = "are tense and quick to react";

const std::string kSizeDescriptionLow = "are introverted";
const std::string kSizeDescriptionMed = "have a strong ability to focus";
const std::string kSizeDescriptionHigh = "are extroverted";

const std::string kSpeedDescriptionLow = "are cautious of their actions";
const std::string kSpeedDescriptionMed = "have a good balance of patience";
const std::string kSpeedDescriptionHigh = "tend to be impulsive";

const std::string kConnectednessDescriptionLow = "tend to be stubborn and rigid";
const std::string kConnectednessDescriptionMed = "adapt easily to environments";
const std::string kConnectednessDescriptionHigh = "are adventurous";

const std::string kLMarginDescriptionLow = "are unsure about current situations";
const std::string kLMarginDescriptionMed = "are content with current situations";
const std::string kLMarginDescriptionHigh = "are ambitious";

const std::string kRMarginDescriptionLow = "are eager to move on";
const std::string kRMarginDescriptionMed = "are easygoing";
const std::string kRMarginDescriptionHigh = "fear the unknown";

const std::string quote_string = "Part of the inhumanity of the computer is that, once it is competently programmed "
        "and working\nsmoothly, it is completely honest.";

#endif /* tests_h */
