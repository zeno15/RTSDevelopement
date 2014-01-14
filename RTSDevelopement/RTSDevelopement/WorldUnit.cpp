#include "WorldUnit.h"


WorldUnit::WorldUnit(Tile::Type _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP/* = 1.0f*/) :
	WorldObject(WorldObject::ObjectType::UNIT, _position, _size, _maxHP, _currentHP),
	m_WorldUnitSpeed(64.0f),
	m_WorldUnitRotationSpeed(360.0f),
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
void WorldUnit::updateMovement(sf::Time _delta)
{
if (m_WorldUnitDirectionToMove != MovementDirection::NONE)
	{
		//~ We have to rotate the unit or move it
		if (m_WorldUnitRotation != getAngleFromDirection(m_WorldUnitDirectionToMove))
		{
			//~ We need to rotate it further before it moves
			float rot = m_WorldUnitRotation - getAngleFromDirection(m_WorldUnitDirectionToMove);

			if (m_WorldUnitRotationSpeed * _delta.asSeconds() > fabsf(rot))
			{
				m_WorldUnitRotation = getAngleFromDirection(m_WorldUnitDirectionToMove);
			}
			else
			{
				m_WorldUnitRotation += m_WorldUnitRotationSpeed * _delta.asSeconds() * (rot > 0.0f ? - 1.0f : + 1.0f);
				if (m_WorldUnitRotation >= 360.0f) m_WorldUnitRotation -= 360.0f;
			}

		}
		else
		{
			//~ Unit is facing correct direction, now need to move
			sf::Vector2f unitVector = getUnitVectorFromDirection(m_WorldUnitDirectionToMove);

			sf::Vector2f movement = unitVector * m_WorldUnitSpeed * _delta.asSeconds();



			if (fabsf(movement.x) > fabsf(m_WorldObjectPosition.x - m_WorldUnitDestination.x))
			{
				m_WorldObjectPosition.x = m_WorldUnitDestination.x;
			}
			else
			{
				m_WorldObjectPosition.x += movement.x;
			}
			if (fabsf(movement.y) > fabsf(m_WorldObjectPosition.y - m_WorldUnitDestination.y))
			{
				m_WorldObjectPosition.y = m_WorldUnitDestination.y;
			}
			else
			{
				m_WorldObjectPosition.y += movement.y;
			}

			if (m_WorldObjectPosition == m_WorldUnitDestination)
			{
				move(MovementDirection::NONE);
			}

			updatePosition();
		}

	}
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