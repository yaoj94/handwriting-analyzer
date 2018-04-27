#include "ofApp.h"
#include "ofxTablet.h"
using namespace handwritinganalysis;

// Set up window, paths, and tablet
void HandwritingAnalyzer::setup(){
    ofSetWindowTitle("Handwriting Analyzer");
    ofBackground(0, 0, 0);

    ofHideCursor();
    
    pen_cursor_.load("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/data/pen.png");
    
    text_.load("/Users/Jenn/Documents/of_v0.9.8_osx_release/apps/myApps/final-project-yaoj94/HandwritingAnalyzer/data/Century Gothic", 18);
    
    paths_.setFilled(false); // don't fill paths
    background_lines_.setFilled(false);
    
    // set up background lines
    for (int i = 300; i < ofGetWindowHeight(); i += 100) {
        background_lines_.moveTo(ofPoint(0, i));
        background_lines_.lineTo(ofPoint(ofGetWindowWidth(), i));
    }
    
    // from ofxTablet example code
    ofxTablet::start();
    ofAddListener(ofxTablet::tabletEvent, this, &HandwritingAnalyzer::tabletMoved);
    
}

//--------------------------------------------------------------
void HandwritingAnalyzer::update(){

}

// Draws background, instructions, and paths
void HandwritingAnalyzer::draw(){
    if (curr_state_ == WRITE) {
        HandwritingAnalyzer::drawWriteState();
    } else {
        HandwritingAnalyzer::drawDisplayState();
    }
}

void HandwritingAnalyzer::drawWriteState() {
    HandwritingAnalyzer::drawBackgroundLines();
    
    ofSetColor(0, 255, 153);
    string instructions = "Write the following line. Press 'D' when done. Press 'C' to start over.";
    text_.drawString(instructions, 50, 80);
    
    ofSetColor(0, 153, 255);
    string quote1 = "Part of the inhumanity of the computer is that, once it is competently programmed and working";
    string quote2 = "smoothly, it is completely honest.";
    text_.drawString(quote1, 50, 120);
    text_.drawString(quote2, 50, 160);
    
    if (print_not_done_) {
        ofSetColor(204, 0, 0);
        string notdone = "Not enough data for analysis... Write some more!";
        text_.drawString(notdone, 50, 200);
    }
    
    HandwritingAnalyzer::drawPaths();
    HandwritingAnalyzer::drawCursor();
    
    //strokes_.drawStrokes();
}

void HandwritingAnalyzer::drawDisplayState() {
    
}

// Reads data from tablet once data is received and updates drawing state flags
void HandwritingAnalyzer::tabletMoved(TabletData &data) {
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
        strokes_.AddPoint(ofPoint(data.abs_screen[0], data.abs_screen[1]), curr_pressure_);
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
void HandwritingAnalyzer::keyPressed(int key){
    int upper_key = toupper(key);
    
    if (upper_key == 'D') {
        // Done: analyse strokes, check for doneness, change states
        strokes_.Analyze();
        
        // Print out data for testing
        std::cout << "Letter size: " << strokes_.GetFactors().size_.data_ << std::endl;
        std::cout << "Left Margin: " << strokes_.GetFactors().left_margin_.data_ << std::endl;
        std::cout << "Right Margin: " << strokes_.GetFactors().right_margin_.data_ << std::endl;
        std::cout << "Number of strokes: " << strokes_.GetNumStrokes() << std::endl;
        std::cout << "Average speed: " << strokes_.GetFactors().speed_.data_ << std::endl;
        std::cout << "Average pressure: " << strokes_.GetFactors().pressure_.data_ << std::endl;
        std::cout << "Connectedness: " << strokes_.GetFactors().connectedness_.data_ << std::endl;
        std::cout << std::endl;
        
        if (strokes_.GetNumStrokes() <= 20) { // number of words
            print_not_done_ = true;
        } else {
            curr_state_ = DISPLAY;
        }
    }
    if (upper_key == 'C') {
        // Clear all paths
        strokes_.ResetStrokes();
        paths_.clear();
    }
}

// Draws background lines
void HandwritingAnalyzer::drawBackgroundLines() {
    background_lines_.setStrokeWidth(1);
    background_lines_.setStrokeColor(ofColor(179, 236, 255));
    background_lines_.draw();
}

// Draws cursor wherever the pen is
void HandwritingAnalyzer::drawCursor() {
    ofSetColor(66, 179, 244);
    pen_cursor_.draw(ofxTablet::tabletData.abs_screen[0], ofxTablet::tabletData.abs_screen[1] - 45, 45, 45);

    // draw point to screen
    //ofSetColor(0, 255, 153);
    //ofDrawCircle(ofxTablet::tabletData.abs_screen[0], ofxTablet::tabletData.abs_screen[1], 2);
}

// Draws handwriting path to screen with set width and color
void HandwritingAnalyzer::drawPaths() {
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
float HandwritingAnalyzer::strokeWidthFromPressure(const float& pressure) {
    if (pressure >= 75) {
        return 7;
    } else if (pressure <= 5) {
        return 0.5;
    } else {
        return pressure / 20;
    }
}

//--------------------------------------------------------------
void HandwritingAnalyzer::keyReleased(int key){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void HandwritingAnalyzer::dragEvent(ofDragInfo dragInfo){ 

}
