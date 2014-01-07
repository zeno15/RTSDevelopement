#include "WorldUnitTriangleTest.h"


WorldUnitTriangleTest::WorldUnitTriangleTest(sf::Vector2f _position) :
	WorldUnit(Tile::Type::HEAVY_VEHICLE, _position, sf::Vector2f(32.0f, 32.0f)),
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
}	
void WorldUnitTriangleTest::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Body,				_states);
}