#pragma once

#include "constants.h"
#include "entity_manager.h"

class game
{
private:
	// Create the game's window using an object of class RenderWindow
	// The constructor takes an SFML 2D vector with the window dimensions
	// and an std::string with the window title
	// The SFML code is in the sf namespace
	sf::RenderWindow game_window{ { constants::window_width, constants::window_height },
		"BlockBlitz++" };

	// Instead of embedding every entity in the game class, use an entity_manager
	entity_manager manager;

	// Use SFML text and font to communicate with the player
	sf::Font verdana;
	sf::Text text_state, text_lives;

	// Enum with allowd values for game state
	enum class game_state { paused, game_over, running, player_won };

	// Member to store the current state of the game
	game_state state{ game_state::running };

	// How many lives does the player have left?
	int lives{ constants::player_lives };

public:
	// Constructor
	game();

	// Reinitialize the game
	void reset();

	// Game loop
	void run();
};

