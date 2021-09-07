// https://en.sfml-dev.org/forums/index.php?topic=28191.0
/* 
Note to self: This makes no sense at all. Solution was to change from debug to release and it works. Despite the property pages only linking to static/debug libs files.
Further investigation is required to make sense of the files operating in the background.

*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

