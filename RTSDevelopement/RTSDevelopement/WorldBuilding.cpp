#include "WorldBuilding.h"

#include "Game.h"

WorldBuilding::WorldBuilding(BuildingType _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObject(WorldObject::ObjectType::BUILDING, _position, _size, _maxHP, _currentHP),
	m_BuildingType(_type)
{
	for (unsigned int i = (unsigned int)(m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i < (unsigned int)(m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i += 1)
	{
		for (unsigned int j = (unsigned int)(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j < (unsigned int)(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j += 1)
		{
			sWorld.m_PathfindingGrid.addObstacle(j, i, Tile::Type::INFANTRY);
			sWorld.m_PathfindingGrid.addObstacle(j, i, Tile::Type::LIGHT_VEHICLE);
			sWorld.m_PathfindingGrid.addObstacle(j, i, Tile::Type::HEAVY_VEHICLE);
			sWorld.m_PathfindingGrid.addObstacle(j, i, Tile::Type::NAVAL);
		}
	}
}

WorldBuilding::~WorldBuilding(void)
{
	for (unsigned int i = (unsigned int)(m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i < (unsigned int)(m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f) / TILESIZE_u; i += 1)
	{
		for (unsigned int j = (unsigned int)(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j < (unsigned int)(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f) / TILESIZE_u; j += 1)
		{
			sWorld.m_PathfindingGrid.removeObstacle(j, i, Tile::Type::INFANTRY);
			sWorld.m_PathfindingGrid.removeObstacle(j, i, Tile::Type::LIGHT_VEHICLE);
			sWorld.m_PathfindingGrid.removeObstacle(j, i, Tile::Type::HEAVY_VEHICLE);
			sWorld.m_PathfindingGrid.removeObstacle(j, i, Tile::Type::NAVAL);
		}
	}
}


WorldBuilding::BuildingType WorldBuilding::getBuildingType(void)
{
	return m_BuildingType;
}
