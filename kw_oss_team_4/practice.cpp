#include"game.h"
using namespace std;
using namespace sf;
void practice(int dif) {
    pmusicstart();
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Practice");
    window.setFramerateLimit(60); // 60fps

    sf::Texture tman; // 텍스쳐를 담을 tman 생성
    tman.loadFromFile("img/main/softman.png"); // tman에 이미지 로드
    sf::Sprite man; // 객체 man을 생성
    man.setTexture(tman); // 객체 man의 이미지를 tman의 이미지로 지정

    sf::Texture tsaebit; // 텍스쳐를 담을 tman 생성
    tsaebit.loadFromFile("img/main/saebit.jpg"); // tman에 이미지 로드
    sf::Sprite saebit; // 객체 man을 생성
    saebit.setTexture(tsaebit); // 객체 man의 이미지를 tman의 이미지로 지정

    sf::Texture tbackground; // 배경화면을 담을 tbg 행성
    tbackground.loadFromFile("img/main/practicemap.png"); // tbg에 배경화면 이미지 로드
    sf::Sprite background; // 객체 bg를 생성
    background.setTexture(tbackground); // 객체 bg의 이미지를 배경화면 이미지인 tbg로 지정

    double cnt = 0;
    int mouseX = 0; //마우스 좌클릭 x좌표
    int mouseY = 0; //마우스 좌클릭 y좌표

    man.setPosition(358, 320); // 시작 시 캐릭터 좌표 설정
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                pmusicstop();
                window.close(); // 게임창 닫고
                musicstart();
                main_difficulty();
                //main(0); // 메인화면 창을 다시 열기
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {speed.y = 8.0f; } //하
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {speed.y = -8.0f; } //상
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {speed.x = -8.0f; } //좌
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {speed.x = 8.0f; } //우

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (man.getPosition().x >= 360 && man.getPosition().x <= 608 && man.getPosition().y >= 312 && man.getPosition().y <= 432) { // 침대 -> 뒤로가기
                pmusicstop();
                window.close();
                musicstart();
                main_difficulty();
            }
            if (man.getPosition().x >= 0 && man.getPosition().x <= 96 && man.getPosition().y >= 0 && man.getPosition().y <= 72) { // game1
                pmusicstop();
                window.close();
                main_game_1(dif,1);
            }
            if (man.getPosition().x >= 0 && man.getPosition().x <= 96 && man.getPosition().y >= 200 && man.getPosition().y <= 272) { // game2
                pmusicstop();
                window.close();
                main_game_2(dif, 1);
            }
            if (man.getPosition().x >= 0 && man.getPosition().x <= 96 && man.getPosition().y >= 400 && man.getPosition().y <= 472) { // game3
                pmusicstop();
                window.close();
                main_game_3(dif, 1);
            }
            if (man.getPosition().x >= 0 && man.getPosition().x <= 96 && man.getPosition().y >= 600 && man.getPosition().y <= 672) {
                pmusicstop();
                window.close();
                main_game_6(dif, 1);
            }

        }

        man.setPosition(man.getPosition() + speed); // 캐릭터 좌표 설정
        window.draw(background); // 배경화면 그리기

        if (man.getPosition().x < 0) { // 위로 나가지 않게
            man.setPosition(0, man.getPosition().y);
        }
        else if (man.getPosition().x > 955) { // 아래로 나가지 않게
            man.setPosition(955, man.getPosition().y);
        }

        if (man.getPosition().y < 0) { // 위로 나가지 않게
            man.setPosition(man.getPosition().x, 0);
        }
        else if (man.getPosition().y > 678) { // 아래로 나가지 않게
            man.setPosition(man.getPosition().x, 678);
        }
        window.draw(man); // 캐릭터 그리기

        window.display(); // 표시

        double x = man.getPosition().x; // 좌표 확인을 위한 콘솔창 출력
        double y = man.getPosition().y;
        cout << x << endl;
        cout << y << endl << endl;
    }

}