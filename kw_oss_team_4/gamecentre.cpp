#include"game.h"

using namespace std;
using namespace sf;

void game_centre(int dif) {
	int cnt = 8;
	main_story(dif);
	midres(cnt);
	cnt-=main_game_1(dif,0);
	midres(cnt);/*
	cnt-=main_game_2(dif,0);
	midres(cnt);
	cnt -= main_game_3(dif,0);
	midres(cnt);
	cnt -= main_game_5(dif,0);
	midres(cnt);
	cnt -= main_game_6(dif, 0);
	midres(cnt);
	cnt -= main_game_7(dif, 0);
	midres(cnt);
	cnt -= main_game_8(dif, 0);
	midres(cnt);
	cnt -= main_game_9(dif, 0);
	midres(cnt);*/
	result(cnt);
}
void midres(int c) {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4");
	window.setFramerateLimit(60);

	sf::Texture tbackground;
	tbackground.loadFromFile("img/main/main.png");
	sf::Sprite background;
	background.setTexture(tbackground);

	sf::Font font;
	font.loadFromFile("font/BMJUA_ttf.ttf");
	sf::Text rest;
	rest.setFont(font);
	rest.setPosition(50 , 50);
	rest.setFillColor(sf::Color::White);
	rest.setCharacterSize(180);
	rest.setString("Game result");

	sf::Text res;
	
	res.setFont(font);
	res.setFillColor(sf::Color::Yellow);
	res.setCharacterSize(170);
	res.setString("o");
	for (int i = 0; i < c; i++) {
		getsound();
		window.draw(rest);
		for (int j = 0; j <= i; j++) {
			res.setPosition(130 * j, 200);
			window.draw(res);
		}
		window.display();
		sf::sleep(sf::seconds(0.3f));
	}
	sf::sleep(sf::seconds(2.0f));
}
void result(int c) {
	cout << "C : "<<c << endl;
	sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4_RESULT");
	window.setFramerateLimit(60);

	sf::Texture tbackground;
	tbackground.loadFromFile("img/main/res.png");
	sf::Sprite background;
	background.setTexture(tbackground);
	window.draw(background);

	sf::Font font;
	font.loadFromFile("font/BMJUA_ttf.ttf");
	sf::Text rest;
	rest.setFont(font);
	rest.setPosition(50, 50);
	rest.setFillColor(sf::Color::White);
	rest.setCharacterSize(180);
	rest.setString("Game result");

	sf::Text res;
	res.setFont(font);
	res.setFillColor(sf::Color::Yellow);
	res.setCharacterSize(170);
	res.setString("o");

	sf::Text restt;
	restt.setFont(font);
	restt.setPosition(450, 450);
	window.draw(rest);
	window.display();
	for (int i = 0; i < c; i++) {
		getsound();
		window.draw(background);
		window.draw(rest);
		for (int j = 0; j <= i; j++) {
			res.setPosition(130 * j, 200);
			window.draw(res);
		}
		window.display();
		sf::sleep(sf::seconds(0.15f));
	}
	sf::sleep(sf::seconds(1.0f));
	getsound();
	if (c >= 7) {
		for (int i = 0; i < c; i++) {
			window.draw(background);
			window.draw(rest);
			for (int j = 0; j <= i; j++) {
				res.setPosition(130 * j, 200);
				window.draw(res);
			}
		}
		restt.setFillColor(sf::Color::Yellow);
		restt.setCharacterSize(180);
		restt.setString("S");
		window.draw(restt);
		window.display();
	}
	else if (c == 5 || c == 6) {
		for (int i = 0; i < c; i++) {
			window.draw(background);
			window.draw(rest);
			for (int j = 0; j <= i; j++) {
				res.setPosition(130 * j, 200);
				window.draw(res);
			}
		}
		restt.setFillColor(sf::Color::Red);
		restt.setCharacterSize(180);
		restt.setString("A");
		window.draw(restt);
		window.display();
	}
	else if (c == 4 || c==3) {
		for (int i = 0; i < c; i++) {
			window.draw(background);
			window.draw(rest);
			for (int j = 0; j <= i; j++) {
				res.setPosition(130 * j, 200);
				window.draw(res);
			}
		}
		restt.setFillColor(sf::Color::Blue);
		restt.setCharacterSize(180);
		restt.setString("B");
		window.draw(restt);
		window.display();
	}
	else if (c == 2 || c==1) {
		for (int i = 0; i < c; i++) {
			window.draw(background);
			window.draw(rest);
			for (int j = 0; j <= i; j++) {
				res.setPosition(130 * j, 200);
				window.draw(res);
			}
		}
		restt.setFillColor(sf::Color::Green);
		restt.setCharacterSize(180);
		restt.setString("C");
		window.draw(restt);
		window.display();
	}
	else {
		window.draw(background);
		window.draw(rest);
		for (int i = 0; i < c; i++) {
			window.draw(background);
			window.draw(rest);
			for (int j = 0; j <= i; j++) {
				res.setPosition(130 * j, 200);
				window.draw(res);
			}
		}
		restt.setFillColor(sf::Color::Black);
		restt.setCharacterSize(180);
		restt.setString("D");
		window.draw(restt);
		window.display();
	}
	sf::sleep(sf::seconds(3.0f));
	window.close();
	main(1);
}