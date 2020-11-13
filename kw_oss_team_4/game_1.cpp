#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;
using namespace sf;

struct TILE
{
    Sprite spTile;
    FloatRect TileRect; //타일 경계
    int HitNum=1; //깨지는 횟수
};

void main_game_1()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Arkanoid");
    window.setFramerateLimit(60); // 60fps

    sf::Texture txBack, txPlayer, txTile1, txTile2, txBall; // 
    sf::SoundBuffer sbTile, sbPlayer; //사운드 버퍼

    txBack.loadFromFile("img/game1/background.jpg"); // 
    txPlayer.loadFromFile("img/game1/paddle.png"); // 
    txBall.loadFromFile("img/game1/ball.png");
    txTile1.loadFromFile("img/game1/block01.png");
    txTile2.loadFromFile("img/game1/block02.png");
    sbTile.loadFromFile("sound/game1/tilesound.wav");
    sbPlayer.loadFromFile("sound/game1/playersound.wav");

    sf::Sprite spBack, spPlayer, spBall; // 
    Sound soundTile, soundPlayer;
    soundTile.setBuffer(sbTile);
    soundPlayer.setBuffer(sbPlayer);

    TILE Tile[40];

    spBack.setTexture(txBack); //
    spPlayer.setTexture(txPlayer);
    spBall.setTexture(txBall);

    float ballX = 300;
    float ballY = 300;
    float powerX = 5;
    float powerY = 5;
    int powerDir = 1; //-1 : left, 0 : 원래방향, 1 : right

    /// set double tile 
    srand((unsigned int)time(NULL));
    int rand1[10];

    //무작위 타일에 doouble 
    for (int i = 0; i < 10; i++)
    {
        rand1[i] = rand() % 40;
        for (int j = 0; j < i; j++)
        {
            if (rand1[j] == rand1[i]) //중복 제거
            {
                rand1[j] = rand() % 40;
                i--;
                break;
            }
        }
        Tile[rand1[i]].HitNum = 2;
    }/// set double tile

    for (int i = 0; i < 40; i++)
    {
        if (Tile[i].HitNum == 1)
            Tile[i].spTile.setTexture(txTile1);
        else
            Tile[i].spTile.setTexture(txTile2);
        Tile[i].spTile.setPosition((float)250 + (i % 8) * 60, (float)120 + (i / 8) * 30);
        Tile[i].TileRect = Tile[i].spTile.getGlobalBounds(); //타일 경계 지정
    }

    spPlayer.setPosition(300, 700);

    while (window.isOpen())
    {
        sf::Event event;
        FloatRect playerRect = spPlayer.getGlobalBounds();
        FloatRect BallRect = spBall.getGlobalBounds();

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
        if (spPlayer.getPosition().x < 0) { // 유저 왼쪽 밖으로 나가지 않게
            spPlayer.setPosition(0, spPlayer.getPosition().y);
        }
        else if (spPlayer.getPosition().x > 924) { // 오른쪽 밖으로 나가지 않게
            spPlayer.setPosition(924, spPlayer.getPosition().y);
        }
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
            soundPlayer.play();
        }

        for(int i=0; i<40; i++)
        {
            if (Tile[i].TileRect.contains(spBall.getPosition())) //공과 타일 충돌하면
            {
                if (BallRect.top - Tile[i].TileRect.top < 30 && BallRect.top - Tile[i].TileRect.top > 0) //타일 옆면을 충돌
                    powerX = -powerX;
                else if (BallRect.top - Tile[i].TileRect.top<=0) //타일 윗면을 충돌
                    powerY = -powerY;
                else if (BallRect.top - Tile[i].TileRect.top >= 30) //타일 밑면을 충돌
                    powerY = -powerY;

                if (Tile[i].HitNum == 1)
                {
                    Tile[i].spTile.setPosition(-100, 0);
                    Tile[i].TileRect = Tile[i].spTile.getGlobalBounds();
                }
                else
                {
                    Tile[i].HitNum--;
                    Tile[i].spTile.setTexture(txTile1);
                }
                soundTile.play();
            }
        }

        window.draw(spBack); // 배경
        window.draw(spBall);
        for (int i = 0; i < 40; i++)
            window.draw(Tile[i].spTile); //타일
        window.draw(spPlayer);//플레이어
        window.display(); // 표시
    }
}