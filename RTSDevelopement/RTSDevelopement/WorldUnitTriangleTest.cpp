#include "WorldUnitTriangleTest.h"

WorldUnitTriangleTest::WorldUnitTriangleTest(sf::Vector2f _position, float _currentHP/* = 1.0f*/) :
	WorldUnit(Tile::Type::HEAVY_VEHICLE, _position, sf::Vector2f(32.0f, 32.0f), 100),
	m_Body(sf::Triangles, 3)
{
	m_Body[0].position = sf::Vector2f(_position.x - 16.0f,
									  _position.y + 16.0f);
	m_Body[1].position = sf::Vector2f(_position.x + 16.0f,
									  _position.y + 16.0f);
	m_Body[2].position = sf::Vector2f(_position.x,
									  _position.y - 16.0f);
}

WorldUnitTriangleTest::~WorldUnitTriangleTest(void)
{
}


void WorldUnitTriangleTest::update(sf::Time _delta)
{
	updateCollisions();

	updateHealthPosition(m_WorldObjectPosition);
}	
void WorldUnitTriangleTest::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Body,				_states);

	_target.draw(m_HealthBar,				_states);

	if (m_Selected)
	{
		_target.draw(m_SelectedCorners,		_states);
	}
}