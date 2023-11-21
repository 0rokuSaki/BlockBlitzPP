#include "brick.h"


sf::Texture brick::texture;


brick::brick(float x, float y) : entity()
{
	// Load the texture
	this->texture.loadFromFile("brick01.png");
	this->sprite.setTexture(this->texture);

	// Set the initial position and velocity of the brick
	// Use (x, y) for the initial position of the brick
	this->sprite.setPosition(x, y);

	// By default, operations are relative to the sprite's top left corner
	// Make them relative to the sprite's centre
	this->sprite.setOrigin(get_center());
}


void brick::update()
{
	// Empty
}


void brick::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}