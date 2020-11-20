#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include<deque>

int main(int sw);
void main_difficulty();
void selectmode(int dif);

void practice(int dif);

void musicstart();
void musicstop();
void pmusicstart();
void pmusicstop();

void game_centre(int dif);

void main_game_1(int dif, int pr);
void main_game_2(int dif, int pr);
void main_game_3(int dif, int pr);
void main_game_5(int dif, int pr);