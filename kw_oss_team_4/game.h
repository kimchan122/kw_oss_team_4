#pragma comment(lib,"user32.lib")
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include<deque>

int main(int sw);
void main_difficulty();
void selectmode(int dif);

void main_makers();

void practice(int dif);

void musicstart();
void musicstop();
void pmusicstart();
void pmusicstop();
void sucsound();
void failsound();
void getsound();

void game_centre(int dif);
void midres(int c);
void result(int c);
void main_story(int dif);

int main_game_1(int dif, int pr);
int main_game_2(int dif, int pr);
int main_game_3(int dif, int pr);
int main_game_5(int dif, int pr);
int main_game_6(int dif, int pr);
int main_game_7(int dif, int pr);
int main_game_8(int dif, int pr);
int main_game_9(int dif, int pr);
void manclick();
void cpuclicksound();