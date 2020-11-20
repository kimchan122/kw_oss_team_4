#include "game.h"
using namespace std;
using namespace sf;
void main_story(int dif) {
    sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4_story");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tbackground; // 배경화면을 담을 tbg 행성
    tbackground.loadFromFile("img/main/story.png"); // tbg에 배경화면 이미지 로드
    sf::Sprite background; // 객체 bg를 생성
    background.setTexture(tbackground); // 객체 bg의 이미지를 배경화면 이미지인 tbg로 지정

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                main(1); // 메인화면 창을 다시 열기
            }
        }
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            window.close();
            break;
        }
        window.draw(background); // 배경화면 그리기
        window.display(); // 표시
    }
}