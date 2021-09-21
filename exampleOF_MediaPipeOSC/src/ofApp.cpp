#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("ofxMediaPipeOSC");
	ofSetFrameRate(60); // run at 60 fps
	ofSetBackgroundColor(54, 54, 54);
	ofSetVerticalSync(true);

	// listen on the given port
	ofLog() << "listening for osc messages on port " << PORT;
	oscReceiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){

	// check for waiting OSC messages
	while (oscReceiver.hasWaitingMessages()) {

		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);

		// check messages of interest
		if (m.getAddress() == "/mediapipe_osc_server/pose/tracking") {
			is_tracking_pose = m.getArgAsBool(0);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/11") {
			left_shoulder.x = m.getArgAsFloat(0);
			left_shoulder.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/12") {
			right_shoulder.x = m.getArgAsFloat(0);
			right_shoulder.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/23") {
			left_hip.x = m.getArgAsFloat(0);
			left_hip.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/24") {
			right_hip.x = m.getArgAsFloat(0);
			right_hip.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/29") {
			left_heel.x = m.getArgAsFloat(0);
			left_heel.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/30") {
			right_heel.x = m.getArgAsFloat(0);
			right_heel.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/15") {
			left_wrist.x = m.getArgAsFloat(0);
			left_wrist.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/pose/16") {
			right_wrist.x = m.getArgAsFloat(0);
			right_wrist.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/hands/left/tracking") {
			is_tracking_left_hand = m.getArgAsBool(0);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/hands/left/9") {
			left_hand.x = m.getArgAsFloat(0);
			left_hand.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/hands/right/tracking") {
			is_tracking_right_hand = m.getArgAsBool(0);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/hands/right/9") {
			right_hand.x = m.getArgAsFloat(0);
			right_hand.y = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/face/tracking") {
			is_tracking_face = m.getArgAsBool(0);
		}
		else if (m.getAddress() == "/mediapipe_osc_server/face/1") {
			face_nose.x = m.getArgAsFloat(0);
			face_nose.y = m.getArgAsFloat(1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 30);

	ofTranslate((WINDOW_WIDTH - RECTANGLE_WIDHT) / 2, (WINDOW_HEIGH - RECTANGLE_HEIGH) / 2);
	ofScale(RECTANGLE_WIDHT, RECTANGLE_HEIGH);

	ofNoFill();
	ofDrawRectangle(0, 0, 1, 1);

	if (is_tracking_pose) {
		ofDrawLine(left_shoulder.getMiddle(right_shoulder), left_hip.getMiddle(right_hip));
		ofDrawLine(left_shoulder.getMiddle(right_shoulder), left_wrist);
		ofDrawLine(left_shoulder.getMiddle(right_shoulder), right_wrist);
		ofDrawLine(left_hip.getMiddle(right_hip), left_heel);
		ofDrawLine(left_hip.getMiddle(right_hip), left_heel);
		ofDrawLine(left_hip.getMiddle(right_hip), right_heel);
	}

	ofFill();
	if (is_tracking_face) {
		ofDrawCircle(face_nose, face_nose.distance(left_shoulder.getMiddle(right_shoulder))/2);
	}
	if (is_tracking_left_hand) {
		ofSetColor(ofColor::red);
		ofDrawCircle(left_hand, left_hand.distance(left_wrist));
	}
	if (is_tracking_right_hand) {
		ofSetColor(ofColor::blue);
		ofDrawCircle(right_hand, right_hand.distance(right_wrist));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
