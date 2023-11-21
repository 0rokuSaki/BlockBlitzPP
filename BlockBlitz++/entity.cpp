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


float entity::left() const noexcept
{
	auto box = this->get_bounding_box();
	return this->x() - box.width / 2.0f;
}


float entity::right() const noexcept
{
	auto box = this->get_bounding_box();
	return this->x() + box.width / 2.0f;
}


float entity::top() const noexcept
{
	auto box = this->get_bounding_box();
	return this->y() - box.height / 2.0f;
}


float entity::bottom() const noexcept
{
	auto box = this->get_bounding_box();
	return this->y() + box.height / 2.0f;
}


void entity::destroy() noexcept
{
	this->destroyed = true;
}


bool entity::is_destroyed() const noexcept
{
	return this->destroyed;
}
