#include "ball.h"


ball::ball(float x, float y)
{
	// Load the texture
	this->texture.loadFromFile("ball.png");
	this->sprite.setTexture(this->texture);

	// Set the initial position and velocity of the ball
	// Use (x, y) for the initial position of the ball
	this->sprite.setPosition(x, y);
	this->velocity = { constants::ball_speed, constants::ball_speed };
}


// Compute the ball's new position
void ball::update()
{
	// Move the position of the ball
	this->sprite.move(velocity);
}


void ball::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}
