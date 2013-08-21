#pragma once

#include "ofMain.h"
#include "ofxVideoBufferPlayer.h"
#include "ofxVideoBuffer.h"

#define IMAGES_SIZE 1000

class testApp : public ofBaseApp{
	
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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
	
    ofxVideoBuffer vidBuffer;
    ofxVideoBufferPlayer vidBufferPlayer;
    
	vector<ofxSharedVideoFrame*> images;
	int imagesIdx;
	
    bool isRecording;
	
};
