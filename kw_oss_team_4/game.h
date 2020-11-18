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

void musicstart();
void musicstop();

void game_centre(int dif);

void main_game_1(int dif);
void main_game_2(int dif);
void main_game_3(int dif);
void main_game_5(int dif);