#include "entity.h"


sf::FloatRect entity::get_bounding_box() const noexcept
{
	return this->sprite.getGlobalBounds();
}


sf::Vector2f entity::get_center() const noexcept
{
	auto box = this->get_bounding_box();
	return { box.width / 2.0f, box.height / 2.0f };
}


float entity::x() const noexcept
{
	return this->sprite.getPosition().x;
}


float entity::y() const noexcept
{
	return this->sprite.getPosition().y;
}
