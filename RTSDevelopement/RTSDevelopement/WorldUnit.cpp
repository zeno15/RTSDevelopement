#include "WorldUnit.h"


WorldUnit::WorldUnit(Tile::Type _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObject(WorldObject::ObjectType::UNIT, _position, _size, _maxHP, _currentHP),
	m_WorldUnitRotation(0.0f),
	m_WorldUnitType(_type),
	m_WorldUnitDirectionToMove(MovementDirection::NONE)
{
}

WorldUnit::~WorldUnit(void)
{
}


void WorldUnit::move(MovementDirection _dir)
{
	m_WorldUnitDirectionToMove = _dir;
}

Tile::Type WorldUnit::getType(void)
{
	return m_WorldUnitType;
}

float WorldUnit::getAngleFromDirection(MovementDirection _dir)
{
	switch (_dir)
	{
	case (NORTH):
		return 0.0f;
	case (NORTH_EAST):
		return 45.0f;
	case (EAST):
		return 90.0f;
	case (SOUTH_EAST):
		return 135.0f;
	case (SOUTH):
		return 180.0f;
	case (SOUTH_WEST):
		return 225.0f;
	case (WEST):
		return 270.0f;
	case (NORTH_WEST):
		return 315.0f;
	default:
		return 0.0f;
	};
}
sf::Vector2f WorldUnit::getUnitVectorFromDirection(MovementDirection _dir)
{
	switch (_dir)
	{
	case (NORTH):
		return sf::Vector2f(+ 0.0f, - 1.0f);
	case (NORTH_EAST):
		return sf::Vector2f(+ 1.0f, - 1.0f);
	case (EAST):
		return sf::Vector2f(+ 1.0f, + 0.0f);
	case (SOUTH_EAST):
		return sf::Vector2f(+ 1.0f, + 1.0f);
	case (SOUTH):
		return sf::Vector2f(+ 0.0f, + 1.0f);
	case (SOUTH_WEST):
		return sf::Vector2f(- 1.0f, + 1.0f);
	case (WEST):
		return sf::Vector2f(- 1.0f, + 0.0f);
	case (NORTH_WEST):
		return sf::Vector2f(- 1.0f, - 1.0f);
	default:
		return sf::Vector2f(+ 0.0f, + 0.0f);
	};
}

float WorldUnit::getMass(void)
{
	return m_WorldUnitMass;
}
float WorldUnit::getMaxSpeed(void)
{
	return m_WorldUnitMaxSpeed;
}
float WorldUnit::getSightDistance(void)
{
	return m_WorldUnitSightDistance;
}
float WorldUnit::getTooCloseDistance(void)
{
	return m_WorldUnitTooCloseDistance;
}
float WorldUnit::getMaxForce(void)
{
	return m_WorldUnitMaxForce;
}
float WorldUnit::getWanderCircleRadius(void)
{
	return m_WorldUnitWanderCircleRadius;
}
float WorldUnit::getSlowingDistance(void)
{
	return m_WorldUnitSlowingDistance;
}
float WorldUnit::getAngleChange(void)
{
	return m_WorldUnitRotationChange;
}
float WorldUnit::getRadius(void)
{
	return length(m_WorldObjectSize) / 2.0f;
}

float WorldUnit::getRotation(void)
{
	return m_WorldUnitRotation;
}
unsigned int WorldUnit::getWaypointIndex(void)
{
	return m_WorldUnitWaypointIndex;
}
sf::Vector2f WorldUnit::getVelocity(void)
{
	return m_WorldUnitVelocity;
}
sf::Vector2f WorldUnit::getPosition(void)
{
	return m_WorldObjectPosition;
}

void WorldUnit::setRotation(float _rotation)
{
	m_WorldUnitRotation = _rotation;
}
void WorldUnit::setWaypointIndex(unsigned int _index)
{
	m_WorldUnitWaypointIndex = _index;
}
void WorldUnit::setVelocity(sf::Vector2f _vel)
{
	m_WorldUnitVelocity = _vel;
}
void WorldUnit::setPosition(sf::Vector2f _pos)
{
	m_WorldObjectPosition = _pos;
}