# Handwriting Analyzer

This project analyzes handwriting using a Wacom Tablet where a person writes onto the tablet and a list of personalities are generated based on certain characteristics of their handwriting. Data from the tablet will be collected to find certain patterns in the handwriting such as pressure, speed, size, etc. It consists of 2 stages: one for the person to write a sentence and another to display the personalities. 

## How to Use

This is an OpenFrameworks program and requires the addons, [ofxTablet](https://github.com/mattebb/ofxTablet) and [ofxAVString](https://github.com/hideyukisaito/ofxAVString). To build the program, simply clone the aforementioned addons and add them to the project. When running the program, it will open in fullscreen mode. To exit, press ESC.

The program was written and currently tested on XCode and MacOS. It was tested using the Wacom Intuos Pen and Touch Tablet, thus Wacom Tablet drivers should be installed and a tablet is required. 

## Testing

Tests were ran with the Catch framework. In order to run the tests, `#include "ofMain.h"` has to be removed and `uint` should be replaced with `unsigned int` for the code to compile correctly.
