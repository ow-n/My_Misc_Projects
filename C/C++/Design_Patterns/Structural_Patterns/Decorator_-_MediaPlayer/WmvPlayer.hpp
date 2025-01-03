#ifndef WMVPLAYER_H
#define WMVPLAYER_H
#include <iostream>

using namespace std;

// Horizantal Scroll Bar Decorator
class WmvPlayer: public Adapter {
  public:
    void playWmv(string name) {
        //Adapter::play(type, name);
        Adapter::play(name);
        cout << "Playing wmv file: " << name << endl;
    }
};

#endif