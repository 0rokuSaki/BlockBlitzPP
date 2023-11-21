#include "entity_manager.h"


// Function to scan all entities and clean up the destroyed ones
void entity_manager::refresh()
{
	// We must clean up the alias pointers first, to avoid dangling pointers
	// We simply remove them from their vector
	for (auto& [type, alias_vector] : grouped_entities)
	{
		auto it = std::remove_if(std::begin(alias_vector), std::end(alias_vector),
			[](const auto& p) {return p->is_destroyed(); }
		);
		alias_vector.erase(it, std::end(alias_vector));
	}

	// Now we can safely destroy the objects, now that there are no aliases to them
	auto it = std::remove_if(std::begin(all_entities), std::end(all_entities),
		[](const auto& p) {return p->is_destroyed(); }
	);
	all_entities.erase(it, std::end(all_entities));
}


// Function to destroy all entities
void entity_manager::clear()
{
	// Again, we must clean up the alias pointers first
	grouped_entities.clear();
	all_entities.clear();
}


// Function to update all the entities
void entity_manager::update()
{
	for (auto& e : all_entities)
	{
		e->update();
	}
}


// Function to update make all the entities draw themselves
void entity_manager::draw(sf::RenderWindow& rw)
{
	for (auto& e : all_entities)
	{
		e->draw(rw);
	}
}