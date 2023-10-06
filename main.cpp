#include <SFML/Graphics.hpp>
#include <iostream>
#include "Aircraft.h"

using namespace sf;

void Play(std::list<Bullet>& Bul_list, std::list<Aircraft>& Air_list, float mouse_x, float mouse_y)
{
    for (auto it_sam = Air_list.begin(); it_sam != Air_list.end(); ++it_sam)
    {
        (*it_sam).Play(mouse_x, mouse_y, Bul_list);
        //Collision(*it_sam, Bul_list);
    }
    if (Bul_list.size() > 0)
    {
        for (auto it_bul = Bul_list.begin(); it_bul != Bul_list.end();)
        {
            (*it_bul).Play(Bul_list, it_bul);
        }
    }
}

int main()
{
    clock_t t0 = clock();
    setlocale(LC_ALL, "rus");

    RenderWindow window(VideoMode(x_window_size, y_window_size), "Version_1");
    Aircraft Airbus(200, 200, 1, 0, "Images/airplane.png");

    std::list <Aircraft> Samoletu;
    Samoletu.push_back(Airbus);

    std::list <Bullet> bullets;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        Play(bullets, Samoletu, Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        window.clear();
        window.setFramerateLimit(fps);

        for (auto it_sam = Samoletu.begin(); it_sam != Samoletu.end(); ++it_sam)
        {
            window.draw((*it_sam).sprite);
        }
        if (bullets.size() > 0)
        {
            for (auto it_bul = bullets.begin(); it_bul != bullets.end(); ++it_bul)
            {
                window.draw((*it_bul).bullet);
            }
        }
        window.display();
    }
    return 0;
}