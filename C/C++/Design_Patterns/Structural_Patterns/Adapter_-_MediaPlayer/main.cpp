#include <iostream>
#include "MediaPlayer.hpp"

using namespace std;

int main() {
    MediaPlayer *player = new MediaPlayer();
    player->play("mp3", "far far away");
    player->play("cd", "alone");
    player->play("mp4", "beyond the horizon");
    player->play("wmv", "mind me");
    return 0;
}
