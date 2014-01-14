#include "WorldUnitTriangleTest.h"

WorldUnitTriangleTest::WorldUnitTriangleTest(sf::Vector2f _position, float _currentHP/* = 1.0f*/) :
	WorldUnit(Tile::Type::HEAVY_VEHICLE, _position, sf::Vector2f(32.0f, 32.0f), 100),
	m_Body(sf::Triangles, 3)
{
	updatePosition();
}

WorldUnitTriangleTest::~WorldUnitTriangleTest(void)
{
}


void WorldUnitTriangleTest::update(sf::Time _delta)
{
	if (m_WorldUnitDirectionToMove == MovementDirection::NONE)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			move(MovementDirection::NORTH);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(0.0f, - TILESIZE_f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			move(MovementDirection::SOUTH);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(0.0f, + TILESIZE_f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move(MovementDirection::WEST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(- TILESIZE_f, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move(MovementDirection::EAST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(+ TILESIZE_f, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			move(MovementDirection::NORTH_WEST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(- TILESIZE_f, - TILESIZE_f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			move(MovementDirection::NORTH_EAST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(+ TILESIZE_f, - TILESIZE_f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			move(MovementDirection::SOUTH_WEST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(- TILESIZE_f, + TILESIZE_f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			move(MovementDirection::SOUTH_EAST);
			m_WorldUnitDestination = m_WorldObjectPosition + sf::Vector2f(+ TILESIZE_f, + TILESIZE_f);
		}
	}



	updateMovement(_delta);	

	updateCollisions();

	updateHealthPosition(m_WorldObjectPosition);
}	
void WorldUnitTriangleTest::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.transform.rotate(m_WorldUnitRotation, m_WorldObjectPosition);

	_target.draw(m_Body,					_states);

	_states.transform = sf::Transform();

	if (m_Selected)
	{
		_target.draw(m_HealthBar,			_states);
		_target.draw(m_SelectedCorners,		_states);
	}
}

void WorldUnitTriangleTest::updatePosition(void)
{
	m_Body[0].position = sf::Vector2f(m_WorldObjectPosition.x - 16.0f,
										m_WorldObjectPosition.y + 16.0f);
	m_Body[1].position = sf::Vector2f(m_WorldObjectPosition.x + 16.0f,
										m_WorldObjectPosition.y + 16.0f);
	m_Body[2].position = sf::Vector2f(m_WorldObjectPosition.x,
										m_WorldObjectPosition.y - 16.0f);
}