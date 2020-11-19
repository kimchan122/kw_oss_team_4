#include "game.h"

using namespace std;
using namespace sf;

struct TileInfo
{
    bool isMine = false; // false이면 일반타일/숫자타일 , true이면 지뢰타일
    bool isSelected = false; //true이면 눌려진 타일
    bool isFlag = false;
    int num = 0;
};

int difficulty;
int difX = 1; //난이도 별 게임판 행
int difY = 1; //난이도 별 게임판 열

struct TileInfo tileInfo[16][16];
Texture tTile[16][16]; // 빈 타일
Texture Result[2];
Sprite Tile[16][16];

Texture tsmile;

int FlagNum = 0; // 우클릭으로 체크한 플래그 갯수
int SelectedTileNum = 0; //눌려진 타일 갯수
int FoundMineNum = 0; //플레이어가 찾은 지뢰수

int difSelectedTileNum; //난이도 별 선택된 타일개수
int difFoundMineNum; //난이도 별 총 지뢰 수


void setMine(int dif) //타일에 지뢰 배정
{
    //난수 생성
    srand((unsigned int)time(NULL));
    int minenum = 0;
    switch (dif) //난이도 별 지뢰개수 설정
    {
    case 1:
        minenum = 16; //1단계 지뢰수
        break;
    case 2:
        minenum = 28;//2단계 지뢰수
        break;
    case 3:
        minenum = 40;//3단계 지뢰수
        break;
    }
    int* rand1 = new int[minenum];
    int* rand2 = new int[minenum];

    //무작위 타일에 지뢰 설정
    for (int i = 0; i < minenum; i++)
    {
        rand1[i] = rand() % difX;
        rand2[i] = rand() % difY;
        for (int j = 0; j < i; j++)
        {
            if (rand1[j] == rand1[i] && rand2[j] == rand2[i]) //중복 제거
            {
                i--;
                break;
            }
        }
    }
    for (int i = 0; i < minenum; i++)
    {
        tileInfo[rand1[i]][rand2[i]].isMine = true;
        //Tile[rand1[i]][rand2[i]].setTexture(tsmile);
    }
    difFoundMineNum = minenum;

}

void setNumber(int dif) // 지뢰 주변 타일에 숫자 배정
{
    for (int i = 0; i < difX; i++)
    {
        for (int j = 0; j < difY; j++)
        {
            if (tileInfo[i][j].isMine == true) //지뢰 타일 주변 타일들의 num을 1씩 증가
            {
                if (i == 0) // 1행
                {
                    if (j == 0) // [0,0]
                    {
                        tileInfo[0][1].num++;
                        tileInfo[1][0].num++;
                        tileInfo[1][1].num++;
                    }
                    else if (j == difY - 1) //[0,15]
                    {
                        tileInfo[1][difY - 1].num++;
                        tileInfo[1][difY - 2].num++;
                        tileInfo[0][difY - 2].num++;
                    }
                    else if (j > 0 && j < difY - 1) // [0, 1~14]
                    {
                        tileInfo[i][j - 1].num++;
                        tileInfo[i + 1][j - 1].num++;
                        tileInfo[i + 1][j].num++;
                        tileInfo[i + 1][j + 1].num++;
                        tileInfo[i][j + 1].num++;
                    }
                }
                else if (i == difX - 1) // 마지막 행
                {
                    if (j == 0) // [8,0]
                    {
                        tileInfo[difX - 2][0].num++;
                        tileInfo[difX - 2][1].num++;
                        tileInfo[difX - 1][1].num++;
                    }
                    else if (j > 0 && j < difY - 1)
                    {
                        tileInfo[i][j - 1].num++;
                        tileInfo[i - 1][j - 1].num++;
                        tileInfo[i - 1][j].num++;
                        tileInfo[i - 1][j + 1].num++;
                        tileInfo[i][j + 1].num++;
                    }
                    else if (j == difY - 1)
                    {
                        tileInfo[difX - 2][difY - 1].num++;
                        tileInfo[difX - 2][difY - 2].num++;
                        tileInfo[difX - 1][difY - 2].num++;
                    }
                }
                else if (i > 0 && i < difX - 1) // 
                {
                    if (j == 0) // [1~14, 0]
                    {
                        tileInfo[i - 1][j].num++;
                        tileInfo[i - 1][j + 1].num++;
                        tileInfo[i][j + 1].num++;
                        tileInfo[i + 1][j + 1].num++;
                        tileInfo[i + 1][j].num++;
                    }
                    else if (j == difY - 1) //[1~14, 15]
                    {
                        tileInfo[i - 1][j].num++;
                        tileInfo[i - 1][j - 1].num++;
                        tileInfo[i][j - 1].num++;
                        tileInfo[i + 1][j - 1].num++;
                        tileInfo[i + 1][j].num++;
                    }
                    else if (j > 0 && j < difY - 1)
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
}

void Spread(int x, int y)
{
    for (int i = x - 1; i < x + 2; i++) // 버튼 주변 8칸 검색
    {
        for (int j = y - 1; j < y + 2; j++) // 버튼 주변 8칸 검색
        {
            if (i >= 0 && i < difX && j >= 0 && j < difY)
            {
                if (!tileInfo[i][j].isSelected)
                {
                    if (tileInfo[i][j].num == 0)
                    {
                        tTile[i][j].loadFromFile("img/game3/selectedtile.png");
                        tileInfo[i][j].isSelected = true;
                        SelectedTileNum++;
                        Spread(i, j);
                    }
                    else if (tileInfo[i][j].num > 0)
                    {
                        switch (tileInfo[i][j].num)
                        {
                        case 1:
                            tTile[i][j].loadFromFile("img/game3/number1tile.png");
                            break;
                        case 2:
                            tTile[i][j].loadFromFile("img/game3/number2tile.png");
                            break;
                        case 3:
                            tTile[i][j].loadFromFile("img/game3/number3tile.png");
                            break;
                        case 4:
                            tTile[i][j].loadFromFile("img/game3/number4tile.png");
                            break;
                        case 5:
                            tTile[i][j].loadFromFile("img/game3/number5tile.png");
                            break;
                        case 6:
                            tTile[i][j].loadFromFile("img/game3/number6tile.png");
                            break;
                        case 7:
                            tTile[i][j].loadFromFile("img/game3/number7tile.png");
                            break;
                        case 8:
                            tTile[i][j].loadFromFile("img/game3/number8tile.png");
                            break;
                        }
                        tileInfo[i][j].isSelected = true;
                        SelectedTileNum++;
                    }
                }
            }
        }
    }
}

void main_game_3(int dif)
{
    difficulty = dif;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "MineSweeper");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tsmile; // 스마일 마크
    tsmile.loadFromFile("img/game3/smile.png"); // tman에 이미지 로드
    sf::Sprite smile; // 객체 man을 생성
    smile.setTexture(tsmile); // 객체 man의 이미지를 tman의 이미지로 지정

    Result[0].loadFromFile("img/game3/win.jpg");
    Result[1].loadFromFile("img/game3/lose.jpg");
    Sprite result[2];
    result[0].setTexture(Result[0]); //win
    result[1].setTexture(Result[1]);
    result[0].setPosition(350, 200);
    result[1].setPosition(350, 200);

    int mouseX = 0; //클릭한 마우스 x좌표
    int mouseY = 0; //클릭한 마우스 y좌표

    switch (difficulty)
    {
    case 1:
        difX = 9; difY = 9;
        difSelectedTileNum = 65;
        break;
    case 2:
        difX = 16; difY = 9; //9행 16열
        difSelectedTileNum = 116;
        break;
    case 3:
        difX = 16; difY = 16;
        difSelectedTileNum = 216;
        break;
    }

    for (int i = 0; i < difX; i++)
    {
        for (int j = 0; j < difY; j++)
        {
            tTile[i][j].loadFromFile("img/game3/tile.png"); // 빈 타일 로드
            Tile[i][j].setTexture(tTile[i][j]);
            Tile[i][j].setPosition((float)200 + 40 * i, (float)100 + 40 * j);
        }
    }
    setMine(difficulty);

    setNumber(difficulty);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                if (event.KeyPressed == sf::Keyboard::Escape) {
                    window.close();
                    main(1);
                }
            }
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 지뢰찾기 창을 닫고
                main(1); // 메인화면 창을 다시 열기
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //마우스 좌클릭 이벤트
                {
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;
                    if (mouseX <= 200 + 40 * difX && mouseX >= 200 && mouseY <= 100 + 40 * difY && mouseY >= 100) //마우스 범위처리
                    {
                        if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected) //눌려있는 타일이 아니라면
                        {
                            if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isMine) //클릭한 타일이 지뢰이면
                            {
                                window.draw(result[1]);
                                window.display();
                                //window.close();
                                //next game;
                            }
                            else if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].num >= 1)
                            {
                                switch (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].num)
                                {
                                case 1:
                                    tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/number1tile.png");
                                    break;
                                case 2:
                                    tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/number2tile.png");
                                    break;
                                case 3:
                                    tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/number3tile.png");
                                    break;
                                case 4:
                                    tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/number4tile.png");
                                    break;
                                case 5:
                                    tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/number5tile.png");
                                    break;
                                }
                                SelectedTileNum++;

                                if (SelectedTileNum == difSelectedTileNum && FoundMineNum == difFoundMineNum) //모든 지뢰 찾으면
                                {
                                    window.draw(result[0]);
                                    window.display();
                                    //next game
                                }
                            }
                            else if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].num == 0) //누른 타일 주변 8칸에 지뢰가 없음
                            {
                                Spread((mouseX - 200) / 40, (mouseY - 100) / 40);
                                if (SelectedTileNum == difSelectedTileNum && FoundMineNum == difFoundMineNum)
                                {
                                    window.draw(result[0]);
                                    window.display();
                                }
                            }

                            tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected = true;
                        }
                        cout << SelectedTileNum << endl;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) //마우스 우클릭 이벤트
                {
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;
                    if (mouseX <= 200 + 40 * difX && mouseX >= 200 && mouseY <= 100 + 40 * difY && mouseY >= 100)
                    {
                        if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected)
                        {
                            if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isFlag) //플래그 안세운 타일이면
                            {
                                tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/flagtile.png");
                                tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isFlag = true;
                                FlagNum++;
                                if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isMine) //플래그 세운 타일이 지뢰 타일이면
                                {
                                    FoundMineNum++;
                                    if (FoundMineNum == difFoundMineNum && SelectedTileNum == difSelectedTileNum) //다 찾았으면
                                    {
                                        window.draw(result[0]);
                                        window.display();
                                    }
                                }
                            }
                            else
                            {
                                tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/tile.png");
                                tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isFlag = false;
                                FlagNum--;
                                if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isMine == true)
                                {
                                    FoundMineNum--;
                                }
                            }
                        }
                        cout << FoundMineNum << endl;
                    }
                }
            }
        }

        window.clear();
        for (int i = 0; i < difX; i++)
        {
            for (int j = 0; j < difY; j++)
            {
                window.draw(Tile[i][j]); // 타일 그리기
            }
        }
        smile.setPosition(300 + (200 * difficulty / 3), 30); // 스마일 위치 설정
        window.draw(smile); // 스마일 그리기
        window.display(); // 표시
    }

    //return 0;
}
