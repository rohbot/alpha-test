#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    shader.load("shadersGL3/shader");

    backgroundImage.load("reveal.png");
    //foregroundImage.load("B.jpg");

    //ball.setup(150);


    int width = backgroundImage.getWidth();
    int height = backgroundImage.getHeight();

    maskFbo.allocate(width, height);
    fbo.allocate(width, height);

    // Clear the FBO's
    // otherwise it will bring some junk with it from the memory
    maskFbo.begin();
    ofClear(0, 0, 0, 255);
    maskFbo.end();

    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    client.begin("localhost", 1883);
    client.connect("openframeworks");

    ofAddListener(client.onOnline, this, &ofApp::onOnline);
    ofAddListener(client.onOffline, this, &ofApp::onOffline);
    ofAddListener(client.onMessage, this, &ofApp::onMessage);

    lastRemoved = ofGetElapsedTimeMillis();

}

void ofApp::onOnline() {
    ofLog() << "online";

    client.subscribe("blobs");
}

void ofApp::onOffline() {
    ofLog() << "offline";
}

void ofApp::onMessage(ofxMQTTMessage &msg) {
    ofLog() << "message: " << msg.topic << " - " << msg.payload;
    vector<string> tokens = ofSplitString(msg.payload, ",", true);
    if (tokens.size() == 3) {
        string id = tokens[0];
        int x = ofToInt(tokens[1]);
        int y = ofToInt(tokens[2]);

        move(id, x, y);
        //ofLog() << id << x << y;
    }

    // x = ofRandomWidth();
    // y = ofRandomHeight();

}

void ofApp::exit() {
    client.disconnect();
}

bool checkDead(Ball &b) {
    return !b.visible;
}



//--------------------------------------------------------------
void ofApp::update() {
    client.update();

    if(ofGetElapsedTimeMillis() - lastRemoved > 10000){
        ofRemove(balls, checkDead);
        ofLog() << "Removing dead balls: " << balls.size();
        
        lastRemoved = ofGetElapsedTimeMillis();
    }
}


//--------------------------------------------------------------
void ofApp::draw() {

    ofSetColor(255);

    //----------------------------------------------------------
    // this is our alpha mask which we draw into.
    maskFbo.begin();
    ofClear(0, 0, 0, 0);

    for (int i = 0; i < balls.size(); i++) {
        balls[i].draw();
    }

    maskFbo.end();

    //----------------------------------------------------------
    // HERE the shader-masking happends
    fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);

    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", maskFbo.getTexture(), 1 );

    backgroundImage.draw(0, 0);
    // reveal1.draw(100,100, 100, 100);
    // reveal2.draw(500,400, 100, 100);
    // reveal3.draw(800,600, 100, 100);

    shader.end();
    fbo.end();

    //----------------------------------------------------------
    // FIRST draw the background image
    ofBackground(51);
    //foregroundImage.draw(0, 0);
    // THEN draw the masked fbo on top
    fbo.draw(0, 0);

    //----------------------------------------------------------
    // ofDrawBitmapString("Drag the Mouse to draw", 15, 15);
    // ofDrawBitmapString("Press spacebar to clear", 15, 30);
}

// void ofApp::collision(int x, int y){

// }

void ofApp::move(string playerId, int x, int y) {
    bool found = false;
    for (int i = 0; i < balls.size(); i++) {
        ofLog() << "ball:" << balls[i].id ;
        if (balls[i].id == playerId) {
            found = true;
            balls[i].update(x, y);
        }
    }

    if (!found) {
        Ball newBall;
        newBall.setup(playerId, 150);
        newBall.update(x, y);
        balls.push_back(newBall);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    move("mouse", x, y);
}


