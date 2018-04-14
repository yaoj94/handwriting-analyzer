#include "ofApp.h"
#include "ofxTablet.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isDrawing_ = false;
    wasDrawing_ = false;
    
    paths_.setFilled(false);
    
    for (int i = 300; i < 1600; i += 100) {
        ofPolyline line;
        line.addVertex(ofPoint(0, i));
        line.addVertex(ofPoint(2560, i));
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
    pen_pressure_ = data.pressure * 50;

    ofApp::drawPaths();
    ofApp::drawCursor(data);
    
}

// get data as soon as it comes in
void ofApp::tabletMoved(TabletData &data) {
    if (!wasDrawing_ && isDrawing_) {
        paths_.moveTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
    }
    else if (isDrawing_) {
        paths_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        currStroke_.lineTo(ofPoint(data.abs_screen[0], data.abs_screen[1]));
        paths_.newSubPath(); //?
    }
    else if (wasDrawing_ && !isDrawing_) {
        strokes_.push_back(currStroke_);
        currStroke_.clear();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key);
    
    if (upper_key == 'D') {
        //done
    }
    if (upper_key == 'C') {
        // clear paths
        strokes_.clear();
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
    if (pen_pressure_ >= 5) {
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
    ofDrawCircle(data.abs_screen[0], data.abs_screen[1], 2);

}

void ofApp::drawPaths() {
    paths_.setStrokeWidth(2);
    paths_.setStrokeColor(ofColor(255, 255, 255));
    paths_.draw();
}

float ofApp::strokeWidthFromPressure() {
    if (pen_pressure_ >= 75) {
        return 7;
    } else if (pen_pressure_ <= 5) {
        return 0.5;
    } else {
        return pen_pressure_/20;
    }
}
