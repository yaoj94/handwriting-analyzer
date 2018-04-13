#include "ofApp.h"
#include "ofxTablet.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(10,10,10);
    
    ofxTablet::start();
    
    // if you want to get data events, you can add a listener to ofxTablet::tabletEvent
    ofAddListener(ofxTablet::tabletEvent, this, &ofApp::tabletMoved);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    // you can also get global tablet data at any time
    TabletData& data = ofxTablet::tabletData;
    
    // draw point to screen
    float pressure = data.pressure * 50;
    if (pressure >= 5) {
        ofSetColor(0, 255, 153);
    } else {
        ofSetColor(255, 255, 255);
    }
    ofDrawCircle(data.abs_screen[0], data.abs_screen[1], 2);
    
}

// get data as soon as it comes in
void ofApp::tabletMoved(TabletData &data) {
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
