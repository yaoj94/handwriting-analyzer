#pragma once

#include "ofMain.h"
#include "ofxTablet.h"
#include "strokes.h"

enum AnalyzeState {
    WRITE,
    DISPLAY
};

class ofApp : public ofBaseApp {
private:
    Strokes strokes_;

    ofPath paths_;
    float curr_pressure_;
    
    // flags to keep track of drawing state
    bool isDrawing_;
    bool wasDrawing_;
    
    // stores background lines
    ofPath background_lines_; 
    
    ofImage pen_cursor_;
    ofTrueTypeFont text_;

    /* map of ofPath to float
     ofPath keeps track of every move and associates a pressure to it
    std::unordered_map<float, ofPath> pressure_paths_;
    ofPath curr_path_; */
    
public:
    void setup();
    void update();
    void draw();

    void drawBackground();
    void drawCursor();
    void drawPaths();
    float strokeWidthFromPressure(const float& pressure);
    
    void tabletMoved(TabletData &data); // Reads data from tablet once data is received
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
