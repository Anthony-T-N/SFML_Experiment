
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
        player.setFillColor(sf::Color::Yellow);
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
    sf::RectangleShape get_player()
    {
        return player;
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
    float get_game_floor_y()
    {
        return game_floor.getPosition().y;
    }
    sf::RectangleShape get_game_floor()
    {
        return game_floor;
    }
private:
    sf::RectangleShape game_floor;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 400), "<====Title====>", sf::Style::Close | sf::Style::Titlebar);
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);

    Player player({ 50, 50 });
    player.set_pos({ 70, 80 });

    Game_Floor game_floor({ 700, 50 });
    game_floor.set_pos({ 0, 350 });

    // Gravity
    const int ground_height = game_floor.get_game_floor_y();
    const float gravity_speed = 0.3;
    bool is_jumping = false;

    while (window.isOpen())
    {
        sf::Event event;

        const float move_speed = 0.2;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        is_jumping = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            shape.move(sf::Vector2f(-0.3f, 0.0));
            player.move_left();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            shape.move(sf::Vector2f(0.3f, 0.0));
            player.move_right();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            shape.move(sf::Vector2f(0.0, -0.3f));
            is_jumping = true;
            player.move_up();
        }
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            shape.move(sf::Vector2f(0.0, +0.3f));
            player.move_down();
        }
        */

        // Gravity Logic 
        if (player.get_player().getPosition().y < ground_height && is_jumping == false)
        {
            player.move_down();
        }


        window.clear();
        player.draw_to(window);
        game_floor.draw_to(window);
        window.draw(shape);
        std::cout << shape.getPosition().x << " " << shape.getPosition().y << "\n";
        if (player.get_player().getGlobalBounds().intersects(game_floor.get_game_floor().getGlobalBounds()))
        {
            std::cout << "Intersection" << "\n";
            player.move_up();
        }
        window_collision_check(window, shape);
        window.display();
        Sleep(0.9);
    }
    return 0;
}
