#ifndef _BALL // if this class hasn't been defined, the program can define it
#define _BALL // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
class Ball {

public: // place public functions or variables declarations here

    // methods, equivalent to specific functions of your class objects
    void setup(string _id, int _size);   // setup method, use this to setup your object's initial state
    void update(int x, int y);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing

    // variables
    string id;
    ofImage brushImage;
    bool visible;

    Ball();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value

private: // place private functions or variables declarations here

    ofVec2f pos;

    int brushImageX;
    int brushImageY;

    uint64_t lastMoved;

    int size;




}; // don't forget the semicolon!
#endif