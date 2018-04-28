#pragma once

#include "ofMain.h"
#include "ofxTablet.h"
#include "strokes.h"
#include "classifier.h"
#include "factors.h"

namespace handwritinganalysis {

enum AnalysisState {
    WRITE,  // User is writing, only change states when strokes has more than a certain number of lines
    DISPLAY // Display personality to screen
};

class HandwritingAnalyzer : public ofBaseApp {
private:
    Classifier classifier_;
    Strokes strokes_;
    AnalysisState curr_state_ = WRITE;
    bool print_not_done_ = false;
    
    ofPath paths_;
    float curr_pressure_ = 0;
    
    // flags to keep track of drawing state
    bool isDrawing_ = false;
    bool wasDrawing_ = false;
    
    // stores background lines
    ofPath background_lines_; 
    
    ofImage pen_cursor_;
    ofTrueTypeFont write_text_;
    ofTrueTypeFont display_text_;
    ofTrueTypeFont disclaimer_;

    /* map of ofPath to float
     ofPath keeps track of every move and associates a pressure to it
    std::unordered_map<float, ofPath> pressure_paths_;
    ofPath curr_path_; */
    
public:
    void setup();
    void update();
    void draw();

    void drawDisplayState();
    void drawWriteState();
    void drawBackgroundLines();
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
}
