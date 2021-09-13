
// https://en.sfml-dev.org/forums/index.php?topic=28191.0
/* 
Note to self: This makes no sense at all. Solution was to change from debug to release and it works. Despite the property pages only linking to static/debug libs files.
Further investigation is required to make sense of the files operating in the background.

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

// call by reference to function.
void window_collision_check(sf::RenderWindow &window, sf::CircleShape &shape)
{
    float win_x = window.getSize().x; 
    float win_y = window.getSize().y;

    float x = shape.getPosition().x;
    float y = shape.getPosition().y;

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

class Player
{
public:
    Player(sf::Vector2f size)
    {
        player.setSize(size);
        player.setFillColor(sf::Color::Magenta);
    }
    void draw_to(sf::RenderWindow& window)
    {
        window.draw(player);
    }
    void set_pos(sf::Vector2f new_pos)
    {
        player.setPosition({ new_pos });
    }
    void move_left()
    {
        player.move(sf::Vector2f(-0.3f, 0.0));
    }
    void move_right()
    {
        player.move(sf::Vector2f(0.3f, 0.0));
    }
    void move_up()
    {
        player.move(sf::Vector2f(0.0, -0.3f));
    }
    void move_down()
    {
        player.move(sf::Vector2f(0.0, +0.3f));
    }
private:
    sf::RectangleShape player;
};

class Game_Floor
{
public:
    Game_Floor(sf::Vector2f size)
    {
        game_floor.setSize(size);
        game_floor.setFillColor(sf::Color::White);
    }
    void draw_to(sf::RenderWindow& window)
    {
        window.draw(game_floor);
    }
    void set_pos(sf::Vector2f new_pos)
    {
        game_floor.setPosition({ new_pos });
    }
private:
    sf::RectangleShape game_floor;
};

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

    Player player({ 50, 50 });
    player.set_pos({ 70, 80 });

    Game_Floor game_floor({ 700, 50 });
    game_floor.set_pos({ 0, 350 });

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
            player.move_left();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            shape.move(sf::Vector2f(0.3f, 0.0));
            player.move_right();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            shape.move(sf::Vector2f(0.0, -0.3f));
            player.move_up();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            shape.move(sf::Vector2f(0.0, +0.3f));
            player.move_down();
        }

        window.clear();
        player.draw_to(window);
        game_floor.draw_to(window);
        window.draw(shape);
        window.draw(shape_two);
        window.draw(class_shape.temp_method());
        std::cout << shape.getPosition().x << " " << shape.getPosition().y << "\n";
        window_collision_check(window, shape);
        //window.draw(rectangle);
        window.display();
        Sleep(0.9);
    }
    return 0;
}
