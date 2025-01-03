#include <iostream>
#include "MediaPlayer.hpp"
#include "Mp4Player.hpp"
#include "WmvPlayer.hpp"

using namespace std;

int main() {
    // MediaPlayer *player = new MediaPlayer();
    // player->play("mp3", "far far away");
    // player->play("cd", "alone");
    // player->play("mp4", "beyond the horizon");
    // player->play("wmv", "mind me");

    iPlayable *iplayer = new MediaPlayer(
            new MediaPlayer(new Mp4Player(
            new WmvPlayer("far far away"))));
    return 0;
}
