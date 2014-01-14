#include "WorldBuilding.h"

#include "Game.h"

WorldBuilding::WorldBuilding(BuildingType _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObject(WorldObject::ObjectType::BUILDING, _position, _size, _maxHP, _currentHP),
	m_BuildingType(_type)
{
	Tile::Type pathfindType;
	switch (m_BuildingType)
	{
	case (BuildingType::MILITARY):
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	case (BuildingType::TEST):
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	default:
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	};

	for (unsigned int i = (unsigned int)(m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i < (unsigned int)(m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i += 1)
	{
		for (unsigned int j = (unsigned int)(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j < (unsigned int)(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j += 1)
		{
			sWorld.m_PathfindingGrid.addObstacle(j, i, pathfindType);
		}
	}
}

WorldBuilding::~WorldBuilding(void)
{
	Tile::Type pathfindType;
	switch (m_BuildingType)
	{
	case (BuildingType::MILITARY):
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	case (BuildingType::TEST):
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	default:
		pathfindType = Tile::Type::HEAVY_VEHICLE;
	};

	for (unsigned int i = (unsigned int)(m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i < (unsigned int)(m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i += 1)
	{
		for (unsigned int j = (unsigned int)(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j < (unsigned int)(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j += 1)
		{
			sWorld.m_PathfindingGrid.removeObstacle(j, i, pathfindType);
		}
	}
}


WorldBuilding::BuildingType WorldBuilding::getBuildingType(void)
{
	return m_BuildingType;
}
