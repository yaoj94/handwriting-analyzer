#include "ofApp.h"
#include "ofxTablet.h"

// Set up window, paths, and tablet
void ofApp::setup(){
    ofSetWindowTitle("Handwriting Analyzer");
    ofBackground(0, 0, 0);

    ofHideCursor();
    
    pen_cursor_.load("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/data/pen.png");
    
    text_.load("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/data/Century Gothic", 18);
    
    isDrawing_ = false;
    wasDrawing_ = false;
    
    paths_.setFilled(false); // don't fill paths
    background_lines_.setFilled(false);
    
    // set up background lines
    for (int i = 300; i < ofGetWindowHeight(); i += 100) {
        background_lines_.moveTo(ofPoint(0, i));
        background_lines_.lineTo(ofPoint(ofGetWindowWidth(), i));
    }
    
    // from ofxTablet example code
    ofxTablet::start();
    ofAddListener(ofxTablet::tabletEvent, this, &ofApp::tabletMoved);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

// Draws background, instructions, and paths
void ofApp::draw(){
    
    ofApp::drawBackground();
    
    ofSetColor(0, 255, 153);
    string instructions = "Write something! Press 'D' when done. Press 'C' to start over.";
    text_.drawString(instructions, 50, 80);
    //ofDrawBitmapString(instructions, 100, 30);
    
    ofApp::drawPaths();
    ofApp::drawCursor();
    
    //strokes_.drawStrokes();
}

// Reads data from tablet once data is received
void ofApp::tabletMoved(TabletData &data) {
    curr_pressure_ = data.pressure * 100;

    // Change drawing flags based on pressure
    if (curr_pressure_ >= 5) {
        if (!isDrawing_) {
            wasDrawing_ = false;
        } else {
            wasDrawing_ = true;
        }
        isDrawing_ = true;
        //std::cout << "Pressure: " << curr_pressure_ << std::endl;

    } else {
        if (isDrawing_) {
            wasDrawing_ = true;
        } else {
            wasDrawing_ = false; // one off
        }
        isDrawing_ = false;
    }
    
    // Add to path
    if (!wasDrawing_ && isDrawing_) {           // just started drawing
        paths_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        //curr_path_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
    } else if (isDrawing_) {                    // still drawing
        //curr_path_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.newSubPath(); //?
        strokes_.AddPoint(ofPoint(data.abs_screen[0], data.abs_screen[1]), curr_pressure_);
        //pressure_paths_.insert(make_pair(curr_pressure_, curr_path_));
        //curr_path_.clear();
        //curr_path_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
    } else if (wasDrawing_ && !isDrawing_) {    // just stopped drawing
        strokes_.EndStroke();
    }
}

// 'D' Changes state when user is done
// 'C' Clears strokes when user wants to start over
void ofApp::keyPressed(int key){
    int upper_key = toupper(key);
    
    if (upper_key == 'D') {
        // Done: analyse strokes, check for doneness, change states
        strokes_.Analyze();
        
        // Print out data for testing
        std::cout << "Letter size: " << strokes_.GetLetterSize() << std::endl;
        std::cout << "Left Margin: " << strokes_.GetLeftMargin() << std::endl;
        std::cout << "Right Margin: " << strokes_.GetRightMargin() << std::endl;
        std::cout << "Number of strokes: " << strokes_.GetNumStrokes() << std::endl;
        std::cout << "Average speed: " << strokes_.GetSpeed() << std::endl;
        std::cout << "Average pressure: " << strokes_.GetPressure() << std::endl;
        std::cout << "Connectedness: " << strokes_.GetConnectedness() << std::endl;
        std::cout << std::endl;
    }
    if (upper_key == 'C') {
        // Clear all paths
        strokes_.ResetStrokes();
        paths_.clear();
    }
}

// Draws background lines
void ofApp::drawBackground() {
    background_lines_.setStrokeWidth(1);
    background_lines_.setStrokeColor(ofColor(179, 236, 255));
    background_lines_.draw();
}

// Draws cursor wherever the pen is
void ofApp::drawCursor() {
    ofSetColor(66, 179, 244);
    pen_cursor_.draw(ofxTablet::tabletData.abs_screen[0], ofxTablet::tabletData.abs_screen[1] - 45, 45, 45);

    // draw point to screen
    //ofSetColor(0, 255, 153);
    //ofDrawCircle(ofxTablet::tabletData.abs_screen[0], ofxTablet::tabletData.abs_screen[1], 2);
}

// Draws handwriting path to screen with set width and color
void ofApp::drawPaths() {
    paths_.setStrokeWidth(2);
    paths_.setStrokeColor(ofColor(255, 255, 255));
    paths_.draw();
    
    /* test code for changing pressure
     for (auto path : pressure_paths_) {
     path.second.setStrokeColor(ofColor(255, 255, 255));
     path.second.setStrokeWidth(strokeWidthFromPressure(path.first));
     path.second.draw();
     }*/
}

// Calculates the width of the stroke based on pressure
float ofApp::strokeWidthFromPressure(const float& pressure) {
    if (pressure >= 75) {
        return 7;
    } else if (pressure <= 5) {
        return 0.5;
    } else {
        return pressure / 20;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
