
// https://en.sfml-dev.org/forums/index.php?topic=28191.0
/* 
Note to self: This makes no sense at all. Solution was to change from debug to release and it works. Despite the property pages only linking to static/debug libs files.
Further investigation is required to make sense of the files operating in the background.

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

// call by reference to function.
void window_collision_check(float win_x, float win_y, float x, float y, sf::CircleShape &shape)
{
    x = shape.getPosition().x;
    y = shape.getPosition().y;

    std::cout << "=====================================================" << "\n";
    std::cout << win_x << "\n";
    std::cout << win_y << "\n";

    if (x <= 0)
    {
        std::cout << "That's bad" << "\n";
        std::cout << "x <= 0" << "\n";
        shape.setPosition(50.f, 50.f);
    }
    if (x >= win_x)
    {
        std::cout << "That's bad" << "\n";
        std::cout << "x >= win_x" << "\n";
        shape.setPosition(50.f, 50.f);
    }
    if (y <= 0)
    {
        std::cout << "That's bad" << "\n";
        std::cout << "y <= 0" << "\n";
        shape.setPosition(50.f, 50.f);
    }
    if (y >= win_y)
    {
        std::cout << "That's bad" << "\n";
        std::cout << "y >= win_y" << "\n";
        shape.setPosition(50.f, 50.f);
    }

    std::cout << "=====================================================" << "\n";
}

class TempClass
{
    public:
        sf::CircleShape temp_method()
        {
            std::cout << "[Debug] Generating shape here" << "\n";
            sf::CircleShape shape(25.f);
            shape.setFillColor(sf::Color::Blue);
            shape.setPosition(50.f, 50.f);
            return shape;
        }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 400), "<====Title====>", sf::Style::Close | sf::Style::Titlebar);
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape_two(25.f);
    shape_two.setFillColor(sf::Color::Red);

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setSize(sf::Vector2f(100.f, 100.f));

    TempClass class_shape;

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
        window.draw(class_shape.temp_method());
        std::cout << shape.getPosition().x << " " << shape.getPosition().y << "\n";
        window_collision_check(window.getSize().x, window.getSize().y, shape.getPosition().x, shape.getPosition().y, shape);
        //window.draw(rectangle);
        window.display();
        Sleep(0.9);

    }

    return 0;
}
