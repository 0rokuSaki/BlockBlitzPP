#include "game.h"
#include "interactions.h"
#include "background.h"
#include "ball.h"
#include "brick.h"
#include "paddle.h"


// Constructor
game::game()
{
	// Limit the framerate
	// This allows other processes to run and reduces power consumption
	game_window.setFramerateLimit(constants::framerate_limit);

	// Load a font from file
	verdana.loadFromFile("C:/Windows/fonts/verdana.ttf");

	// Configure text objects
	text_state.setFont(verdana);
	text_state.setPosition(constants::text_state_position_x, constants::text_state_position_y);
	text_state.setCharacterSize(constants::text_state_size);
	text_state.setFillColor(sf::Color::White);
	text_state.setString("Running");

	text_lives.setFont(verdana);
	text_lives.setPosition(constants::text_lives_position_x, constants::text_lives_position_y);
	text_lives.setCharacterSize(constants::text_lives_size);
	text_lives.setFillColor(sf::Color::White);
	text_lives.setString("Lives: " + std::to_string(lives));

	reset();
}


// Reinitialize the game
void game::reset()
{
    state = game_state::paused;

	// Reset number of lives
	lives = constants::player_lives;
	text_lives.setString("Lives: " + std::to_string(lives));

    // Destroy all the entities and re-create them
    manager.clear();

    manager.create<background>(0.0f, 0.0f);
    manager.create<ball>(constants::window_width / 2.0f, constants::window_height / 2.0f);
    manager.create<paddle>(constants::window_width / 2.0f, constants::window_height - constants::paddle_height);

    // Re-populate the bricks vector
    for (int i = 0; i < constants::brick_columns; ++i) {
        for (int j = 0; j < constants::brick_rows; ++j) {
            // Calculate the brick's position
            float x = constants::brick_offset + (i + 1) * constants::brick_width;
            float y = (j + 1) * constants::brick_height;

            // Create the brick object
            manager.create<brick>(x, y);
        }
    }
}


// (Re)start the game
void game::run() {
	// Was the pause key pressed in the last frame?
	bool pause_key_active{ false };

	while (game_window.isOpen())
	{
		// Clear the screen
		game_window.clear(sf::Color::Black);

		// Check for any events since the last loop iteration
		sf::Event event;

		// If the user pressed "Escape", or clicked on "close", we close the window
		// This will terminate the program
		while (game_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				game_window.close();
			}
		}

		// Check for user input
		// If the user presses "Escape", we jump out of the loop
		// This will terminate the program
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			break;
		}

		// If the user presses "P", we pause/unpause the game
		// To prevent repeated use, we ignore it if it was pressed on the last iteration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			reset();
		}

		// If the game is not running, the entities are not updated
		// They are redrawn only if the game is paused
		if (state == game_state::paused) {
			// Display the graphics
			manager.draw(game_window);
		}


		if (state != game_state::running)
		{
			switch (state)
			{
			case game_state::paused:
				text_state.setString("   Paused   ");
				break;
			case game_state::game_over:
				text_state.setString(" Game Over! ");
				break;
			case game_state::player_won:
				text_state.setString("Player Wins!");
				break;
			default:
				break;
			}

			game_window.draw(text_state);
			game_window.draw(text_lives);
		}
		else
		{
			// If there are no remaining balls on the screen
			if (manager.get_all<ball>().empty())
			{
				// Spawn a new one and reduce the player's remaining lives
				manager.create<ball>(constants::window_width / 2.0f, constants::window_height / 2.0f);
				--lives;

				state = game_state::paused;
			}

			// If there are no remaining bricks on the screen, the player has won
			if (manager.get_all<brick>().empty())
			{
				state = game_state::player_won;
			}

			// If the player used up all of their lives, the game is over
			if (lives <= 0)
			{
				state = game_state::game_over;
			}

			// Update number of lives
			text_lives.setString("Lives: " + std::to_string(lives));

			// Calculate the updated graphics
			manager.update();

			// For every ball, call a function which
			//    For every brick, call a function which
			//         Calls handle_collision with the ball and the brick as arguments
			manager.apply_all<ball>([this](auto& the_ball) {
				manager.apply_all<brick>([&the_ball](auto& the_brick) {
					handle_collision(the_ball, the_brick);
					});
				});

			// Paddle interaction
			manager.apply_all<ball>([this](auto& the_ball) {
				manager.apply_all<paddle>([&the_ball](auto& the_paddle) {
					handle_collision(the_ball, the_paddle);
					});
				});
			manager.refresh();

			// Display the updated graphics
			manager.draw(game_window);
		}
		game_window.display();
	}
}