
// https://en.sfml-dev.org/forums/index.php?topic=28191.0
/* 
Note to self: This makes no sense at all. Solution was to change from debug to release and it works. Despite the property pages only linking to static/debug libs files.
Further investigation is required to make sense of the files operating in the background.

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

void window_collision_check(float win_x, float win_y, float x, float y)
{
    std::cout << win_x << "\n";
    std::cout << win_y << "\n";
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 400), "<====Title====>", sf::Style::Close | sf::Style::Titlebar);
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape_two(25.f);
    shape_two.setFillColor(sf::Color::Red);

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setSize(sf::Vector2f(100.f, 100.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            shape.move(sf::Vector2f(-0.3f, 0.0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            shape.move(sf::Vector2f(0.3f, 0.0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            shape.move(sf::Vector2f(0.0, -0.3f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            shape.move(sf::Vector2f(0.0, +0.3f));
        }

        window.clear();
        window.draw(shape);
        window.draw(shape_two);
        std::cout << shape.getPosition().x << " " << shape.getPosition().y << "\n";
        window_collision_check(window.getSize().x, window.getSize().y, shape.getPosition().x, shape.getPosition().y);
        window.draw(rectangle);
        window.display();
        Sleep(0.01);

    }

    return 0;
}
