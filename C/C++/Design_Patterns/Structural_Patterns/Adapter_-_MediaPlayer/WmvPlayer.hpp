#ifndef WMVPLAYER_H
#define WMVPLAYER_H
#include <iostream>

using namespace std;

class WmvPlayer {
  public:
    void playWmv(string name) {
        cout << "Playing wmv file: " << name << endl;
    }
};

#endif