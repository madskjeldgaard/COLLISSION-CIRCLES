#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  ofPoint pos1;
  ofPoint pos2;

  float radius1;
  float radius2;
  float minRadius;
  float maxRadius;

  ofColor bgCol;
  ofColor col1;
  ofColor col2;

  ofxOscSender oscSender;
  ofxOscSenderSettings oscSettings;

  ofxOscBundle bundle;
  ofxOscMessage m1;

  ofxOscMessage radiusMsg;
  ofxOscMessage collision;
  ofxOscMessage xMsg;
  ofxOscMessage yMsg;
};
