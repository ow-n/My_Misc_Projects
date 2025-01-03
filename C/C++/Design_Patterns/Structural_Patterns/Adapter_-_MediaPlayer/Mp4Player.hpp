#ifndef MP4PLAYER_H
#define MP4PLAYER_H
#include <iostream>

using namespace std;

class Mp4Player {
  public:
    void playMp4(string name) {
        cout << "Playing mp4 file: " << name << endl;
    }
};

#endif