#include "game.h"

using namespace std;
using namespace sf;

sf::SoundBuffer mainbgm;
sf::Sound mainsound;
sf::SoundBuffer practicebgm;
sf::Sound psound;

void musicstart() {
    mainbgm.loadFromFile("sound/main/SellBuyMusic_guitarandbeat.wav");
    mainsound.setBuffer(mainbgm);
    mainsound.setLoop(true);
    mainsound.play();
}
void musicstop() {

    mainsound.stop();
}
void pmusicstart() {
    practicebgm.loadFromFile("sound/main/SellBuyMusic_jgfg.wav");
    psound.setBuffer(practicebgm);
    psound.setLoop(true);
    psound.play();
}
void pmusicstop() {
    psound.stop();
}