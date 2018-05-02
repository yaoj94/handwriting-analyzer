# Handwriting Analyzer

This project analyzes handwriting using a Wacom Tablet where a person writes onto the tablet and a list of personalities are generated based on certain characteristics of their handwriting. Data from the tablet will be collected to find certain patterns in the handwriting such as pressure, speed, size, etc. It consists of 2 stages: one for the person to write a sentence and another to display the personalities. 

## How to Use

This is an OpenFrameworks program and requires the addons, ofxTablet and ofxAVString. It was tested using the Wacom Intuos Tablet, thus Wacom Tablet drivers should be installed and a tablet is required.

The program was written and currently tested on XCode and MacOS.

## Testing

Tests were ran with the Catch framework. In order to run the tests, `#include "ofMain.h"` has to be removed and `uint` should be replaced with `unsigned int` for the code to compile correctly.
