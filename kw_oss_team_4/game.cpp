#include "game.h"

using namespace std;
using namespace sf;

sf::SoundBuffer mainbgm;
sf::Sound mainsound;

void musicstart() {
    mainbgm.loadFromFile("sound/main/SellBuyMusic_guitarandbeat.wav");
    mainsound.setBuffer(mainbgm);
    mainsound.play();
}
void musicstop() {

    mainsound.stop();
}