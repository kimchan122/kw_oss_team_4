#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tman; // 텍스쳐를 담을 tman 생성
    tman.loadFromFile("img/man.png"); // tman에 이미지 로드
    sf::Sprite man; // 객체 man을 생성
    man.setTexture(tman); // 객체 man의 이미지를 tman의 이미지로 지정

    sf::Texture tbackground; // 배경화면을 담을 tbg 행성
    tbackground.loadFromFile("img/hill.jpg"); // tbg에 배경화면 이미지 로드
    sf::Sprite background; // 객체 bg를 생성
    background.setTexture(tbackground); // 객체 bg의 이미지를 배경화면 이미지인 tbg로 지정


    double cnt = 0;
    int sw = 0;

    man.setPosition(512, 384); // 시작 시 캐릭터 좌표 설정
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        sf::Vector2f speed = { 0,0 }; // 속도 초기화

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { speed.x = 8.0f;} // D
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { speed.x = -8.0f; } // A
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { speed.y = 8.0f; } // S
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { speed.y = -8.0f; } // W

        man.setPosition(man.getPosition() + speed); // 캐릭터 좌표 설정
        window.draw(background); // 배경화면 그리기
        
        if (man.getPosition().x < 0) { // 왼쪽 밖으로 나가지 않게
            man.setPosition(0, man.getPosition().y);
        }
        else if (man.getPosition().x > 924) { // 오른쪽 밖으로 나가지 않게
            man.setPosition(924, man.getPosition().y);
        }
        if (man.getPosition().y < 0) { // 위로 나가지 않게
            man.setPosition(man.getPosition().x, 0);
        }
        else if (man.getPosition().y > 668) { // 아래로 나가지 않게
            man.setPosition(man.getPosition().x, 668);
        }

        // 특정 좌표 1일 경우 game_1으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_1로 이동한다.

        // 특정 좌표 2일 경우 game_2으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_2로 이동한다.

        // 특정 좌표 3일 경우 game_3으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_3로 이동한다.

        // 특정 좌표 4일 경우 game_4으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_4로 이동한다.


        man.rotate(10); // 테스트를 위한 스프라이트 회전

        window.draw(man); // 캐릭터 그리기

        window.display(); // 표시

        double x = man.getPosition().x; // 좌표 확인을 위한 콘솔창 출력
        double y = man.getPosition().y;
        cout << x << endl;
        cout << y << endl << endl;
    }

    return 0;
}