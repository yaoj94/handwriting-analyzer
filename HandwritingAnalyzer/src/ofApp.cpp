#include "ofApp.h"
#include "ofxTablet.h"
using namespace handwritinganalysis;

// Set up window, paths, and tablet
void HandwritingAnalyzer::setup(){
    classifier_.GetFactors().ReadAttributesFromFile("attributes");
    quote_.Setup("Part of the inhumanity of the computer is that, once it is competently programmed and working\nsmoothly, it is completely honest.");

    /*// Print out all the attributes
    for (auto factor : classifier_.GetFactors().factors_array_) {
        std::cout << factor->attribute_.description_low_ << std::endl;
        std::cout << factor->attribute_.description_med_ << std::endl;
        std::cout << factor->attribute_.description_high_ << std::endl;
    }*/

    ofSetWindowTitle("Handwriting Analyzer");
    ofBackground(0, 0, 0);

    ofHideCursor();
    
    pen_cursor_.load("pen.png");
    write_text_.load("Century Gothic", 18);
    display_text_.load("Gabriola.ttf", 30);
    attribute_text_.load("Gabriola.ttf", 45);
    disclaimer_.load("PrestigeEliteStd-Bd.otf", 8);
    
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

// Update which factor gets printed to screen during DISPLAY state
void HandwritingAnalyzer::update(){
    if (curr_state_ == DISPLAY && ofGetElapsedTimeMillis() - last_update_time_ >= kAttributeUpdatePeriod) {
        avs_.setup(classifier_.GetFactors().factors_array[factor_index_]->GetAttribute());
        avs_.play(5, 1000);
        last_update_time_ = ofGetElapsedTimeMillis();
        
        // Increment factor
        factor_index_++;
        if (factor_index_ >= classifier_.GetFactors().factors_array.size()) {
            factor_index_ = 0;
        }
    }
}

// Draws write state and display state
void HandwritingAnalyzer::draw(){
    if (curr_state_ == WRITE) {
        HandwritingAnalyzer::drawWriteState();
    } else {
        HandwritingAnalyzer::drawDisplayState();
    }
}

// Draws instructions, quote, and paths to screen
void HandwritingAnalyzer::drawWriteState() {
    HandwritingAnalyzer::drawBackgroundLines();
    
    ofSetColor(0, 255, 153);
    string instructions = "Write the following line. Press 'D' when done. Press 'C' to start over.";
    write_text_.drawString(instructions, 50, 80);
    
    ofSetColor(0, 153, 255);
    write_text_.drawString(quote_.GetQuote(), 50, 120);
    
    if (print_not_done_) {
        ofSetColor(204, 0, 0);
        string notdone = "Not enough data for analysis... Write some more!";
        write_text_.drawString(notdone, 50, 200);
    }
    
    HandwritingAnalyzer::drawPaths();
    HandwritingAnalyzer::drawCursor();
    
    //strokes_.drawStrokes();
}

// Draws attributes and disclaimer to screen
void HandwritingAnalyzer::drawDisplayState() {
    ofSetColor(153, 102, 255);
    string intro = "People with your handwriting style typically . . . ";
    display_text_.drawString(intro, 100, 80);
    
    ofSetColor(204, 255, 102);
    attribute_text_.drawString(avs_, 75, ofGetWindowHeight() / 2);
    
    /*
    int position = 150;
    for (auto factor : classifier_.GetFactors().factors_array_) {
        display_text_.drawString(factor->GetAttribute(), 80, position);
        position += 70;
    }*/
    
    ofSetColor(200, 200, 200);
    string disclaimer = "Disclaimer: The results from this test are for entertainment purposes only and are not clinically proven. Use the information at your own risk.";
    disclaimer_.drawString(disclaimer, 50, ofGetWindowHeight() - 50);
}

// Draws background lines
void HandwritingAnalyzer::drawBackgroundLines() {
    background_lines_.setStrokeWidth(1);
    background_lines_.setStrokeColor(ofColor(179, 236, 255));
    background_lines_.draw();
}

// Draws cursor wherever the pen is
void HandwritingAnalyzer::drawCursor() {
    ofSetColor(170, 201, 224);
    pen_cursor_.draw(ofxTablet::tabletData.abs_screen[0], ofxTablet::tabletData.abs_screen[1] - kPenImageSize, kPenImageSize, kPenImageSize);
    
}

// Draws handwriting path to screen with set width and color
void HandwritingAnalyzer::drawPaths() {
    paths_.setStrokeWidth(2);
    paths_.setStrokeColor(ofColor(255, 255, 255));
    paths_.draw();
    
}

// Reads data from tablet once data is received and updates drawing state flags
void HandwritingAnalyzer::tabletMoved(TabletData &data) {
    curr_pressure_ = data.pressure * kPressureFactor;

    // Change drawing flags based on pressure
    if (curr_pressure_ >= kPressureThreshold) {
        if (!isDrawing_) {
            wasDrawing_ = false;
        } else {
            wasDrawing_ = true;
        }
        isDrawing_ = true;
        
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
    } else if (isDrawing_) {                    // still drawing
        paths_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.newSubPath(); //?
        strokes_.AddPoint(ofPoint(data.abs_screen[0], data.abs_screen[1]), curr_pressure_);
    } else if (wasDrawing_ && !isDrawing_) {    // just stopped drawing
        strokes_.EndStroke();
    }
}

// 'D' Changes state when user is done
// 'C' Clears strokes when user wants to start over
void HandwritingAnalyzer::keyPressed(int key){
    int upper_key = toupper(key);
    
    // Write state key presses
    if (curr_state_ == WRITE) {
        if (upper_key == 'D') {
            // Done: analyse strokes, check for doneness, change states
            strokes_.Analyze(classifier_.GetFactors());
            classifier_.Classify(quote_);
            
            // Print out data for testing
            std::cout << "Letter size: " << classifier_.GetFactors().size.data << std::endl;
            std::cout << "Left Margin: " << classifier_.GetFactors().left_margin.data << std::endl;
            std::cout << "Right Margin: " << classifier_.GetFactors().right_margin.data << std::endl;
            std::cout << "Number of strokes: " << strokes_.GetNumStrokes() << std::endl;
            std::cout << "Average speed: " << classifier_.GetFactors().speed.data << std::endl;
            std::cout << "Average pressure: " << classifier_.GetFactors().pressure.data << std::endl;
            std::cout << "Connectedness: " << classifier_.GetFactors().connectedness.data << std::endl;
            std::cout << std::endl;
            
            if (strokes_.GetNumStrokes() < quote_.GetNumWords()) {
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
