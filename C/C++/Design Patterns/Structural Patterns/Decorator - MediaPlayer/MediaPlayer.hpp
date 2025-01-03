#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <iostream>
#include "iPlayable.hpp"
#include "Adapter.hpp"

using namespace std;

// Windows
class MediaPlayer:public iPlayable {
  public:
    void play(string type, string name) override {
        if(type == "mp3") {
            iPlayable::play(name);
            cout << "Playing mp3 file: " << name << endl;
        } else if(type == "cd") {
            iPlayable::play(name);
            cout << "Playing CD: " << name << endl;
        } else if(type == "mp4") {
            //adapter->play(type, name);
            //mp4player->playMp4(name);
        } else if(type == "wmv") {
            //adapter->play(type, name);
            //wmvPlayer->playWmv(name);
        } else {
            cout << "Invalid media. Format not supported." << endl;
        }
    }
    //Adapter *adapter = new Adapter();
    //Mp4Player *mp4player = new Mp4Player();
    //WmvPlayer *wmvPlayer = new WmvPlayer();
};

#endif