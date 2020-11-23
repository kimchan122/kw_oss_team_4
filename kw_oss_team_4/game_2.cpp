#include"game.h"

using namespace sf;

struct point
{
    int x, y;
    int valid = 1;
};

int main_game_2(int dif, int pr)
{
    bool isGaming = true;
    bool win = false;

    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4;
    t1.loadFromFile("img/game2/background.png");
    t2.loadFromFile("img/game2/platform.png");
    t3.loadFromFile("img/game2/doodle.png");
    t4.loadFromFile("img/game2/coin.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3), sCoin(t4);

    sf::Font font;

    font.loadFromFile("font/Brokenbrush.ttf");

    sf::Text scoreText("Score: ", font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 0);
    
    sf::Text scoreText2("0", font);
    scoreText2.setCharacterSize(40);
    scoreText2.setFillColor(sf::Color::Black);
    scoreText2.setPosition(110, 0);

    sf::Text winText("YOU WIN", font);
    winText.setCharacterSize(60);
    winText.setFillColor(sf::Color::Black);
    winText.setPosition(110, 100);

    sf::Text loseText("YOU LOSE", font);
    loseText.setCharacterSize(60);
    loseText.setFillColor(sf::Color::Black);
    loseText.setPosition(110, 100);

    sf::SoundBuffer sbStart, sbJump, sbWin, sbLose, sbCoin;
    sbStart.loadFromFile("sound/game2/start.wav");
    sbJump.loadFromFile("sound/game2/jump-arcade.mp3");
    sbWin.loadFromFile("sound/game2/win.mp3");
    sbLose.loadFromFile("sound/game2/falling-sound-arcade.mp3");
    sbCoin.loadFromFile("sound/game2/coin.wav");

    Sound soundStart, soundJump, soundWin, soundLose, soundCoin;
    soundStart.setBuffer(sbStart);
    soundJump.setBuffer(sbJump);
    soundWin.setBuffer(sbWin);
    soundLose.setBuffer(sbLose);
    soundCoin.setBuffer(sbCoin);


    point plat[20];
    point coin[20];

    int score = 0;
    int point;


    // 난이도에 따른 배점
    if (dif == 1) {
        point = 5;
    }

    if (dif == 2) {
        point = 2;
    }

    if (dif == 3){
        point = 1;
    }


    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % (400-68);
        plat[i].y = rand() % 533;
    }

    for (int i = 0; i < 10; i++) {
        if (coin[i].valid == 1) {
            coin[i].x = plat[i].x + 12;
            coin[i].y = plat[i].y - 45;
        }
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    soundStart.play();

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
            if (Keyboard::isKeyPressed(Keyboard::Right) && x < 320) x += 3;
            if (Keyboard::isKeyPressed(Keyboard::Left) && x > 0) x -= 3;
            dy += 0.2;
            y += dy;


            if (y < h)
                for (int i = 0; i < 10; i++)
                {
                    y = h;
                    plat[i].y = plat[i].y - dy;
                    coin[i].y = coin[i].y - dy;
                    if (plat[i].y > 533) {
                        plat[i].y = 0; plat[i].x = rand() % (400 - 68);
                        coin[i].valid = 1;
                        coin[i].y = plat[i].y - 45; coin[i].x = plat[i].x + 12;
                        soundJump.play();
                    }
                }


            for (int i = 0; i < 10; i++)
                if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                    && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;


            // 코인 얻음
            for (int i = 0; i < 10; i++)
                if ((x + 50 > coin[i].x) && (x + 20 < coin[i].x + 40)
                    && (y + 70 > coin[i].y) && (y + 70 < coin[i].y + 40)) {
                    coin[i].y = -1000;
                    coin[i].valid = 0;
                    soundCoin.play();
                    if (score < 100) {
                        score += point;
                        if (score == 100)    isGaming = false;
                        scoreText2.setString(std::to_string(score));
                    }
                }

            
        }

        


        // 성공
        if (score == 100) {
            soundWin.play();
            win = true;
            dy = 0;
            dx = 0;
            point = 0;
            //if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                break;
            }
            
        }


        // 게임 오버
        if (y > 500) {
            soundLose.play();
            isGaming = false;
            app.draw(loseText);
            app.display();
            failsound();
            sf::sleep(sf::seconds(1.5f));
            app.close();
            return 1;
            break;
            if (pr == 1) {
                //if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    //app.close();
                    practice(dif);
                    break;
                }
            }
            //dy = 0;
            //dx = 0;
            //if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                app.close();
                break;
            }
        }

        sPers.setPosition(x, y);

        
        app.draw(sBackground);
        app.draw(sPers);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            sCoin.setPosition(coin[i].x, coin[i].y);
            app.draw(sCoin);
            app.draw(sPlat);
        }
        app.draw(scoreText);
        app.draw(scoreText2);

        if (isGaming == false && win == true) {
            app.draw(winText);
            app.display();
            //suc sound
            sf::sleep(sf::seconds(1.5f));
            app.close();
            return 0;
            break;
        }
        if (isGaming == false && win == false) {
            app.draw(loseText);
        }
        app.display();
    }

    return 0;
}
