#include "paddle.h"


paddle::paddle(float x, float y)
{
	// Load the texture
	this->texture.loadFromFile("paddle.png");
	this->sprite.setTexture(this->texture);

	// Set the initial position and velocity of the ball
	// Use (x, y) for the initial position of the ball
	this->sprite.setPosition(x, y);
	this->velocity = { 0.0f, 0.0f };
}


void paddle::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		this->x() < (constants::window_width - constants::paddle_width))
	{
		this->velocity.x = constants::paddle_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		     this->x() > 0)
	{
		this->velocity.x = -constants::paddle_speed;
	}

	// Move the position of the paddle
	this->sprite.move(velocity);

	// Reset velocity
	this->velocity.x = 0.0f;
}


void paddle::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}