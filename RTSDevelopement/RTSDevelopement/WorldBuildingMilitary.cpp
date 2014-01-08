#include "WorldBuildingMilitary.h"

WorldBuildingMilitary::WorldBuildingMilitary(WorldBuildingMilitary::MilitaryBuildingType _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldBuilding(WorldBuilding::BuildingType::MILITARY, _position, _size, _maxHP, _currentHP),
	m_MilitaryBuildingType(_type)
{
}

WorldBuildingMilitary::~WorldBuildingMilitary(void)
{
}


WorldBuildingMilitary::MilitaryBuildingType WorldBuildingMilitary::getMilitaryBuildingType(void)
{
	return m_MilitaryBuildingType;
}