#include "game.h"
#include <time.h>

using namespace std;
using namespace sf;

struct Enemy
{
    bool isHit = false;
    Sprite spEnemy;
    Vector2f speed = { 8,8 };
};
int i = 0;
int main_game_6(int dif, int pr) // 난이도를 나타내는 dif. 1 : easy, 2 : normal, 3 : hard
{
    sf::RenderWindow window(sf::VideoMode(1024, 678), "dodge");
    window.setFramerateLimit(60); // 60fps

    Texture txBackground, txPlayer, txEnemy;
    txBackground.loadFromFile("img/game6/background.png");
    txPlayer.loadFromFile("img/game6/poland.png");
    txEnemy.loadFromFile("img/game6/enemy.png");

    Enemy enemy[300];
    Sprite spBackground,spPlayer;
    spBackground.setTexture(txBackground);
    spPlayer.setTexture(txPlayer);

    for(int i=0; i<300; i++)
    enemy[i].spEnemy.setTexture(txEnemy);
    

    spPlayer.setPosition(512, 384);

    Clock clock;
    
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close();
                if (pr == 1) {
                    practice(dif);
                }
                else {
                    musicstart();
                    main_difficulty();
                }
            }
        }

        Vector2f speed = { 0,0 }; // 속도 초기화
        Time elapsed = clock.getElapsedTime(); //다음 restart() 까지 걸린 시간

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { speed.y = 8.0f; } //하
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { speed.y = -8.0f; } //상
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { speed.x = -8.0f; } //좌
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { speed.x = 8.0f; } //우
        spPlayer.setPosition(spPlayer.getPosition() + speed); // 캐릭터 좌표 설정

        if (spPlayer.getPosition().x < 0) { // 왼쪽으로 나가지 않게
            spPlayer.setPosition(0, spPlayer.getPosition().y);
        }
        else if (spPlayer.getPosition().x > 990) { // 오른쪽으로 나가지 않게
            spPlayer.setPosition(990, spPlayer.getPosition().y);
        }

        if (spPlayer.getPosition().y < 0) { // 위로 나가지 않게
            spPlayer.setPosition(spPlayer.getPosition().x, 0);
        }
        else if (spPlayer.getPosition().y > 648) { // 아래로 나가지 않게
            spPlayer.setPosition(spPlayer.getPosition().x, 648);
        }
        
        
        
        window.draw(spBackground);
        window.draw(spPlayer);

        if (elapsed.asSeconds() >= 0.3) //0.3초마다 발생 이벤트
        {
            enemy[i].spEnemy.setPosition(enemy[i].spEnemy.getPosition() + enemy[i].speed);
            window.draw(enemy[i].spEnemy);
            i++;
            clock.restart(); //타이머 재시작
        }
        if (i == 300)
            i = 0;
        window.display(); // 표시
    }
    return 0;
}