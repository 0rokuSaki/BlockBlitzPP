#include "background.h"


sf::Texture background::texture;


background::background(float x, float y) :
	entity()
{
	// Load the texture
	this->texture.loadFromFile("background.jpg");

	this->sprite.setTexture(this->texture);

	// Set the initial position of the background
	this->sprite.setPosition(x, y);
}


// Compute the background's new position
void background::update()
{
	// Nothing to do here
}


void background::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}