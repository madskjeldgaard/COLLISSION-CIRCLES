#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  ofEnableAlphaBlending();    // enable transparancy
  ofEnableAntiAliasing();     // enable anti-aliasing
  ofEnableSmoothing();        // enable line smooth
  ofSetCircleResolution(100); // make nicer circles

  ofSetFrameRate(60);      // limits framerate to 60 FPS
  ofSetVerticalSync(true); // sync with screen
  ofSetWindowTitle(ofToString(ofGetFrameRate()));

  // Constrain raidus of circles to these values
  minRadius = 10;
  maxRadius = ofGetScreenHeight() / 4;

  // init radii of circles
  radius1 = 250;
  radius2 = 250;

  // init position of circles
  pos1.set(ofGetScreenWidth() / 2 - radius1, ofGetScreenHeight() / 2);
  pos2.set(pos1.x + radius1 + radius2, pos1.y);

  // color setup
  bgCol = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
  col1.lerp(bgCol.invert(), 0.5);
  col2 = ofColor(0);

  // OSC setup
  oscSettings.host = "127.0.0.1";
  oscSettings.port = 1210;
  oscSettings.broadcast = true;

  oscSender.setup(oscSettings);

  m1.setAddress("/helloFromOF/");
  m1.addIntArg(666);
}

//--------------------------------------------------------------
void ofApp::update() {
  auto time = ofGetElapsedTimef();
  auto width = ofGetScreenWidth();
  auto height = ofGetScreenHeight();
  auto distance = pos1.distance(pos2);

  // OSC STUFF

  // Send OSC
  bundle.clear();
  string addRoot = "/of/circle";

  // Collision message
  collision.clear();
  collision.setAddress(addRoot + "/1/collision");
  collision.addBoolArg(false);
  bundle.addMessage(collision);

  // Radius
  radiusMsg.clear();
  radiusMsg.setAddress(addRoot + "/1/radius");
  radiusMsg.addFloatArg(radius1);
  bundle.addMessage(radiusMsg);

  // X pos (normalized)
  xMsg.clear();
  xMsg.setAddress(addRoot + "/1/x");
  xMsg.addFloatArg(pos1.x / width);
  bundle.addMessage(xMsg);

  // Y pos (normalized)
  yMsg.clear();
  yMsg.setAddress(addRoot + "/1/y");
  yMsg.addFloatArg(pos1.y / width);
  bundle.addMessage(yMsg);

  // Impact detection
  if (distance <= (radius1 + radius2)) {
    // Change colors
    bgCol = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    col1.lerp(bgCol.invert(), 0.5);
    col2 = bgCol.getInverted();

    ofSetBackgroundColor(bgCol);
    //
    // Collision message
    collision.clear();
    collision.setAddress(addRoot + "/1/collision");
    collision.addBoolArg(true);
    bundle.addMessage(collision);
  }

  oscSender.sendBundle(bundle);

  // Movements
  if ((pos1.x + radius1) <= width)
    pos1.x = ofClamp(pos1.x + (sin(time * 3 + ofRandom(-10, 10))) * 10, 0,
                     width - radius1);
  else
    pos1.x -= radius1;

  if ((pos1.y + radius1) <= height)
    pos1.y = ofClamp(pos1.y + (sin(time * 5) + ofRandom(-10, 10)) * 10, 0,
                     height - radius1);
  else
    pos1.y -= 1;

  if ((pos2.x + radius2) <= width)
    pos2.x = ofClamp(pos2.x + (cos(time * sin(pos1.x * 3))) * 10, 0,
                     width - radius2);
  else
    pos2.x -= 1;

  if ((pos2.y + radius2) <= height)
    pos2.y =
        ofClamp(pos2.y + (sin(time * ofRandom(2, -2))), 0, height - radius2);
  else
    pos2.y -= 1;

  /*   pos1.x = ofClamp(pos1.x, 0, width); */
  /*   pos2.x = ofClamp(pos2.x, 0, width); */

  /*   pos1.y = ofClamp(pos1.y, 0, height); */
  /* pos2.y = ofClamp(pos2.y, 0, height); */

  // Update radii
  radius1 = ofClamp(radius1 + ofRandom(-1, 1), minRadius, maxRadius);
  radius2 = ofClamp(radius2 * sin(ofNoise(time)) * 2 + minRadius, minRadius,
                    maxRadius);
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Circle 1
  ofSetColor(col1);
  ofDrawCircle(pos1, radius1);

  // Circle 2
  ofSetColor(col2);
  ofDrawCircle(pos2, radius2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
