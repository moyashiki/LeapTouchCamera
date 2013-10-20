#include "testApp.h"

/* Note on OS X, you must have this in the Run Script Build Phase of your project. 
where the first path ../../../addons/ofxLeapMotion/ is the path to the ofxLeapMotion addon. 

cp -f ../../../addons/ofxLeapMotion/libs/lib/osx/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/libLeap.dylib"; install_name_tool -change ./libLeap.dylib @executable_path/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";

   If you don't have this you'll see an error in the console: dyld: Library not loaded: @loader_path/libLeap.dylib
*/

//--------------------------------------------------------------
void testApp::setup()
{
    //window size
    ofSetWindowShape(SCREEN_WIDTH ,SCREEN_HEIGHT);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
	leap.open();
	leap.setupGestures();   // we enable our gesture detection here
    // Camera Initialize
    // Mac
    // 0:Facetime
    camera.setDeviceID(1);
    camera.initGrabber(SCREEN_WIDTH ,SCREEN_HEIGHT);
    camera.setVerbose(true);
    // Sound
    sound.loadSound("inazuma_ikimasu.wav");
    sound.setMultiPlay(true);
    shutter.loadSound("shutter.mp3");
    complete.loadSound("complete.wav");
    brush = false;
    fingersize = 0;
    // image
    screenimage.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, OF_IMAGE_COLOR);
}


//--------------------------------------------------------------
void testApp::update()
{
    
	leap.updateGestures();  // check for gesture updates
    // 描画モード on/off
    if(leap.iGestures == 10 && !paintmode){
        paintmode = true;
        // 撮影音
#ifdef DEBUG
        sound.play();
#else
        shutter.play();
#endif
    } else if(leap.iGestures == 9 && paintmode){
        // 音声再生
        complete.play();
        fingers.clear();
        // 画像保存
        screenimage.grabScreen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        screenimage.saveImage("/Users/moyashiki/of_v0.8.0/apps/myApps/example-gestures/public/"+ofGetTimestampString()+".png");
        paintmode = false;
        
        system("sips -Z 640 -s formatOptions 50 /Users/moyashiki/of_v0.8.0/apps/myApps/example-gestures/public/*.png");
        
    }
    
    // ブラシ on/off
    if(paintmode && !brush && leap.iGestures == 3) {
        brush  = true;
    } else if (paintmode && brush && leap.iGestures == 4) {
        brush  = false;
    }
    
    // 手の情報を読み取り
    simpleHands = leap.getSimpleHands();
    if(simpleHands.size() > 0)
    fingersize = simpleHands[0].fingers.size();
    
    if(paintmode){

        if( leap.isFrameNew() && simpleHands.size() ){
            // mapping
            leap.setMappingX(-200, 200, 0, ofGetWidth());
            leap.setMappingY(90, 490, -ofGetHeight()/2 - 500, ofGetHeight()/2);
            
            for(int i = 0; i < simpleHands.size(); i++){
                for(int j = 0; j < simpleHands[i].fingers.size(); j++){

                    printf("current pos : %f %f\n",cursor_x,cursor_y);
                    
                    if(simpleHands[0].fingers.size() > 1){
                        fingers.push_back(simpleHands[0].fingers[0].pos);
                    }
                }
            }
        }
    } else {
        camera.update();
    }
    // cursor
    if(simpleHands.size() > 0 ){
        if(simpleHands[0].fingers.size() > 0){
            cursor_x = simpleHands[0].fingers[0].pos.x;
            cursor_y = simpleHands[0].fingers[0].pos.y;
        }
    }

    leap.markFrameAsOld();	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.

}

//--------------------------------------------------------------
void testApp::draw()
{
    camera.draw(0, 0);
    
    
    string msg;
    msg = gestureMessage(leap.iGestures);
    
    if(fingersize == 2) {
        //ofLine(cursor_x, cursor_y, 0, 0);
    }
    
    for(int i=0;i<fingers.size();++i){
        ofCircle(fingers[i].x, -fingers[i].y, 7);
//        ofCircle(-fingers[i].x, fingers[i].y, 7);
    }
    if(paintmode) {
        ofRect(cursor_x, -cursor_y, 10, 10);
//        ofRect(-cursor_x, cursor_y, 10, 10);
    }
    // ofDrawBitmapString(msg, 20, 20);  // let's draw our message to the screen

}

string testApp::gestureMessage(int gesturetype) {
    string msg;
    
    /* Leap iGesture Key
     --------------------------------
     1 = Screen Tap
     2 = Key Tap
     3 = Swipe Right
     4 = Swipe Left
     5 = Swipe Down
     6 = Swipe Up
     7 = Swipe Forward
     8 = Swipe Backward (towards yourself)
     9 = Circle Left (counter-clockwise)
     10 = Circle Right (clockwise)
     --------------------------------
     */

    switch (gesturetype)
    {
        case 1:
            msg = "Screen Tap";
            break;
            
        case 2:
            msg = "Key Tap";
            break;
            
        case 3:
            msg = "Swipe Right";
            break;
            
        case 4:
            msg = "Swipe Left";
            break;
            
        case 5:
            msg = "Swipe Down";
            break;
            
        case 6:
            msg = "Swipe Up";
            break;
            
        case 7:
            msg = "Swipe Forward";
            break;
            
        case 8:
            msg = "Swipe Backwards";
            break;
            
        case 9:
            msg = "Circle Left";
            break;
            
        case 10:
            msg = "Circle Right";
            break;
            
        default:
            msg = "Waiting for hand movement...";
            break;
    }
    return msg;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'x')
        ofToggleFullscreen();
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void testApp::exit()
{
    leap.close();  // let's close down Leap and kill the controller
}
