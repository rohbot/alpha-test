#include "Ball.h"
Ball::Ball() {

}

void Ball::setup(string _id, int _size) {
    size = _size;
    visible = false;
    id = _id;
    brushImage.load("brush.png");
    lastMoved = ofGetElapsedTimeMillis();
    ofLog() << "New ball: " << id;
}

void Ball::update(int x, int y) {
    if (!visible) {
        visible = true;
    }
    pos.set(x,y);
    brushImageX = x - size * 0.5;
    brushImageY = y - size * 0.5;
    lastMoved = ofGetElapsedTimeMillis();

}

void Ball::draw() {
    if (visible) {
        brushImage.draw(brushImageX, brushImageY, size, size);
        if(ofGetElapsedTimeMillis() - lastMoved  > 3000){
            visible = false;
        }

    }


}