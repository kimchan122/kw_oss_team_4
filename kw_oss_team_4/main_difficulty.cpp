#include "game.h"

using namespace std;
using namespace sf;
void main_difficulty()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "OSS_Team_4");
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

    man.setPosition(358, 384); // 시작 시 캐릭터 좌표 설정
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                main(0); // 메인화면 창을 다시 열기
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //마우스 좌클릭 이벤트
                {
                    Vector2i pos = Mouse::getPosition(window);
                    mouseX = pos.x;
                    mouseY = pos.y;
                    cout << mouseX << endl;
                    cout << mouseY << endl;
                }
            }
        }
        window.clear();

        sf::Vector2f speed = { 0,0 }; // 속도 초기화

        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { speed.x = 8.0f; } // D
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { speed.x = -8.0f; } // A

        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { speed.y = 8.0f; } // S
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { speed.y = -8.0f; } // W

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { sf::sleep(sf::seconds(0.1f)); speed.y = 102.0f; } // 아래
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { sf::sleep(sf::seconds(0.1f)); speed.y = -102.0f; } // 위

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            switch ((int)man.getPosition().y) {
            case 418:
                musicstop();
                window.close();
                game_centre(1);
                //main_game_1(1);
                //game(1);
                break;
            case 520:
                musicstop();
                window.close();
                game_centre(2);
                // 만든 이 실행
                //game(2);
                break;
            case 622:
                musicstop();
                window.close();
                game_centre(3);
                //game(3);
                break;
            }
        }

        man.setPosition(man.getPosition() + speed); // 캐릭터 좌표 설정
        window.draw(background); // 배경화면 그리기

        if (man.getPosition().y < 418) { // 위로 나가지 않게
            man.setPosition(man.getPosition().x, 418);
        }
        else if (man.getPosition().y > 622) { // 아래로 나가지 않게
            man.setPosition(man.getPosition().x, 622);
        }
        window.draw(man); // 캐릭터 그리기

        window.display(); // 표시

        double x = man.getPosition().x; // 좌표 확인을 위한 콘솔창 출력
        double y = man.getPosition().y;
        cout << x << endl;
        cout << y << endl << endl;
    }
        // 특정 좌표 1일 경우 game_1으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_1로 이동한다.

        // 특정 좌표 2일 경우 game_2으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_2로 이동한다.
        /*
        if (man.getPosition().x == 0 && man.getPosition().y == 668) { // 지뢰찾기 게임(좌하단)
            window.close(); // 메인화면 닫고
            main_game_3(); // 지뢰찾기 실행
            // 지뢰찾기 종료 후 메인화면 실행
        }
        else if (man.getPosition().x == 0 && man.getPosition().y == 0) { // arkanoid게임 (좌상단)
            window.close(); // 메인화면 닫고
            main_game_1(); // 지뢰찾기 실행
            // 지뢰찾기 종료 후 메인화면 실행
        }
        */
        // 특정 좌표 3일 경우 game_3으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_3로 이동한다.

        // 특정 좌표 4일 경우 game_4으로 이동하겠냐는 메시지를 띄운다.
        // 이동(YES)일 경우, game_4로 이동한다.

    //return 0;
}