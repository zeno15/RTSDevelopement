#include "WorldUnit.h"


WorldUnit::WorldUnit(Tile::Type _type, sf::Vector2f _position, sf::Vector2f _size) :
	WorldObject(WorldObject::ObjectType::UNIT, _position, _size),
	m_WorldUnitSpeed(75.0f),
	m_WorldUnitType(_type)
{
}

WorldUnit::~WorldUnit(void)
{
}


void WorldUnit::move(MovementDirection _dir)
{
	m_WorldUnitDirectionToMove = _dir;
}

void WorldUnit::setSpeed(float _speed)
{
	m_WorldUnitSpeed = _speed;
}
float WorldUnit::getSpeed(void)
{
	return m_WorldUnitSpeed;
}

Tile::Type WorldUnit::getType(void)
{
	return m_WorldUnitType;
}