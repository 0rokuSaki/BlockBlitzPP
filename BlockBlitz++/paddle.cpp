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
	// Move the position of the paddle
	this->sprite.move(velocity);
}


void paddle::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}