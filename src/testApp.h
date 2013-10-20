#pragma once

#include "ofMain.h"
#include "ofxLeapMotion.h"

class testApp : public ofBaseApp{

  public:
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
 
    void setup();
    void update();
    void draw();
	
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    string gestureMessage(int gesturetype);
    
		
	ofxLeapMotion leap;
    ofVideoGrabber camera;
    ofSoundPlayer sound,shutter,complete;
    ofImage screenimage;
    bool paintmode;
    bool brush;
    float cursor_x,cursor_y;
    int fingersize;
    
    vector<ofxLeapMotionSimpleHand> simpleHands;
    vector<ofPoint> fingers;
};
