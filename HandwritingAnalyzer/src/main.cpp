#include "ofMain.h"
#include "ofApp.h"
using namespace handwritinganalysis;

//========================================================================
int main( ){
	ofSetupOpenGL(2560, 1600, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new HandwritingAnalyzer());

}
