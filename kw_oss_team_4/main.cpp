#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setSize(sf::Vector2f(100.f, 100.f));

    sf::CircleShape octagon(80.f, 8);
    octagon.setFillColor(sf::Color::Yellow);

    double cnt = 100;
    int sw = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        shape.setPosition(100.f, 100.f);
        rectangle.setPosition(400.f, 400.f);

        window.draw(shape);
        window.draw(rectangle);
        window.draw(octagon);

        octagon.rotate(1.f);
        rectangle.setSize(sf::Vector2f(cnt, cnt));
        if (cnt > 0 && sw==0) {
            cnt -= 0.1;
        }
        else if (cnt <= 0 && sw == 0) {
            sw = 1;
        }
        else if(cnt<100 && sw==1){
            cnt += 0.1;
        }
        else if (cnt >= 100 && sw == 1) {
            sw = 0;
        }
        //cout << "CNT : " << cnt <<", SW : "<<sw<< '\n';
        //test
        //test
        window.display();
    }

    return 0;
}