#include "game.h"

using namespace std;
using namespace sf;


void main_game_6(int dif, int pr) // 난이도를 나타내는 dif. 1 : easy, 2 : normal, 3 : hard
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "dodge");
    window.setFramerateLimit(60); // 60fps

    Texture txBackground;
    txBackground.loadFromFile("img/man.png");
    Sprite spBackground;
    spBackground.setTexture(txBackground);
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                if (event.KeyPressed == sf::Keyboard::Escape) {
                    window.close();
                    main(1);
                }
            }
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close();
                if (pr == 1) {
                    practice(dif);
                }
                else {
                    main(1); // 메인화면 창을 다시 열기
                }
            }
        }

        
        if (Keyboard::isKeyPressed(Keyboard::Right)) //방향키 우
        {
            
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) //방향키 좌
        {
            
        }

        window.draw(spBackground);
        window.display(); // 표시

        
    }
}