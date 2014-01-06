#include "WorldBuildingFootprint.h"

WorldBuildingFootprint::WorldBuildingFootprint(sf::Vector2f _position, sf::Vector2f _size) :
	WorldObject(WorldObject::ObjectType::FOOTPRINT, _position, _size)
{
	//~ Texture start 0, 384
	//~ Have world buildings create their own footprint?
}


WorldBuildingFootprint::~WorldBuildingFootprint(void)
{
}


void WorldBuildingFootprint::update(sf::Time _delta)
{
}
void WorldBuildingFootprint::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
}