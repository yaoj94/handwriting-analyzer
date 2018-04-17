#pragma once

#include "ofMain.h"
#include "ofxTablet.h"
#include "strokes.h"

enum AnalyzeState {
    WRITE,
    DISPLAY
};

class ofApp : public ofBaseApp{
private:
    Strokes strokes_;
    
    bool isDrawing_;
    bool wasDrawing_;
    ofPath paths_;
    float curr_pressure_;
    
    /* map of ofPath to float
     ofPath keeps track of every move and associates a pressure to it */
    std::unordered_map<float, ofPath> pressure_paths_;
    ofPath curr_path_;
    
    // background lines
    std::vector<ofPolyline> lines_;
    
public:
    void setup();
    void update();
    void draw();

    void tabletMoved(TabletData &data);  // for receiving tablet events directly

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
    
    void drawBackground();
    void drawCursor(TabletData &data);
    void drawPaths();
    float strokeWidthFromPressure(const float& pressure);
    
};
