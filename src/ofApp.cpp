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
  minRadius = ofGetScreenHeight() / 10;
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

  hasCollided = false;
}

//--------------------------------------------------------------
void ofApp::update() {
  auto time = ofGetElapsedTimef();
  auto distance = pos1.distance(pos2);
  width = ofGetScreenWidth();
  height = ofGetScreenHeight();

  // Impact detection
  if (distance <= (radius1 + radius2)) {
    // Change colors
    bgCol = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    col1.lerp(bgCol.invert(), 0.5);
    col2 = bgCol.getInverted();

    ofSetBackgroundColor(bgCol);

    // Collision message
    hasCollided = true;

  } else {
    hasCollided = false;
  }

  // Movements
  if ((pos1.x + radius1) <= width)
    pos1.x = ofClamp(pos1.x + (sin(time * 3 + ofRandom(-1, 1))) * 20, 0,
                     width - radius1);
  else
    pos1.x -= radius1;

  if ((pos1.y + radius1) <= height)
    pos1.y = ofClamp(pos1.y + (sin(ofRandom(time * 3 + ofRandom(-1, 1)))) * 20,
                     0, width - radius1);
  else
    pos1.y -= 1;

  if ((pos2.x + radius2) <= width)
    pos2.x = ofClamp(pos2.x + (sin(ofRandom(time * 3 + ofRandom(-1, 1)))) * 20,
                     0, width - radius2);
  else
    pos2.x -= 1;

  if ((pos2.y + radius2) <= height)
    pos2.y = ofClamp(pos2.y + (sin(time * 5) + ofRandom(-1, 1)) * 10, 0,
                     height - radius2);
  else
    pos2.y -= 1;

  // Update radii
  radius1 = ofClamp(radius1 + ofRandom(-1, 1), minRadius, maxRadius);
  radius2 = ofClamp(radius2 * sin(ofNoise(time)) * 2 + minRadius, minRadius,
                    maxRadius);

  // Send off osc bundle
  sendOsc();
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
void ofApp::sendOsc() {
  bundle.clear();
  string addRoot = "/of/circle";

  // Collision message
  collision.clear();
  collision.setAddress(addRoot + "/1/collision");
  collision.addBoolArg(hasCollided);
  bundle.addMessage(collision);

  // Radius
  radiusMsg.clear();
  radiusMsg.setAddress(addRoot + "/1/radius");
  radiusMsg.addFloatArg(radius1 / maxRadius);
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

  oscSender.sendBundle(bundle);
};
