#include "WorldBuilding.h"

WorldBuilding::WorldBuilding(BuildingType _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObject(WorldObject::ObjectType::BUILDING, _position, _size, _maxHP, _currentHP),
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