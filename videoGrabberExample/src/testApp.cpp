#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(30);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth,camHeight);
	
//	videoInverted 	= new unsigned char[camWidth*camHeight*3];
//	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
//	ofSetVerticalSync(true);
	
	
	vidBuffer.setSize(30 * 60);
	ofxSharedVideoBuffer videoBuffer(&vidBuffer);
	vidBufferPlayer.loadVideoBuffer(videoBuffer);
	
	vidBufferPlayer.start();
	vidBuffer.setBufferType(OFX_VIDEO_BUFFER_CIRCULAR);
	
	ofSetFullscreen(true);
	
	imagesIdx = 0;
	
	for (int i = 0; i < IMAGES_SIZE; i++) {
		images.push_back(new ofxSharedVideoFrame(new ofImage()));
	}
						 
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(0, 0, 0);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
//		int totalPixels = camWidth*camHeight*3;
//		unsigned char * pixels = vidGrabber.getPixels();
//		for (int i = 0; i < totalPixels; i++){
//			videoInverted[i] = 255 - pixels[i];
//		}
//		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
		
		ofxSharedVideoFrame* frame = images[imagesIdx++];
		(*frame)->setFromPixels(vidGrabber.getPixelsRef());
		vidBuffer.bufferFrame(*frame);
		
		if (imagesIdx == IMAGES_SIZE) {
			imagesIdx = 0;
		}
	}
	
	vidBuffer.update();
	vidBufferPlayer.update();
	

}

//--------------------------------------------------------------
void testApp::draw(){
	ofHideCursor();
	
	ofSetHexColor(0xffffff);
//	vidGrabber.draw(20,20);
//	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	
	int x = 20;
	int y = 20;
	
//	vidBufferPlayer.draw(0,0, camWidth, camHeight);
//	vidBufferPlayer.draw(0,0, 1024, 768);
	vidBufferPlayer.draw(0,0, 1280, 720);
	
	//
//	
//	if(!vidBuffer.isLoading()) {
//		float p = vidBuffer.getPercentFull();
//		ofFill();
//		ofSetColor(255,255,0,127);
//		ofRect(x,y+camHeight-5,camWidth*p,5);
//	}
//	
//	if (vidBufferPlayer.getSize() > 0) {
//	{
//		ofPushStyle();
//		float ff = vidBufferPlayer.getFrame() / vidBufferPlayer.getSize();
//		ofSetRectMode(OF_RECTMODE_CENTER);
//		ofSetColor(0,255,0);
//		ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
//		ofPopStyle();
//	}
//	
//	{
//		ofPushStyle();
//		float ff = vidBufferPlayer.getLoopPointStart() / vidBufferPlayer.getSize();
//		ofSetRectMode(OF_RECTMODE_CENTER);
//		ofSetColor(0,0,255);
//		ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
//		ofPopStyle();
//	}
//	
//	{
//		ofPushStyle();
//		float ff = vidBufferPlayer.getLoopPointEnd() / vidBufferPlayer.getSize();
//		ofSetRectMode(OF_RECTMODE_CENTER);
//		ofSetColor(0,0,255);
//		ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
//		ofPopStyle();
//	}
//	}
//	
//	
//	ofSetColor(255);
//	// draw some stats
//	string stats = vidBufferPlayer.toString();
//	ofDrawBitmapString(stats, x + 20, y + 20);
//	
	
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
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
