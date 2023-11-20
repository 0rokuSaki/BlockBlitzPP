#include "ball.h"


sf::Texture ball::texture;


ball::ball(float x, float y)
{
	// Load the texture
	this->texture.loadFromFile("ball.png");
	this->sprite.setTexture(this->texture);

	// Set the initial position and velocity of the ball
	// Use (x, y) for the initial position of the ball
	this->sprite.setPosition(x, y);
	this->velocity = { constants::ball_speed, constants::ball_speed };

	// By default, operations are relative to the sprite's top left corner
	// Make them relative to the sprite's center
	this->sprite.setOrigin(get_center());
}


// Compute the ball's new position
void ball::update()
{
	// Move the position of the ball
	this->sprite.move(velocity);

	// Check if the ball moved off the side of the window
	// If so, change the sign of the appropriate velocity
	if (x() < 0 or x() > constants::window_width)
	{
		this->velocity.x *= -1;
	}
	if (y() < 0 or y() > constants::window_height)
	{
		this->velocity.y *= -1;
	}
}


void ball::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}


void ball::move_up() noexcept
{
	this->velocity.y = -constants::ball_speed;
}


void ball::move_down() noexcept
{
	this->velocity.y = constants::ball_speed;
}


void ball::move_left() noexcept
{
	this->velocity.x = -constants::ball_speed;
}


void ball::move_right() noexcept
{
	this->velocity.x = constants::ball_speed;
}