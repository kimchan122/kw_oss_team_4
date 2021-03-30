#include "game.h"
using namespace std;
using namespace sf;
int main_game_8(int dif, int pr)
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4_Game_8");
    window.setFramerateLimit(60); // 60fps
    sf::Clock clock;
    sf::Texture tgtext;
    tgtext.loadFromFile("img/main/g8.png");
    sf::Sprite gtext;
    gtext.setTexture(tgtext);
    window.draw(gtext);
    window.display();
    sf::sleep(sf::seconds(2.0f));

    sf::Texture press;
    sf::Texture pressed;
    press.loadFromFile("img/game8/press.png");
    pressed.loadFromFile("img/game8/pressed.png");
    sf::Sprite gpress;
    sf::Sprite gpressed;
    gpress.setTexture(press);
    gpressed.setTexture(pressed);

    sf::Font font;
    font.loadFromFile("font/BMJUA_ttf.ttf");
    sf::Text timers("timer", font);
    timers.setCharacterSize(90);
    timers.setFillColor(sf::Color::Black);
    timers.setPosition(512 - timers.getLocalBounds().width / 2, 20);
    sf::Text countt("count", font);
    countt.setCharacterSize(90);
    countt.setFillColor(sf::Color::Black);
    countt.setPosition(120, 20);

    double cnt = 0;
    bool sw = true,pan=false;
    int num = 0;
    int mouseX = 0; //���콺 ��Ŭ�� x��ǥ
    int mouseY = 0; //���콺 ��Ŭ�� y��ǥ
    if (dif == 1) {
        cnt = 50;
        timers.setString("50.00");
    }
    else if (dif == 2) {
        cnt = 30;
        timers.setString("30.00");
    }
    else if (dif == 3) {
        cnt = 10;
        timers.setString("10.00");
    }
    window.draw(gpress);
    int sww = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // ��ũ���� X��ư�� �����ų�, Ȥ�� Ű������ ESC�� ������ ����ȭ������ ���ư����� ����
                window.close(); // ����â �ݰ�
                if (pr == 1) {
                    practice(dif);
                }
                else {
                    musicstart();
                    main_difficulty();
                }
            }
            cout << "ENTER!!" << endl;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && sww==1) {
                cout << "ENTER" << endl;
                window.draw(gpressed);
                window.display();
                num++;
                sww = 0;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter && sww == 0) {
                sww = 1;
            }
        }
        //window.display();
        int timer = clock.getElapsedTime().asSeconds();
        if (sw) {
            window.draw(gpress);
            //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && sww==0){

            //if (num > 0 && num < 50) 

//            }

            if (cnt < 0 && num != 50) {
                // ���� ����
                // soundLose.play();
                timers.setString("0");
                sw = false;
                failsound();
                sf::sleep(sf::seconds(3.0f));
                window.close(); // ����â �ݰ�
                if (pr == 1) {
                    practice(dif);
                }
                return 1;
                break;
            }

            if (cnt != 0 && num == 50) {
                // ���� ����
                //soundWin.play();
                sw = false;
                pan = true;
                sucsound();
                sf::sleep(sf::seconds(3.0f));
                window.close(); // ����â �ݰ�
                if (pr == 1) {
                    practice(dif);
                }
                return 0;
                break;
            }
        }
        window.draw(timers);
        window.draw(countt);
        window.display();
        timer = clock.getElapsedTime().asSeconds();
        if (cnt > 0);
        cnt -= 0.017;
        int cs = int(cnt);
        int cms = (cnt - cs) * 100;

        timers.setString(std::to_string(cs) + "." + std::to_string(cms));
        timers.setPosition(750, 20);

        window.draw(countt);
        //window.display();
        countt.setString("count: " + std::to_string(num) + " / 50" );
        countt.setPosition(10, 20);
    }

    return 0;
}