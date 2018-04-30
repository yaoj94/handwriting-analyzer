#include "tests.h"
using namespace handwritinganalysis;

TEST_CASE("Files are read and Attributes are set correctly") {
    HandwritingFactors factors;
    factors.ReadAttributesFromFile("attributes");
    
    SECTION("Pressure") {
        REQUIRE(factors.pressure.attribute.description_low == kPressureDescriptionLow);
        REQUIRE(factors.pressure.attribute.description_med == kPressureDescriptionMed);
        REQUIRE(factors.pressure.attribute.description_high == kPressureDescriptionHigh);
    }
    
    SECTION("Size") {
        REQUIRE(factors.size.attribute.description_low == kSizeDescriptionLow);
        REQUIRE(factors.size.attribute.description_med == kSizeDescriptionMed);
        REQUIRE(factors.size.attribute.description_high == kSizeDescriptionHigh);
    }
    
    SECTION("Speed") {
        REQUIRE(factors.speed.attribute.description_low == kSpeedDescriptionLow);
        REQUIRE(factors.speed.attribute.description_med == kSpeedDescriptionMed);
        REQUIRE(factors.speed.attribute.description_high == kSpeedDescriptionHigh);
    }
    
    SECTION("Connectedness") {
        REQUIRE(factors.connectedness.attribute.description_low == kConnectednessDescriptionLow);
        REQUIRE(factors.connectedness.attribute.description_med == kConnectednessDescriptionMed);
        REQUIRE(factors.connectedness.attribute.description_high == kConnectednessDescriptionHigh);
    }
    
    SECTION("Left Margin") {
        REQUIRE(factors.left_margin.attribute.description_low == kLMarginDescriptionLow);
        REQUIRE(factors.left_margin.attribute.description_med == kLMarginDescriptionMed);
        REQUIRE(factors.left_margin.attribute.description_high == kLMarginDescriptionHigh);
    }
    
    SECTION("Right Margin") {
        REQUIRE(factors.right_margin.attribute.description_low == kRMarginDescriptionLow);
        REQUIRE(factors.right_margin.attribute.description_med == kRMarginDescriptionMed);
        REQUIRE(factors.right_margin.attribute.description_high == kRMarginDescriptionHigh);
    }
}

TEST_CASE("Classifier outputs correct Attribute") {
    Classifier classifier;
    classifier.GetFactors().ReadAttributesFromFile("attributes");
    Quote quote;
    quote.Setup(quote_string);

    SECTION("LOW") {
        classifier.GetFactors().pressure.data = 40;
        classifier.GetFactors().size.data = 15;
        classifier.GetFactors().speed.data = 10;
        classifier.GetFactors().connectedness.data = 20;
        classifier.GetFactors().left_margin.data = 60;
        classifier.GetFactors().right_margin.data = 60;

        classifier.Classify(quote);
        REQUIRE(classifier.GetFactors().pressure.GetAttribute() == kPressureDescriptionLow);
        REQUIRE(classifier.GetFactors().size.GetAttribute() == kSizeDescriptionLow);
        REQUIRE(classifier.GetFactors().speed.GetAttribute() == kSpeedDescriptionLow);
        REQUIRE(classifier.GetFactors().connectedness.GetAttribute() == kConnectednessDescriptionLow);
        REQUIRE(classifier.GetFactors().left_margin.GetAttribute() == kLMarginDescriptionLow);
        REQUIRE(classifier.GetFactors().right_margin.GetAttribute() == kRMarginDescriptionLow);
    }

    SECTION("MED") {
        classifier.GetFactors().pressure.data = 50;
        classifier.GetFactors().size.data = 20;
        classifier.GetFactors().speed.data = 20;
        classifier.GetFactors().connectedness.data = 40;
        classifier.GetFactors().left_margin.data = 100;
        classifier.GetFactors().right_margin.data = 100;

        classifier.Classify(quote);
        REQUIRE(classifier.GetFactors().pressure.GetAttribute() == kPressureDescriptionMed);
        REQUIRE(classifier.GetFactors().size.GetAttribute() == kSizeDescriptionMed);
        REQUIRE(classifier.GetFactors().speed.GetAttribute() == kSpeedDescriptionMed);
        REQUIRE(classifier.GetFactors().connectedness.GetAttribute() == kConnectednessDescriptionMed);
        REQUIRE(classifier.GetFactors().left_margin.GetAttribute() == kLMarginDescriptionMed);
        REQUIRE(classifier.GetFactors().right_margin.GetAttribute() == kRMarginDescriptionMed);

    }

    SECTION("HIGH") {
        classifier.GetFactors().pressure.data = 70;
        classifier.GetFactors().size.data = 30;
        classifier.GetFactors().speed.data = 30;
        classifier.GetFactors().connectedness.data = 100;
        classifier.GetFactors().left_margin.data = 200;
        classifier.GetFactors().right_margin.data = 200;

        classifier.Classify(quote);
        REQUIRE(classifier.GetFactors().pressure.GetAttribute() == kPressureDescriptionHigh);
        REQUIRE(classifier.GetFactors().size.GetAttribute() == kSizeDescriptionHigh);
        REQUIRE(classifier.GetFactors().speed.GetAttribute() == kSpeedDescriptionHigh);
        REQUIRE(classifier.GetFactors().connectedness.GetAttribute() == kConnectednessDescriptionHigh);
        REQUIRE(classifier.GetFactors().left_margin.GetAttribute() == kLMarginDescriptionHigh);
        REQUIRE(classifier.GetFactors().right_margin.GetAttribute() == kRMarginDescriptionHigh);
    }
}

TEST_CASE("Quote object is set correctly") {
    Quote quote;

    SECTION("Empty strings") {
        quote.Setup("");
        REQUIRE(quote.GetNumWords() == 0);
        REQUIRE(quote.GetNumLetters() == 0);
    }

    SECTION("Leading spaces") {
        quote.Setup(" This is to test leading spaces.");
        REQUIRE(quote.GetNumWords() == 6);
        REQUIRE(quote.GetNumLetters() == 25);
    }

    SECTION("Trailing spaces") {
        quote.Setup("This is to test trailing spaces.  ");
        REQUIRE(quote.GetNumWords() == 6);
        REQUIRE(quote.GetNumLetters() == 26);
    }

    SECTION("Multiple spacing") {
        quote.Setup("  This is  to test   multiple   spacing.   ");
        REQUIRE(quote.GetNumWords() == 6);
        REQUIRE(quote.GetNumLetters() == 27);
    }

    SECTION("Escape sequences") {
        quote.Setup("This is to test\ttabs and\nnew lines.");
        REQUIRE(quote.GetNumWords() == 8);
        REQUIRE(quote.GetNumLetters() == 27);
    }

    SECTION("Normal case") {
        quote.Setup("This is to test a normal sentence.");
        REQUIRE(quote.GetNumWords() == 7);
        REQUIRE(quote.GetNumLetters() == 27);
    }
}