#define NOMINMAX
#include<Windows.h>
#include "game.h"
using namespace std;
using namespace sf;
int main(int sw)
{
    HWND hWndConsole = GetConsoleWindow();
    ShowWindow(hWndConsole, SW_HIDE);
    cout << sw << endl;
    if (sw == 1) {
        musicstart();
    }
    sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4_main");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tman; // 텍스쳐를 담을 tman 생성
    tman.loadFromFile("img/main/select.png"); // tman에 이미지 로드
    sf::Sprite man; // 객체 man을 생성
    man.setTexture(tman); // 객체 man의 이미지를 tman의 이미지로 지정

    sf::Texture tbackground; // 배경화면을 담을 tbg 행성
    tbackground.loadFromFile("img/main/main.png"); // tbg에 배경화면 이미지 로드
    sf::Sprite background; // 객체 bg를 생성
    background.setTexture(tbackground); // 객체 bg의 이미지를 배경화면 이미지인 tbg로 지정

    double cnt = 0;
    int mouseX = 0; //마우스 좌클릭 x좌표
    int mouseY = 0; //마우스 좌클릭 y좌표

    man.setPosition(358, 418); // 시작 시 캐릭터 좌표 설정
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                return 0;
            }
        }
        window.clear();

        sf::Vector2f speed = { 0,0 }; // 속도 초기화

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { sf::sleep(sf::seconds(0.1f)); speed.y = 102.0f; } // 아래 방향키
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { sf::sleep(sf::seconds(0.1f)); speed.y = -102.0f; } // 위 방향키

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            switch ((int)man.getPosition().y) {
            case 418: //게임시작
                window.close();
                main_difficulty();
                break;
            case 520: //만든이
                window.close();
                main_makers();
                // 만든 이 실행
                break;
            case 622: //나가기
                window.close();
                return 0;
                break;
            }
        }

        man.setPosition(man.getPosition()+speed); // 캐릭터 좌표 설정
        window.draw(background); // 배경화면 그리기

        if (man.getPosition().y < 418) { // 위로 나가지 않게
            man.setPosition(man.getPosition().x, 418);
        }
        else if (man.getPosition().y > 622) { // 아래로 나가지 않게
            man.setPosition(man.getPosition().x, 622);
        }
        window.draw(man); // 캐릭터 그리기

        window.display(); // 표시
    }
    return 0;
}