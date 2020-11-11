#include<iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;
using namespace sf;

void main_game_1()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Arkanoid");
    window.setFramerateLimit(60); // 60fps

    sf::Texture txBack, txPlayer, txTile, txBall; // 
    txBack.loadFromFile("img/game1/background.jpg"); // 
    txPlayer.loadFromFile("img/game1/paddle.png"); // 
    txBall.loadFromFile("img/game1/ball.png");
    txTile.loadFromFile("img/game1/block01.png");

    sf::Sprite spBack, spPlayer, spBall; // 
    Sprite spTile[40];
    FloatRect TileRect[40];

    spBack.setTexture(txBack); //
    spPlayer.setTexture(txPlayer);
    spBall.setTexture(txBall);

    float ballX = 300;
    float ballY = 300;
    float powerX = 5;
    float powerY = 5;
    int powerDir = 1; //-1 : left, 0 : 원래방향, 1 : right

    for (int i = 0; i < 40; i++)
    {
        spTile[i].setTexture(txTile);
        spTile[i].setPosition((float)250 + (i % 8) * 60, (float)120 + (i / 8) * 30);
        TileRect[i] = spTile[i].getGlobalBounds(); //타일 경계 지정
    }

    spPlayer.setPosition(300, 700);

    while (window.isOpen())
    {
        sf::Event event;
        FloatRect playerRect = spPlayer.getGlobalBounds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                if (event.KeyPressed == sf::Keyboard::Escape) {
                    window.close();
                    main();
                }
            }
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                main(); // 메인화면 창을 다시 열기
            }
        }
        if (ballX <= 0 || ballX >= 1024) //공이 프레임 밖으로 나가지 않게
            powerX = -powerX;
        if (ballY <= 0 || ballY >= 768)
            powerY = -powerY;
        powerDir = 0;
        if (Keyboard::isKeyPressed(Keyboard::Right)) //방향키 우
        {
            spPlayer.setPosition(spPlayer.getPosition().x + 8, 700);
            powerDir = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) //방향키 좌
        {
            spPlayer.setPosition(spPlayer.getPosition().x - 8, 700);
            powerDir = -1;
        }
        

        ballY += powerY; //공이 떨어지는 정도
        ballX += powerX;
        spBall.setPosition(ballX, ballY);

        if (playerRect.contains(spBall.getPosition())) //공과 플레이어 충돌하면
        {
            powerY = -powerY;
            float temp = spBall.getPosition().x - spPlayer.getPosition().x;
            powerX += temp / 100;
            powerY += temp / 100;

            if (powerDir==1 && powerX <= 0)
                powerX = -powerX;
            else if (powerDir==-1 && powerX >= 0)
                powerX = -powerX;
        }

        for(int i=0; i<40; i++)
        {
            if (TileRect[i].contains(spBall.getPosition())) //공과 타일 충돌하면
            {
                spTile[i].setPosition(-100, 0);
                TileRect[i] = spTile[i].getGlobalBounds();
                powerY = -powerY;
            }
        }

        window.draw(spBack); // 배경
        window.draw(spBall);
        for (int i = 0; i < 40; i++)
            window.draw(spTile[i]); //타일
        window.draw(spPlayer);//플레이어
        window.display(); // 표시
    }
}
