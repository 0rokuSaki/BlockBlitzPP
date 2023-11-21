#include "game.h"
#include "interactions.h"


// Constructor
game::game()
{
	// The background, ball and paddle are initialized in-place
	// Populate the bricks vector
    for (int i = 0; i < constants::brick_columns; ++i)
    {
        for (int j = 0; j < constants::brick_rows; ++j)
        {
            // Calculate the brick's position
            auto x = constants::brick_offset + (i + 1) * constants::brick_width;
            auto y = (j + 1) * constants::brick_height;

            // Create the brick object
            this->bricks.emplace_back(x, y);
        }
    }

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    game_window.setFramerateLimit(constants::framerate_limit);
}


// Reinitialize the game
void game::reset()
{
    // Re-populate the bricks vector
    for (int i = 0; i < constants::brick_columns; ++i)
    {
        for (int j = 0; j < constants::brick_rows; ++j)
        {
            // Calculate the brick's position
            auto x = constants::brick_offset + (i + 1) * constants::brick_width;
            auto y = (j + 1) * constants::brick_height;

            // Create the brick object
            this->bricks.emplace_back(x, y);
        }
    }
}


// Game loop
void game::run()
{
    // Was the pause key pressed in the last frame?
    bool pause_key_active{ false };

    while (this->game_window.isOpen())
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

        // If the user presses "P", we pause/unpause the game
        // To prevent repeated use, we ignore it if it was pressed on the last iterations
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            // If it was not pressed on the last iteration, toggle the status
            if (!pause_key_active)
            {
                if (state == game_state::paused)
                {
                    state = game_state::running;
                }
                else
                {
                    state = game_state::paused;
                }
            }
            pause_key_active = true;
        }
        else
        {
            pause_key_active = false;
        }

        // If the user presses "R", we reset the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            reset();
        }

        // In the paused state, the entities are not updated, only re-drawn
        if (state != game_state::paused)
        {
            // Calculate the updated graphics
            the_background.update();
            the_ball.update();
            the_paddle.update();

            for (auto& b : bricks)
            {
                b.update();
            }

            handle_collision(the_ball, the_paddle);

            // Check every brick for a collision with the ball
            for (auto& b : bricks)
            {
                handle_collision(the_ball, b);
            }

            // Erase any destroyed bricks from the grid

            // remove_if moves all elements to the back for which the conditional is true
            // It returns an iterator to the first moved element
            // We then call erase with this iterator as argument
            // This will erase every element following this iterator
            auto it = std::remove_if(std::begin(bricks), std::end(bricks),
                [](const brick& b) { return b.is_destroyed(); });

            bricks.erase(it, std::end(bricks));
        }

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
}
