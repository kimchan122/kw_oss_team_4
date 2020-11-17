#include"game.h"
using namespace sf;

struct point
{
    int x, y;
};

void main_game_2()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4;
    t1.loadFromFile("img/game2/background.png");
    t2.loadFromFile("img/game2/platform.png");
    t3.loadFromFile("img/game2/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && x < 320) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left) && x > 0) x -= 3;
        

        dy += 0.2;
        y += dy;


        if (y < h)
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
            }

        for (int i = 0; i < 10;     i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;


        // 게임 오버
        if (y > 500) {
            dy = 0;
            dx = 0;
            if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
                break;
            }
        }

        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    //return 0;
}
