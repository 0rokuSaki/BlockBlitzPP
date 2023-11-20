#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "background.h"
#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "constants.h"
#include "interactions.h"

using namespace std::literals;


// The main function for the program
int main()
{
    // Create the background object
    background the_background{ 0.0f, 0.0f };

    // Create a ball object in the middle of the screen
    ball the_ball{ constants::window_width / 2.0f, constants::window_height / 2.0f };

    // Create a paddle object in the bottom-middle of the screen
    paddle the_paddle{ (constants::window_width / 2.0f) - (constants::paddle_width / 2.0f),
                   (constants::window_height) - constants::paddle_height };

    // Create the grid of bricks 
    // We will use an std::vector to store them
    std::vector<brick> bricks;

    for (int i = 0; i < constants::brick_columns; ++i)
    {
        for (int j = 0; j < constants::brick_rows; ++j)
        {
            // Calculate the brick's position
            auto x = constants::brick_offset + (i + 1) * constants::brick_width;
            auto y = (j + 1) * constants::brick_height;

            // Create the brick object
            bricks.emplace_back(x, y);
        }
    }

    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow game_window{ {constants::window_width, constants::window_height}, "BlockBlitz++"s };

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    game_window.setFramerateLimit(constants::framerate_limit);

    // Game loop
    // Clear the screen
    // Check for new events
    // Calculate the updated graphics
    // Display the updated graphics
    while (game_window.isOpen())
    {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        // Check for any event since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "Close", we close the window
        // This will terminate the program
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game_window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            game_window.close();
        }

        // Calculate the updated graphics
        the_background.update();
        the_ball.update();
        the_paddle.update();

        for (auto& b : bricks)
        {
            b.update();
        }

        handle_collision(the_ball, the_paddle);

        // Draw the graphics to the window's buffer
        the_background.draw(game_window);
        the_ball.draw(game_window);
        the_paddle.draw(game_window);

        for (auto b : bricks)
        {
            b.draw(game_window);
        }

        // Display the updated graphics
        game_window.display();
    }

	return 0;
}
