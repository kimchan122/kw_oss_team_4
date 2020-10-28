#include<iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

struct TileInfo
{
    bool isMine = false; // false이면 일반타일/숫자타일 , true이면 지뢰타일
    bool isSelected = false; //true이면 눌려진 타일
    int num = 0;
};

struct TileInfo tileInfo[16][16];

void setMine() //타일에 지뢰 배정
{
    //난수 생성
    srand((unsigned int)time(NULL));
    int rand1[40];
    int rand2[40];

    //무작위 타일에 지뢰 설정
    for (int i = 0; i < 40; i++)
    {
        rand1[i] = rand() % 16;
        rand2[i] = rand() % 16;
        for (int j = 0; j < i; j++)
        {
            if (rand1[j] == rand1[i] && rand2[j] == rand2[i]) //중복 제거
            {
                i--;
                break;
            }
        }
    }

    for (int i = 0; i < 40; i++)
    {
        tileInfo[rand1[i]][rand2[i]].isMine = true;
    }
}

void setNumber() // 지뢰 주변 타일에 숫자 배정
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (tileInfo[i][j].isMine == true) //지뢰 타일 주변 타일들의 num을 1씩 증가
            {
                if (i == 0) // [0,j]
                {
                    if (j == 0) // [0,0]
                    {
                        tileInfo[0][1].num++;
                        tileInfo[1][0].num++;
                        tileInfo[1][1].num++;
                    }
                    else if (j == 15) //[0,15]
                    {
                        tileInfo[1][15].num++;
                        tileInfo[1][14].num++;
                        tileInfo[0][14].num++;
                    }
                    else if (j > 0 && j < 15) // [0, 1~14]
                    {
                        tileInfo[i][j - 1].num++;
                        tileInfo[i + 1][j - 1].num++;
                        tileInfo[i + 1][j].num++;
                        tileInfo[i + 1][j + 1].num++;
                        tileInfo[i][j + 1].num++;
                    }
                }
                else if (i == 15) // [15, y]
                {
                    if (j == 0) // [15,0]
                    {
                        tileInfo[14][0].num++;
                        tileInfo[14][1].num++;
                        tileInfo[15][1].num++;
                    }
                    else if (j == 15)
                    {
                        tileInfo[14][15].num++;
                        tileInfo[14][14].num++;
                        tileInfo[15][14].num++;
                    }
                }
            }
            else if (i > 0 && i < 15) // [1~14, j]
            {
                if (j == 0) // [1~14, 0]
                {
                    tileInfo[i - 1][j].num++;
                    tileInfo[i - 1][j + 1].num++;
                    tileInfo[i][j + 1].num++;
                    tileInfo[i + 1][j + 1].num++;
                    tileInfo[i + 1][j].num++;
                }
                else if (j == 15) //[1~14, 15]
                {
                    tileInfo[i - 1][j].num++;
                    tileInfo[i - 1][j - 1].num++;
                    tileInfo[i][j - 1].num++;
                    tileInfo[i + 1][j - 1].num++;
                    tileInfo[i + 1][j].num++;
                }
                else if (j > 0 && j < 15)
                {
                    tileInfo[i - 1][j].num++;
                    tileInfo[i - 1][j - 1].num++;
                    tileInfo[i][j - 1].num++;
                    tileInfo[i + 1][j - 1].num++;
                    tileInfo[i + 1][j].num++;
                    tileInfo[i + 1][j + 1].num++;
                    tileInfo[i][j + 1].num++;
                    tileInfo[i - 1][j + 1].num++;
                }
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "MineSweeper");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tsmile; // 스마일 마크
    tsmile.loadFromFile("img/smile.png"); // tman에 이미지 로드
    sf::Sprite smile; // 객체 man을 생성
    smile.setTexture(tsmile); // 객체 man의 이미지를 tman의 이미지로 지정

    Texture tTile[16][16]; // 빈 타일

    Sprite Tile[16][16]; //16 x 16 게임판

    int FlagNum = 0; // 우클릭으로 체크한 플래그 갯수
    int SelectedTileNum = 0; //눌려진 타일 갯수
    int mouseX = 0; //클릭한 마우스 x좌표
    int mouseY = 0; //클릭한 마우스 y좌표

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            tTile[i][j].loadFromFile("img/tile.png"); // 빈 타일 로드
            Tile[i][j].setTexture(tTile[i][j]);
            Tile[i][j].setPosition((float)200 + 40 * i, (float)100 + 40 * j);
        }
    }

    setMine();
    setNumber();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //마우스 좌클릭 이벤트
                {
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;

                }
            }
        }

        window.clear();
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                window.draw(Tile[i][j]); // 타일 그리기
            }
        }

        smile.setPosition(500, 30); // 스마일 위치 설정
        window.draw(smile); // 스마일 그리기

        window.display(); // 표시
    }

    return 0;
}
