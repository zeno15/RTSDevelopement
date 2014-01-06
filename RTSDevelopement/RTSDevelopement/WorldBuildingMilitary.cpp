#include "WorldBuildingMilitary.h"

WorldBuildingMilitary::WorldBuildingMilitary(WorldBuildingMilitary::MilitaryBuildingType _type, sf::Vector2f _position, sf::Vector2f _size) :
	WorldBuilding(WorldBuilding::BuildingType::MILITARY, _position, _size),
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