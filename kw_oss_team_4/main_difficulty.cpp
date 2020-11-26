#include "game.h"

using namespace std;
using namespace sf;
void main_difficulty()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4_diffi");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tman; // 텍스쳐를 담을 tman 생성
    tman.loadFromFile("img/main/select.png"); // tman에 이미지 로드
    sf::Sprite man; // 객체 man을 생성
    man.setTexture(tman); // 객체 man의 이미지를 tman의 이미지로 지정

    sf::Texture tbackground; // 배경화면을 담을 tbg 행성
    tbackground.loadFromFile("img/main/diffi.png"); // tbg에 배경화면 이미지 로드
    sf::Sprite background; // 객체 bg를 생성
    background.setTexture(tbackground); // 객체 bg의 이미지를 배경화면 이미지인 tbg로 지정

    double cnt = 0;
    int sw = 0;
    int mouseX = 0; //마우스 좌클릭 x좌표
    int mouseY = 0; //마우스 좌클릭 y좌표

    man.setPosition(358, 418); // 시작 시 캐릭터 좌표 설정

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                main(0); // 메인화면 창을 다시 열기
            }
        }
        window.clear();
        sf::Vector2f speed = { 0,0 }; // 속도 초기화

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { sf::sleep(sf::seconds(0.2f)); speed.y = 102.0f; } // 아래
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { sf::sleep(sf::seconds(0.2f)); speed.y = -102.0f; } // 위
        if(window.isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                switch ((int)man.getPosition().y) {
                case 419:
                    window.close();
                    selectmode(1);
                    //game_centre(1);
                    //main_game_1(1);
                    //game(1);
                    break;
                case 521:
                    //musicstop();
                    window.close();
                    selectmode(2);
                    //game_centre(2);
                    //game(2);
                    break;
                case 623:
                    //musicstop();
                    window.close();
                    selectmode(3);
                    //game_centre(3);
                    //game(3);
                    break;
                }
            }
        }
        man.setPosition(man.getPosition() + speed); // 캐릭터 좌표 설정
        window.draw(background); // 배경화면 그리기

        if (man.getPosition().y < 419) { // 위로 나가지 않게
            man.setPosition(man.getPosition().x, 419);
        }
        else if (man.getPosition().y > 623) { // 아래로 나가지 않게
            man.setPosition(man.getPosition().x, 623);
        }
        window.draw(man); // 캐릭터 그리기

        window.display(); // 표시

        double x = man.getPosition().x; // 좌표 확인을 위한 콘솔창 출력
        double y = man.getPosition().y;
        cout << x << endl;
        cout << y << endl << endl;
    }
    //return 0;
}