#pragma once


#include <SFML/Graphics.hpp>


// Abstract base class to represent any graphical entity on the screen
class entity
{
protected:
	sf::Sprite sprite;

	// Boolean member tracks the entity's status
	bool destroyed{ false };

public:
	// Pure virtual functions
	// Concrete graphical entities must implement these functions

	// The update member function will compute the new position, appearance, etc of the entity
	virtual void update() = 0;

	// The draw member function will cause the entity to be displayed on the window
	virtual void draw(sf::RenderWindow& rw) = 0;

	// Getter function for the sprite's bounding box
	sf::FloatRect get_bounding_box() const noexcept;

	// Getter function for the sprite's center coordinates
	sf::Vector2f get_center() const noexcept;

	// Getter functions for the sprite's position
	float x() const noexcept;
	float y() const noexcept;

	// Helper functions to get the edges of the sprite
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;

	// Helper functions for the state of the entity
	void destroy() noexcept;
	bool is_destroyed() const noexcept;

	// Virtual d'tor
	virtual ~entity() {};
};


// Abstract base class to represent graphical entities which can move around the screen
class moving_entity :
	public entity
{
protected:
	// SFML vector to store the object's velocity
	// This is the distance the ball moves between screen updates
	sf::Vector2f velocity;


public:
	// Helper functions to change the sprite's directions
	virtual void move_up() noexcept = 0;
	virtual void move_down() noexcept = 0;
	virtual void move_left() noexcept = 0;
	virtual void move_right() noexcept = 0;
};

