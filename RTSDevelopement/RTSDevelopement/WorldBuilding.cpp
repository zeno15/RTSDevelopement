#include "WorldBuilding.h"

WorldBuilding::WorldBuilding(BuildingType _type, sf::Vector2f _position, sf::Vector2f _size) :
	WorldObject(WorldObject::ObjectType::BUILDING, _position, _size),
	m_BuildingType(_type)
{
}

WorldBuilding::~WorldBuilding(void)
{
}


WorldBuilding::BuildingType WorldBuilding::getBuildingType(void)
{
	return m_BuildingType;
}