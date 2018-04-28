#include "tests.h"
using namespace handwritinganalysis;

TEST_CASE("Files are read and Attributes are set correctly") {
    HandwritingFactors factors;
    factors.ReadAttributesFromFile("attributes");
    
    SECTION("Pressure") {
        REQUIRE(factors.pressure_.attribute_.description_low_ == kPressureDescriptionLow);
        REQUIRE(factors.pressure_.attribute_.description_med_ == kPressureDescriptionMed);
        REQUIRE(factors.pressure_.attribute_.description_high_ == kPressureDescriptionHigh);
    }
    
    SECTION("Size") {
        REQUIRE(factors.size_.attribute_.description_low_ == kSizeDescriptionLow);
        REQUIRE(factors.size_.attribute_.description_med_ == kSizeDescriptionMed);
        REQUIRE(factors.size_.attribute_.description_high_ == kSizeDescriptionHigh);
    }
    
    SECTION("Speed") {
        REQUIRE(factors.speed_.attribute_.description_low_ == kSpeedDescriptionLow);
        REQUIRE(factors.speed_.attribute_.description_med_ == kSpeedDescriptionMed);
        REQUIRE(factors.speed_.attribute_.description_high_ == kSpeedDescriptionHigh);
    }
    
    SECTION("Connectedness") {
        REQUIRE(factors.connectedness_.attribute_.description_low_ == kConnectednessDescriptionLow);
        REQUIRE(factors.connectedness_.attribute_.description_med_ == kConnectednessDescriptionMed);
        REQUIRE(factors.connectedness_.attribute_.description_high_ == kConnectednessDescriptionHigh);
    }
    
    SECTION("Left Margin") {
        REQUIRE(factors.left_margin_.attribute_.description_low_ == kLMarginDescriptionLow);
        REQUIRE(factors.left_margin_.attribute_.description_med_ == kLMarginDescriptionMed);
        REQUIRE(factors.left_margin_.attribute_.description_high_ == kLMarginDescriptionHigh);
    }
    
    SECTION("Right Margin") {
        REQUIRE(factors.right_margin_.attribute_.description_low_ == kRMarginDescriptionLow);
        REQUIRE(factors.right_margin_.attribute_.description_med_ == kRMarginDescriptionMed);
        REQUIRE(factors.right_margin_.attribute_.description_high_ == kRMarginDescriptionHigh);
    }
}

TEST_CASE("Classifier outputs correct Attribute") {
    Classifier classifier;
    classifier.GetFactors().ReadAttributesFromFile("attributes");

    SECTION("LOW") {
        classifier.GetFactors().pressure_.data_ = 40;
        classifier.GetFactors().size_.data_ = 15;
        classifier.GetFactors().speed_.data_ = 10;
        classifier.GetFactors().connectedness_.data_ = kNumWords;
        classifier.GetFactors().left_margin_.data_ = 60;
        classifier.GetFactors().right_margin_.data_ = 60;

        classifier.Classify(kNumWords, kNumLetters);
        REQUIRE(classifier.GetFactors().pressure_.GetAttribute() == kPressureDescriptionLow);
        REQUIRE(classifier.GetFactors().size_.GetAttribute() == kSizeDescriptionLow);
        REQUIRE(classifier.GetFactors().speed_.GetAttribute() == kSpeedDescriptionLow);
        REQUIRE(classifier.GetFactors().connectedness_.GetAttribute() == kConnectednessDescriptionLow);
        REQUIRE(classifier.GetFactors().left_margin_.GetAttribute() == kLMarginDescriptionLow);
        REQUIRE(classifier.GetFactors().right_margin_.GetAttribute() == kRMarginDescriptionLow);
    }

    SECTION("MED") {
        classifier.GetFactors().pressure_.data_ = 50;
        classifier.GetFactors().size_.data_ = 20;
        classifier.GetFactors().speed_.data_ = 20;
        classifier.GetFactors().connectedness_.data_ = kNumWords * 2;
        classifier.GetFactors().left_margin_.data_ = 100;
        classifier.GetFactors().right_margin_.data_ = 100;

        classifier.Classify(kNumWords, kNumLetters);
        REQUIRE(classifier.GetFactors().pressure_.GetAttribute() == kPressureDescriptionMed);
        REQUIRE(classifier.GetFactors().size_.GetAttribute() == kSizeDescriptionMed);
        REQUIRE(classifier.GetFactors().speed_.GetAttribute() == kSpeedDescriptionMed);
        REQUIRE(classifier.GetFactors().connectedness_.GetAttribute() == kConnectednessDescriptionMed);
        REQUIRE(classifier.GetFactors().left_margin_.GetAttribute() == kLMarginDescriptionMed);
        REQUIRE(classifier.GetFactors().right_margin_.GetAttribute() == kRMarginDescriptionMed);

    }

    SECTION("HIGH") {
        classifier.GetFactors().pressure_.data_ = 70;
        classifier.GetFactors().size_.data_ = 30;
        classifier.GetFactors().speed_.data_ = 30;
        classifier.GetFactors().connectedness_.data_ = kNumLetters;
        classifier.GetFactors().left_margin_.data_ = 200;
        classifier.GetFactors().right_margin_.data_ = 200;

        classifier.Classify(kNumWords, kNumLetters);
        REQUIRE(classifier.GetFactors().pressure_.GetAttribute() == kPressureDescriptionHigh);
        REQUIRE(classifier.GetFactors().size_.GetAttribute() == kSizeDescriptionHigh);
        REQUIRE(classifier.GetFactors().speed_.GetAttribute() == kSpeedDescriptionHigh);
        REQUIRE(classifier.GetFactors().connectedness_.GetAttribute() == kConnectednessDescriptionHigh);
        REQUIRE(classifier.GetFactors().left_margin_.GetAttribute() == kLMarginDescriptionHigh);
        REQUIRE(classifier.GetFactors().right_margin_.GetAttribute() == kRMarginDescriptionHigh);
    }
}
