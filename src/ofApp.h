#pragma once

#include "ofMain.h"
#include "ofxMQTT.h"
#include "Ball.h"


class ofApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();

	//void collision(int x, int y);
	void move(string player, int x, int y);


	void keyPressed(int key);
	void mouseMoved(int x, int y);
	void onOnline();
	void onOffline();
	void onMessage(ofxMQTTMessage &msg);
	void exit();
	
	ofShader shader;

	ofImage backgroundImage;
	//ofImage foregroundImage;
	
	
	ofFbo maskFbo;
	ofFbo fbo;

	//Ball newBall;

	vector<Ball> balls;

	ofxMQTT client;

	uint64_t lastRemoved;
};
