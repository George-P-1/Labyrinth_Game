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
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

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

    // ------------Walls and Borders------------
    texture_wall.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(texture_wall);

    std::vector<sf::Sprite> walls; // Vector for walls

    // ------------Borders------------
    // Left wall
    wall.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y - 125)); // Leave space for starting position
    wall.setPosition(0.0, 125.0); // Starting position
    walls.emplace_back(wall);
    // Top wall
    wall.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 50));
    wall.setPosition(0.0, 0.0);
    walls.emplace_back(wall);
    // Right wall
    wall.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y - 125)); // Leave space for ending position
    wall.setPosition(window.getSize().x - 50, 0.0);
    walls.emplace_back(wall);
    // Bottom wall
    wall.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 50));
    wall.setPosition(0.0, window.getSize().y - 50);
    walls.emplace_back(wall);
    // ------------Maze Walls------------
    // x axis - 100 including width of wall - 75
    // y axis - 100 including width of wall - 75
    // Vertical Walls
    //1
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(125.0, 450.0);
    walls.emplace_back(wall);
    //2
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(225.0, 50.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(225.0, 550.0);
    walls.emplace_back(wall);
    //3
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(325.0, 150.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(325.0, 450.0);
    walls.emplace_back(wall);
    //4
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(425.0, 50.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 200));
    wall.setPosition(425.0, 350.0);
    walls.emplace_back(wall);
    //5
    wall.setTextureRect(sf::IntRect(0, 0, 25, 100));
    wall.setPosition(525.0, 50.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 100));
    wall.setPosition(525.0, 250.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 100));
    wall.setPosition(525.0, 550.0);
    walls.emplace_back(wall);
    //6
    wall.setTextureRect(sf::IntRect(0, 0, 25, 100));
    wall.setPosition(625.0, 350.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 25, 100));
    wall.setPosition(625.0, 650.0);
    walls.emplace_back(wall);
    // Horizontal Walls
    //1
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(50.0, 150.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(550.0, 125.0);
    walls.emplace_back(wall);
    //2
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(150.0, 250.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(650.0, 250.0);
    walls.emplace_back(wall);
    //3
    wall.setTextureRect(sf::IntRect(0, 0, 500, 25));
    wall.setPosition(50.0, 350.0);
    walls.emplace_back(wall);
    //4
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(250.0, 450.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(550.0, 450.0);
    walls.emplace_back(wall);
    //5
    wall.setTextureRect(sf::IntRect(0, 0, 100, 25));
    wall.setPosition(150.0, 550.0);
    walls.emplace_back(wall);
    wall.setTextureRect(sf::IntRect(0, 0, 200, 25));
    wall.setPosition(550.0, 550.0);
    walls.emplace_back(wall);
    //6
    wall.setTextureRect(sf::IntRect(0, 0, 200, 25));
    wall.setPosition(350.0, 637.0);
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
