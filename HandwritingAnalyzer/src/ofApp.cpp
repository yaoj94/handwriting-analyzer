#include "ofApp.h"
#include "ofxTablet.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isDrawing_ = false;
    wasDrawing_ = false;
    
    paths_.setFilled(false);
    
    for (int i = 300; i < ofGetWindowHeight(); i += 100) {
        ofPolyline line;
        line.addVertex(ofPoint(0, i));
        line.addVertex(ofPoint(ofGetWindowWidth(), i));
        line.close();
        lines_.push_back(line);
    }
    
    ofxTablet::start();
    
    // if you want to get data events, you can add a listener to ofxTablet::tabletEvent
    ofAddListener(ofxTablet::tabletEvent, this, &ofApp::tabletMoved);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofApp::drawBackground();
    
    // you can also get global tablet data at any time
    TabletData& data = ofxTablet::tabletData;
    curr_pressure_ = data.pressure * 100;

    ofApp::drawPaths();
    //strokes_.drawStrokes();
    ofApp::drawCursor(data);
    
}

// get data as soon as it comes in
void ofApp::tabletMoved(TabletData &data) {
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
    
    if (!wasDrawing_ && isDrawing_) {           // just started drawing
        paths_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        //curr_path_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
    } else if (isDrawing_) {                    // still drawing
        //curr_path_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.newSubPath(); //?
        strokes_.addPoint(ofPoint(data.abs_screen[0], data.abs_screen[1]), curr_pressure_);
        //pressure_paths_.insert(make_pair(curr_pressure_, curr_path_));
        //curr_path_.clear();
        //curr_path_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
    } else if (wasDrawing_ && !isDrawing_) {    // just stopped drawing
        strokes_.endStroke();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key);
    
    if (upper_key == 'D') {
        //done
    }
    if (upper_key == 'C') {
        std::cout << "Number of strokes: " << strokes_.getLength() << std::endl;
        std::cout << "Average speed: " << strokes_.getAverageSpeed() << std::endl;
        std::cout << "Average pressure: " << strokes_.calculateAveragePressure() << std::endl;

        // clear paths
        strokes_.resetStrokes();
        paths_.clear();
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

void ofApp::drawBackground() {
    ofBackground(0, 0, 0);
    ofSetColor(179, 236, 255);
    for (auto line : lines_) {
        line.draw();
    }
}

void ofApp::drawCursor(TabletData &data) {
    ofSetColor(0, 255, 153);

    // draw point to screen
    ofDrawCircle(data.abs_screen[0], data.abs_screen[1], 2);

}

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

float ofApp::strokeWidthFromPressure(const float& pressure) {
    if (pressure >= 75) {
        return 7;
    } else if (pressure <= 5) {
        return 0.5;
    } else {
        return (pressure)/20;
    }
}
