#include "brick.h"


// Initialize static data
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


void brick::set_strength(int s) noexcept
{
	strength = s;
}


void brick::weaken() noexcept
{
	--strength;
}


bool brick::is_too_weak() noexcept
{
	return strength <= 0;
}


void brick::update()
{
	// Change the color of the brick, depending on how many times it has been hit
	float scale = 255.0f / constants::brick_strength;
	sf::Uint8 opacity = static_cast<int>(scale) * strength;

	// The color is a shade of green depending on the brick's strength
	const sf::Color brick_colour{ 0, 255, 0, opacity };

	// Set the color
	sprite.setColor(brick_colour);
}


void brick::draw(sf::RenderWindow& rw)
{
	// Ask the window to draw the sprite for us
	rw.draw(this->sprite);
}