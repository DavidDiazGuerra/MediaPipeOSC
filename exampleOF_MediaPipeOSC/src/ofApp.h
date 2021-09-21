#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listening port
#define PORT 8000

// window size
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGH 768

// drawing area size
#define RECTANGLE_WIDHT WINDOW_WIDTH/2
#define RECTANGLE_HEIGH WINDOW_HEIGH/2

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		ofxOscReceiver oscReceiver;

		bool is_tracking_pose = false;
		bool is_tracking_face = false;
		bool is_tracking_left_hand = false;
		bool is_tracking_right_hand = false;
		ofPoint left_shoulder, right_shoulder,
			left_hip, right_hip,
			left_heel, right_heel,
			left_wrist, right_wrist,
			left_hand, right_hand,
			face_nose;
};
