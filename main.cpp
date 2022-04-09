// ------------------------------FINAL ASSIGNMENT-------------------------------
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void exact_bound(sf::Sprite &guy, int right, int bottom)
{
    sf::FloatRect bounds = guy.getGlobalBounds();
    if(bounds.top <= 0.0)
    {
        guy.setPosition(bounds.left, 0.0);
    }
    if(bounds.left <= 0.0)
    {
        guy.setPosition(0.0, bounds.top);
    }
    if(bounds.left >= right - bounds.width)
    {
        guy.setPosition(right - bounds.width, bounds.top);
    }
    if(bounds.top >= bottom - bounds.height)
    {
        guy.setPosition(bounds.left, bottom - bounds.height);
    }
}

void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key, sf::Sprite &guy, sf::RenderWindow &window)
{
    // set speed
    int speed_x = 250;
    int speed_y = 250;
    int right = window.getSize().x;
    int bottom = window.getSize().y;
    sf::FloatRect bounds = guy.getGlobalBounds();
    if(key == sf::Keyboard::Up && !(bounds.top <= 0.0))
    {
        guy.move(0, -speed_y * elapsed.asSeconds());
    }
    else if(key == sf::Keyboard::Right && !(bounds.left >= right - bounds.width))
    {
        guy.move(speed_x * elapsed.asSeconds(), 0);
    }
    else if(key == sf::Keyboard::Down && !(bounds.top >= bottom - bounds.height))
    {
        guy.move(0, speed_y * elapsed.asSeconds());
    }
    else if(key == sf::Keyboard::Left && !(bounds.left <= 0.0))
    {
        guy.move(-speed_x * elapsed.asSeconds(), 0);
    }
    exact_bound(guy, right, bottom);
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");

    // ------------Load Textures------------
    sf::Texture texture_grass;
    if (!texture_grass.loadFromFile("grass.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("wall.png")) return 1;

    sf::Texture texture_guy;
    if(!texture_guy.loadFromFile("guy.png")) return 1;

    // ------------Grass Background------------
    texture_grass.setRepeated(true);
    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    // ------------Walls------------
    texture_wall.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(texture_wall);

    std::vector<sf::Sprite> walls; // Vector for walls

    // Left wall
    wall.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y - 125)); // Leave space for starting position
    wall.setPosition(0.0, 125.0); // Starting position
    walls.emplace_back(wall);
    // Top wall
    wall.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 50));
    wall.setPosition(0.0, 0.0);
    walls.emplace_back(wall);
    // Right wall
    wall.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y));
    wall.setPosition(window.getSize().x - 50, 0.0);
    walls.emplace_back(wall);
    // Bottom wall
    wall.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 50));
    wall.setPosition(0.0, window.getSize().y - 50);
    walls.emplace_back(wall);

    // ------------Character------------
    sf::Sprite guy;
    guy.setTexture(texture_guy);
    guy.setPosition(0.0, 50.0); // Start at top-left

    // Start clock
    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        // ------------Move Character------------
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            moveInDirection(elapsed, sf::Keyboard::Up, guy, window);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            moveInDirection(elapsed, sf::Keyboard::Down, guy, window);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            moveInDirection(elapsed, sf::Keyboard::Left, guy, window);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            moveInDirection(elapsed, sf::Keyboard::Right, guy, window);
        }

        // ------------Quit - Press Q------------
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            return 0; // return 0 means program worked how it was supposed to.
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) window.close();
        }

        // ------------draw everything here...------------
        // Background
        window.draw(grass);
        // Walls
        for(auto &wall : walls)
        {
            window.draw(wall);
        }
        // Character
        window.draw(guy);

        // end the current frame
        window.display();
    }

    return 0;
}
