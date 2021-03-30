#include "game.h"

using namespace std;
using namespace sf;

struct TileInfo
{
    bool isMine = false; // false�̸� �Ϲ�Ÿ��/����Ÿ�� , true�̸� ����Ÿ��
    bool isSelected = false; //true�̸� ������ Ÿ��
    bool isFlag = false;
    int num = 0;
};

int difficulty;
int difX = 1; //���̵� �� ������ ��
int difY = 1; //���̵� �� ������ ��

struct TileInfo tileInfo[16][16];
Texture tTile[16][16]; // �� Ÿ��
Texture Result[2];
Texture oneMore[1];
Sprite Tile[16][16];

Texture tsmile;

int FlagNum = 0; // ��Ŭ������ üũ�� �÷��� ����
int SelectedTileNum = 0; //������ Ÿ�� ����
int FoundMineNum = 0; //�÷��̾ ã�� ���ڼ�

int difSelectedTileNum; //���̵� �� ���õ� Ÿ�ϰ���
int difFoundMineNum; //���̵� �� �� ���� ��


void setMine(int dif) //Ÿ�Ͽ� ���� ����
{
    //���� ����
    srand((unsigned int)time(NULL));
    int minenum = 0;
    switch (dif) //���̵� �� ���ڰ��� ����
    {
    case 1:
        minenum = 16; //1�ܰ� ���ڼ�
        break;
    case 2:
        minenum = 28;//2�ܰ� ���ڼ�
        break;
    case 3:
        minenum = 40;//3�ܰ� ���ڼ�
        break;
    }
    int* rand1 = new int[minenum];
    int* rand2 = new int[minenum];

    //������ Ÿ�Ͽ� ���� ����
    for (int i = 0; i < minenum; i++)
    {
        rand1[i] = rand() % difX;
        rand2[i] = rand() % difY;
        for (int j = 0; j < i; j++)
        {
            if (rand1[j] == rand1[i] && rand2[j] == rand2[i]) //�ߺ� ����
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

void setNumber(int dif) // ���� �ֺ� Ÿ�Ͽ� ���� ����
{
    for (int i = 0; i < difX; i++)
    {
        for (int j = 0; j < difY; j++)
        {
            if (tileInfo[i][j].isMine == true) //���� Ÿ�� �ֺ� Ÿ�ϵ��� num�� 1�� ����
            {
                if (i == 0) // 1��
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
                else if (i == difX - 1) // ������ ��
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
    for (int i = x - 1; i < x + 2; i++) // ��ư �ֺ� 8ĭ �˻�
    {
        for (int j = y - 1; j < y + 2; j++) // ��ư �ֺ� 8ĭ �˻�
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

int main_game_3(int dif, int pr)
{
    difficulty = dif;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "MineSweeper");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tgtext;
    tgtext.loadFromFile("img/main/g3.png");
    sf::Sprite gtext;
    gtext.setTexture(tgtext);
    window.draw(gtext);
    window.display();
    sf::sleep(sf::seconds(2.0f));

    sf::Texture tsmile; // ������ ��ũ
    tsmile.loadFromFile("img/game3/smile.png"); // tman�� �̹��� �ε�
    sf::Sprite smile; // ��ü man�� ����
    smile.setTexture(tsmile); // ��ü man�� �̹����� tman�� �̹����� ����

    sf::SoundBuffer sbClick;
    sbClick.loadFromFile("sound/game3/click.mp3");
    sf::Sound soundClick;
    soundClick.setBuffer(sbClick);

    Result[0].loadFromFile("img/game3/win.jpg");
    Result[1].loadFromFile("img/game3/lose.jpg");
    Sprite result[2];
    result[0].setTexture(Result[0]); //win
    result[1].setTexture(Result[1]);
    result[0].setPosition(350, 200);
    result[1].setPosition(12, 80);

    oneMore[0].loadFromFile("img/game3/tryagain.png");
    Sprite onemore[1];
    onemore[0].setTexture(oneMore[0]); //ù����case
    onemore[0].setPosition(350, 200);


    int mouseX = 0; //Ŭ���� ���콺 x��ǥ
    int mouseY = 0; //Ŭ���� ���콺 y��ǥ
    bool isFirst = true;
    switch (difficulty)
    {
    case 1:
        difX = 9; difY = 9;
        difSelectedTileNum = 65;
        break;
    case 2:
        difX = 16; difY = 9; //9�� 16��
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
            tTile[i][j].loadFromFile("img/game3/tile.png"); // �� Ÿ�� �ε�
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
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // ��ũ���� X��ư�� �����ų�, Ȥ�� Ű������ ESC�� ������ ����ȭ������ ���ư����� ����
                window.close(); // ����ã�� â�� �ݰ�
                if (pr == 1) {
                    practice(dif);
                }
                else {
                    musicstart();
                    main_difficulty();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //���콺 ��Ŭ�� �̺�Ʈ
                {
                    soundClick.play();
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;
                    if (mouseX <= 200 + 40 * difX && mouseX >= 200 && mouseY <= 100 + 40 * difY && mouseY >= 100) //���콺 ����ó��
                    {
                        if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected) //�����ִ� Ÿ���� �ƴ϶��
                        {
                            if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isMine) //Ŭ���� Ÿ���� �����̸�
                            {
                                if (isFirst == true) {
                                    window.draw(onemore[0]);
                                    window.display();
                                    sf::sleep(sf::seconds(3.0f));
                                    isFirst = false;
                                    break;
                                }
                                window.draw(result[1]);
                                window.display();
                                failsound();
                                sf::sleep(sf::seconds(3.0f));
                                window.close();
                                if (pr == 1) {
                                    practice(dif);
                                }
                                else {
                                    return 1;
                                    break;
                                }
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

                                if (SelectedTileNum == difSelectedTileNum && FoundMineNum == difFoundMineNum) //��� ���� ã����
                                {
                                    sucsound();
                                    //cout << "��ã��!" << endl;
                                    window.draw(result[0]);
                                    window.display();
                                    sf::sleep(sf::seconds(3.0f));
                                    window.close();
                                    if (pr == 1) {
                                        practice(dif);
                                    }
                                    else {
                                        return 0;
                                    }
                                    break;
                                    //next game
                                }
                            }
                            else if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].num == 0) //���� Ÿ�� �ֺ� 8ĭ�� ���ڰ� ����
                            {
                                Spread((mouseX - 200) / 40, (mouseY - 100) / 40);
                                if (SelectedTileNum == difSelectedTileNum && FoundMineNum == difFoundMineNum)
                                {
                                    window.draw(result[0]);
                                    window.display();
                                }
                            }
                            isFirst = false;

                            tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected = true;
                        }
                        cout << SelectedTileNum << endl;
                    }
                    //isFirst = false;
                }
                else if (event.mouseButton.button == sf::Mouse::Right) //���콺 ��Ŭ�� �̺�Ʈ
                {
                    soundClick.play();
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;
                    if (mouseX <= 200 + 40 * difX && mouseX >= 200 && mouseY <= 100 + 40 * difY && mouseY >= 100)
                    {
                        if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isSelected)
                        {
                            if (!tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isFlag) //�÷��� �ȼ��� Ÿ���̸�
                            {
                                tTile[(mouseX - 200) / 40][(mouseY - 100) / 40].loadFromFile("img/game3/flagtile.png");
                                tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isFlag = true;
                                FlagNum++;
                                if (tileInfo[(mouseX - 200) / 40][(mouseY - 100) / 40].isMine) //�÷��� ���� Ÿ���� ���� Ÿ���̸�
                                {
                                    FoundMineNum++;
                                    if (FoundMineNum == difFoundMineNum && SelectedTileNum == difSelectedTileNum) //�� ã������
                                    {
                                        sucsound();
                                        window.draw(result[0]);
                                        window.display();
                                        sf::sleep(sf::seconds(5.0f));
                                        window.close();
                                        if (pr == 1) {
                                            practice(dif);
                                        }
                                        else {
                                            return 0;
                                            break;
                                        }
                                        break;
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
                window.draw(Tile[i][j]); // Ÿ�� �׸���
            }
        }
        smile.setPosition(300 + (200 * difficulty / 3), 30); // ������ ��ġ ����
        window.draw(smile); // ������ �׸���
        window.display(); // ǥ��
    }

    return 0;
}
