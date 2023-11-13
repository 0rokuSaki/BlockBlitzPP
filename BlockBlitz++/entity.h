#pragma once


#include <SFML/Graphics.hpp>


// Abstract base class to represent any graphical entity on the screen
class entity
{
protected:
	sf::Sprite sprite;


public:
	// Pure virtual functions
	// Concrete graphical entities must implement these functions

	// The update member function will compute the new position, appearance, etc of the entity
	virtual void update() = 0;

	// The draw member function will cause the entity to be displayed on the window
	virtual void draw(sf::RenderWindow& rw) = 0;
};

