#ifndef ADAPTER_H
#define ADAPTER_H
#include <iostream>
#include "iPlayable.hpp"
#include "Mp4Player.hpp"
#include "WmvPlayer.hpp"

using namespace std;

class Adapter:public iPlayable {
  public:
    void play(string type, string name) {
        if(type == "mp4") {
            mp4player->playMp4(name);
        } else if(type == "wmv") {
            wmvPlayer->playWmv(name);
        }
    }
    Mp4Player *mp4player = new Mp4Player();
    WmvPlayer *wmvPlayer = new WmvPlayer();
};

#endif