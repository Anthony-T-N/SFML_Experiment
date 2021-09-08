
// https://en.sfml-dev.org/forums/index.php?topic=28191.0
/* 
Note to self: This makes no sense at all. Solution was to change from debug to release and it works. Despite the property pages only linking to static/debug libs files.
Further investigation is required to make sense of the files operating in the background.

*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "<====Title====>");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape_two(25.f);
    shape_two.setFillColor(sf::Color::Red);

    //sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    //rectangle.setSize(sf::Vector2f(100.f, 100.f));

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
            shape.move(sf::Vector2f(-0.5f, 0.0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            shape.move(sf::Vector2f(0.5f, 0.0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            shape.move(sf::Vector2f(0.0, -0.5f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            shape.move(sf::Vector2f(0.0, +0.5f));
        }

        window.clear();
        window.draw(shape);
        window.draw(shape_two);
        //window.draw(rectangle);
        window.display();

    }

    return 0;
}
