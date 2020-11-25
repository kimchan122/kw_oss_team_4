#include "game.h"

using namespace std;
using namespace sf;

sf::SoundBuffer mainbgm;
sf::Sound mainsound;
sf::SoundBuffer practicebgm;
sf::Sound psound;
sf::SoundBuffer sucbgm;
sf::Sound suc;
sf::SoundBuffer failedbgm;
sf::Sound failed;
sf::SoundBuffer tmclick;
sf::Sound mclick;
sf::SoundBuffer tcpuclick;
sf::Sound cpuclick;
sf::SoundBuffer tblop;
sf::Sound blop;

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
void sucsound() {
    //CC0 1.0 Universal made by DayDreamSound
    //https ://youtu.be/kfnh9QAfDgA
    sucbgm.loadFromFile("sound/main/suc.wav");
    suc.setBuffer(sucbgm);
    suc.play();
}
void failsound() {
    //CC0 1.0 Universal
    //Short jingles by Kenney Vleugels(www.kenney.nl)
    failedbgm.loadFromFile("sound/main/jingles.wav");
    failed.setBuffer(failedbgm);
    failed.play();
}
void sucsound2() {
    //CC0 1.0 Universal
    //Short jingles by Kenney Vleugels(www.kenney.nl)
}
void getsound() {
    //Thanks to, Mark DiAngelo
    //From : http://soundbible.com/2067-Blop.html
    //Distributor: 저작권 걱정없는 유튜브용 음원& 무료 효과음 서비스 ‘뮤팟’
    //https ://www.mewpot.com
    tblop.loadFromFile("sound/main/blop.wav");
    blop.setBuffer(tblop);
    blop.play();
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