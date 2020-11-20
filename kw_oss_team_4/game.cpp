#include "game.h"

using namespace std;
using namespace sf;

sf::SoundBuffer mainbgm;
sf::Sound mainsound;
sf::SoundBuffer practicebgm;
sf::Sound psound;
sf::SoundBuffer failedbgm;
sf::Sound failed;
sf::SoundBuffer tmclick;
sf::Sound mclick;
sf::SoundBuffer tcpuclick;
sf::Sound cpuclick;

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
void failsound() {
    //CC0 1.0 Universal
    //Short jingles by Kenney Vleugels(www.kenney.nl)
    failedbgm.loadFromFile("sound/main/jingles.wav");
    failed.setBuffer(failedbgm);
    failed.play();
}
void manclick() {
    tmclick.loadFromFile("sound/main/manclick.wav");
    mclick.setBuffer(tmclick);
    mclick.play();
}
void cpuclicksound() {
    tcpuclick.loadFromFile("sound/main/cpuclick.wav");
    cpuclick.setBuffer(tcpuclick);
    cpuclick.play();
}