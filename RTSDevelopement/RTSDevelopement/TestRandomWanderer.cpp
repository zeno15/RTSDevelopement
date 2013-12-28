#include "TestRandomWanderer.h"

#include <cstdlib>

#include "Game.h"

#define TESTWANDERER_DEFAULTMOVETIME		sf::Time(sf::seconds(1.0f))

TestRandomWanderer::TestRandomWanderer(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size) :
	WorldObject(_type, _position, _size),
	m_CurrentMovementTime(TESTWANDERER_DEFAULTMOVETIME),
	m_MovementDirection(WorldObject::MovementDirection::NONE),
	m_Rectangle(_size)
{
	m_WorldObjectSpeed = 100.0f;

	m_Rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	m_Rectangle.setOrigin(_size.x / 2.0f, _size.y / 2.0f);
	m_Rectangle.setPosition(_position);

}

TestRandomWanderer::~TestRandomWanderer(void)
{
}


void TestRandomWanderer::update(sf::Time _delta)
{
	m_CurrentMovementTime -= _delta;

	if (m_CurrentMovementTime < sf::Time::Zero)
	{
		m_CurrentMovementTime = sf::Time::Zero;

		int random = rand() % (WorldObject::MovementDirection::NUM_DIRECTIONS * 2) - WorldObject::MovementDirection::NUM_DIRECTIONS;

		if (random >= 0)
		{
			m_MovementDirection = (WorldObject::MovementDirection)random;
			m_CurrentMovementTime = TESTWANDERER_DEFAULTMOVETIME;
		}
	}
	else
	{
		if (m_WorldObjectPosition.x < m_WorldObjectSize.x / 2.0f)
		{
			m_MovementDirection = EAST;
		}
		else if (m_WorldObjectPosition.y < m_WorldObjectSize.y / 2.0f)
		{
			m_MovementDirection = SOUTH;
		}
		move(m_MovementDirection, _delta);
	}
}	
void TestRandomWanderer::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Rectangle,			_states);
}

void TestRandomWanderer::move(WorldObject::MovementDirection _dir, sf::Time _delta)
{
	m_WorldObjectPosition += getUnitVector(_dir) * _delta.asSeconds() * m_WorldObjectSpeed;
	m_Rectangle.setPosition(m_WorldObjectPosition);
	updateCollisions();
}

sf::Vector2f TestRandomWanderer::getUnitVector(WorldObject::MovementDirection _dir)
{
	sf::Vector2f unit = sf::Vector2f();

	if (_dir == NORTH_WEST || _dir == NORTH || _dir == NORTH_EAST)
	{
		unit.y = - 1.0f;
	}
	else if (_dir == SOUTH_WEST || _dir == SOUTH || _dir == SOUTH_EAST)
	{
		unit.y = + 1.0f;
	}

	if (_dir == NORTH_WEST || _dir == WEST || _dir == SOUTH_WEST)
	{
		unit.x = - 1.0f;
	}
	else if (_dir == NORTH_EAST || _dir == EAST || _dir == SOUTH_EAST)
	{
		unit.x = + 1.0f;
	}

	return unit;
}




