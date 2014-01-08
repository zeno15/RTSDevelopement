#include "WorldObject.h"

#include "Game.h"

WorldObject::WorldObject(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObjectHealth(_position, _size, _maxHP, _currentHP),
	m_WorldObjectType(_type),
	m_WorldObjectPosition(_position),
	m_WorldObjectSize(_size)
{
}

WorldObject::~WorldObject(void)
{
	for (unsigned int i = 0; i < m_TouchingCells.size(); i += 1)
	{
		m_TouchingCells.at(i)->removeWorldObject(this);
	}
}


WorldObject::ObjectType WorldObject::getType(void)
{
	return m_WorldObjectType;
}

sf::Vector2f WorldObject::getPosition(void)
{
	return m_WorldObjectPosition;
}
sf::Vector2f WorldObject::getSize(void)
{
	return m_WorldObjectSize;
}
sf::FloatRect WorldObject::getBounds(void)
{
	return sf::FloatRect(m_WorldObjectPosition - m_WorldObjectSize / 2.0f, m_WorldObjectSize);
}

void WorldObject::kill(void)
{
	m_Alive = false;
}
bool WorldObject::isAlive(void)
{
	return m_Alive;
}

void WorldObject::updateCollisions(void)
{
	sWorld.m_CollisionGrid.updateTouchingCells(this);
}

std::vector<CollisionCell *> *WorldObject::getTouchingCells(void)
{
	return &m_TouchingCells;
}