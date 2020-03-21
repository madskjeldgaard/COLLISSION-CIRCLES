#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp {
private:
  void sendOsc();

public:
  void setup();
  void update();
  void draw();

  /*   void keyPressed(int key); */
  /*   void keyReleased(int key); */
  /*   void mouseMoved(int x, int y); */
  /*   void mouseDragged(int x, int y, int button); */
  /*   void mousePressed(int x, int y, int button); */
  /*   void mouseReleased(int x, int y, int button); */
  /*   void mouseEntered(int x, int y); */
  /*   void mouseExited(int x, int y); */
  /*   void windowResized(int w, int h); */
  /*   void dragEvent(ofDragInfo dragInfo); */
  /*   void gotMessage(ofMessage msg); */

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
  ofxOscMessage radiusMsg;
  ofxOscMessage collision;
  ofxOscMessage xMsg;
  ofxOscMessage yMsg;

  bool hasCollided;

  float width;
  float height;

  float seed1, seed2, seed3, seed4;
};
