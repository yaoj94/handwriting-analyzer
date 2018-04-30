#pragma once

#include "ofMain.h"
#include "ofxTablet.h"
#include "strokes.h"
#include "classifier.h"
#include "factors.h"
#include "quote.h"
#include "ofxAVString.h"

namespace handwritinganalysis {
    
enum AnalysisState {
    WRITE,  // Collect strokes data
    DISPLAY // Display personalities to screen
};

class HandwritingAnalyzer : public ofBaseApp {
private:
    // Analyzer constants
    const int kPenImageSize = 45;
    const int kAttributeUpdatePeriod = 3000;
    const int kPressureFactor = 100;
    const int kPressureThreshold = 5;
    
    // Analyzer objects
    Quote quote_;
    Classifier classifier_;
    Strokes strokes_;
    
    // Keeps track of analysis state
    AnalysisState curr_state_ = WRITE;
    bool print_not_done_ = false;
    
    // Keep track of paths to print to screen
    ofPath paths_;
    float curr_pressure_ = 0;
    
    // flags to keep track of drawing state
    bool isDrawing_ = false;
    bool wasDrawing_ = false;
    
    // stores background lines
    ofPath background_lines_; 
    
    // store fonts
    ofImage pen_cursor_;
    ofTrueTypeFont write_text_;
    ofTrueTypeFont display_text_;
    ofTrueTypeFont disclaimer_;
    ofTrueTypeFont attribute_text_;
    ofxAVString avs_;
    
    // update attribute variables
    uint64_t last_update_time_ = 0;
    int factor_index_ = 0;
    
public:
    // Set up window, paths, and tablet
    void setup();
    
    // Update which factor gets printed to screen during DISPLAY state
    void update();
    
    // Draws write state and display state
    void draw();
    
    // Draws instructions, quote, and paths to screen
    void drawWriteState();
    
    // Draws attributes and disclaimer to screen
    void drawDisplayState();
    
    // Draws background lines
    void drawBackgroundLines();
    
    // Draws cursor wherever the pen is
    void drawCursor();
    
    // Draws handwriting path to screen with set width and color
    void drawPaths();
    
    // Reads data from tablet once data is received and updates drawing state flags
    void tabletMoved(TabletData &data);
    
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
