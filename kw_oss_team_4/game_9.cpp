#include"game.h"

using namespace sf;

struct point
{
    int x, y;
    int valid = 1;
    int num;
};


point tiles1[5][5];
point tiles2[5][5];

Sprite stiles1[25];
Sprite stiles2[25];

int BLANCK_SIZE = 10;
int INIT_X = 250;
int INIT_Y = 200;


int main_game_9(int dif, int pr)
{
    bool isGaming = true;
    bool win = false;

    srand(time(0));

    RenderWindow app(VideoMode(1024, 786), "1to50");
    app.setFramerateLimit(60);


    sf::Texture tgtext;
    tgtext.loadFromFile("img/main/g9.png");
    sf::Sprite gtext;
    gtext.setTexture(tgtext);
    app.draw(gtext);
    app.display();
    sf::sleep(sf::seconds(2.0f));
    /*
    * 조작법
    * 1부터 50까지의 버튼을 빠르게 클릭한다.
    * 쉬움 : 70초 이내 / 중간 : 60초 이내 / 어려움: 50초 이내
    * 
    sf::Texture tgtext;
    tgtext.loadFromFile("img/main/g9.png");
    sf::Sprite gtext;
    gtext.setTexture(tgtext);
    app.draw(gtext);
    app.display();
    sf::sleep(sf::seconds(2.0f));
    */
    
    
    Texture t1, t2, t3, t4, t5;
    t1.loadFromFile("img/game9/background.png");
    t2.loadFromFile("img/game9/tile1.png");
    t3.loadFromFile("img/game9/tile2.png");
    t4.loadFromFile("img/game9/tiles1.png");
    t5.loadFromFile("img/game9/tiles2.png");

    int TILE_WIDTH = 98;


    Sprite sBackground(t1), sTile1(t2), sTile2(t3);

    sf::Font font;

    font.loadFromFile("font/BebasNeue-Regular.ttf");

    sf::Text timerText("timer", font);
    timerText.setCharacterSize(90);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(512 - timerText.getLocalBounds().width/2 , 20);

    sf::Text winText("YOU WIN", font);
    winText.setCharacterSize(60);
    winText.setFillColor(sf::Color::Black);
    winText.setPosition(512 - winText.getLocalBounds().width / 2, 393-winText.getLocalBounds().height/2);

    sf::Text loseText("YOU LOSE", font);
    loseText.setCharacterSize(60);
    loseText.setFillColor(sf::Color::Black);
    loseText.setPosition(512 - loseText.getLocalBounds().width / 2, 393 - loseText.getLocalBounds().height / 2);

    sf::Clock clock;

    
    sf::SoundBuffer sbButton;
    sbButton.loadFromFile("sound/game9/button.wav");

    Sound soundButton;
    soundButton.setBuffer(sbButton);
    
    
    float countdown = 100;
    int num = 0;

    // 난이도에 따른 시간
    if (dif == 1) {
        countdown = 40;
        timerText.setString("40.00");
    }

    if (dif == 2) {
        countdown = 35;
        timerText.setString("35.00");
    }

    if (dif == 3) {
        countdown = 30;
        timerText.setString("30.00");
    }


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tiles1[i][j].x = INIT_X + i * (TILE_WIDTH + BLANCK_SIZE);
            tiles1[i][j].y = INIT_Y + j * (TILE_WIDTH + BLANCK_SIZE);
            tiles1[i][j].valid = 1;
            tiles1[i][j].num = (j * 5) + i ;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tiles2[i][j].x = INIT_X + i * (TILE_WIDTH + BLANCK_SIZE);
            tiles2[i][j].y = INIT_Y + j * (TILE_WIDTH + BLANCK_SIZE);
            tiles2[i][j].valid = 0;
            tiles2[i][j].num = (j * 5) + i + 25;
        }
    }

    // 1부터 50까지의 숫자를 랜덤으로 배치
    srand(time(NULL));
    int temp;
    int randx, randy;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                randx = rand() % 5;
                randy = rand() % 5;
                temp = tiles1[i][j].num;
                tiles1[i][j].num = tiles1[randx][randy].num;
                tiles1[randx][randy].num = temp;
            }
        }
    }
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                randx = rand() % 5;
                randy = rand() % 5;
                temp = tiles2[i][j].num;
                tiles2[i][j].num = tiles2[randx][randy].num;
                tiles2[randx][randy].num = temp;
            }
        }
    }


    // 타일 스프라이트 설정
    for (int i = 0; i < 25; i++) {
        stiles1[i].setTexture(t4);
        stiles1[i].setTextureRect(IntRect((i % 5) * TILE_WIDTH, (i / 5) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
    }
    for (int i = 0; i < 25; i++) {
        stiles2[i].setTexture(t5);
        stiles2[i].setTextureRect(IntRect((i % 5) * TILE_WIDTH, (i / 5) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
    }



    //soundStart.play();
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                app.close(); // 게임창 닫고

                if (pr == 1) {
                    practice(dif);
                }
                else {
                    musicstart();
                    main_difficulty();
                }
            }
        }



        if (isGaming) {
            // 클릭 이벤트
            Vector2i pos = Mouse::getPosition(app);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (pos.x > tiles1[i][j].x && pos.x < tiles1[i][j].x + TILE_WIDTH &&
                            pos.y > tiles1[i][j].y && pos.y < tiles1[i][j].y + TILE_WIDTH)
                        {
                            if (tiles1[i][j].valid ==1) {
                                if (num == tiles1[i][j].num) {
                                    tiles1[i][j].valid = 0;
                                    tiles2[i][j].valid = 1;
                                    num++;
                                    soundButton.play();
                                }
                            }
                        }

                        if (pos.x > tiles2[i][j].x && pos.x < tiles2[i][j].x + TILE_WIDTH &&
                            pos.y > tiles2[i][j].y && pos.y < tiles2[i][j].y + TILE_WIDTH)
                        {
                            if (tiles1[i][j].valid ==0 && tiles2[i][j].valid == 1) {
                                if (num == tiles2[i][j].num) {
                                    tiles2[i][j].valid = 0;
                                    num++;
                                    soundButton.play();
                                }
                            }
                        }
                    }
                }
            }


            int timer = clock.getElapsedTime().asSeconds();

            if (num >0 && num < 50) {
                timer = clock.getElapsedTime().asSeconds();
                if (countdown > 0);
                    countdown -= 0.01;
                int cs = int(countdown);
                int cms = (countdown - cs) * 100;
                
                timerText.setString(std::to_string(cs) + "." + std::to_string(cms));
                timerText.setPosition(512 - timerText.getLocalBounds().width / 2, 20);
            }

            if (countdown < 0 && num != 50) {
                // 게임 오버
                // soundLose.play();
                timerText.setString("0");
                isGaming = false;
            }

            if (countdown != 0 && num == 50) {
                // 게임 성공
                //soundWin.play();
                isGaming = false;
                win = true;
            }

        }

        // draw
        app.draw(sBackground);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++) {
                if (tiles1[i][j].valid == 1) {
                    int tilenum = tiles1[i][j].num;
                    stiles1[tilenum].setPosition(tiles1[i][j].x, tiles1[i][j].y);
                    app.draw(stiles1[tilenum]);
                }
                if (tiles2[i][j].valid == 1) {
                    int tilenum = tiles2[i][j].num - 25;
                    stiles2[tilenum].setPosition(tiles2[i][j].x, tiles2[i][j].y);
                    app.draw(stiles2[tilenum]);
                }
            }
        app.draw(timerText);

        // 성공
        if (isGaming == false && win == true) {
            sucsound();
            app.draw(winText);
            app.display();
            sf::sleep(sf::seconds(1.5f));
            app.close();
            if (pr == 1) {
                practice(dif);
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
                app.close();
                break;
            }
            return 0;
            break;
        }

        // 실패
        if (isGaming == false && win == false) {
            failsound();
            app.draw(loseText);
            app.display();
            sf::sleep(sf::seconds(1.5f));
            app.close();
            if (pr == 1) {
                practice(dif);
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
                app.close();
                break;
            }sf::sleep(sf::seconds(1.5f));
            app.close();
            return 1;
        }
        app.display();
    }

    return 0;
}
