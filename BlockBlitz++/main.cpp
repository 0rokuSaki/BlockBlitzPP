#include <SFML/Graphics.hpp>

#include <string>

#include "constants.h"
#include "background.h"

using namespace std::literals;


// The main function for the program
int main()
{
    // Create the background object
    background bg{ 0.0f, 0.0f };

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
        bg.update();

        // Draw the graphics to the window's buffer
        bg.draw(game_window);

        // Display the updated graphics
        game_window.display();
    }

	return 0;
}
