#include "WorldUnitTriangleTest.h"

WorldUnitTriangleTest::WorldUnitTriangleTest(sf::Vector2f _position, float _currentHP/* = 1.0f*/) :
	WorldUnit(Tile::Type::HEAVY_VEHICLE, _position, sf::Vector2f(32.0f, 32.0f), 100),
	m_Body(sf::Triangles, 3)
{
	m_WorldUnitMaxSpeed = 50.0f;
	m_WorldUnitMass = 25.0f;
	m_WorldUnitSightDistance = 60.0f;
	m_WorldUnitTooCloseDistance = 20.0f;
	m_WorldUnitMaxForce = 50.0f;
	m_WorldUnitWanderCircleRadius = 10.0f;
	m_WorldUnitSlowingDistance = 32.0f;
	m_WorldUnitRotationChange = 45.0f;

	m_WorldUnitWaypointIndex = 0;

	updatePosition();
}

WorldUnitTriangleTest::~WorldUnitTriangleTest(void)
{
}


void WorldUnitTriangleTest::update(sf::Time _delta)
{
	SteeringBehaviourUnitBase::update(_delta);

	updateCollisions();

	updatePosition();
	
	updateHealthPosition(m_WorldObjectPosition);
}	
void WorldUnitTriangleTest::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Body,					_states);

	if (m_Selected)
	{
		_target.draw(m_HealthBar,			_states);
		_target.draw(m_SelectedCorners,		_states);
	}
}

void WorldUnitTriangleTest::updatePosition(void)
{
	m_Body[0].position = m_WorldObjectPosition + rotate(sf::Vector2f(- 16.0f, - 16.0f), getRotation());
	m_Body[1].position = m_WorldObjectPosition + rotate(sf::Vector2f(- 16.0f, + 16.0f), getRotation());
	m_Body[2].position = m_WorldObjectPosition + rotate(sf::Vector2f(+ 16.0f, +  0.0f), getRotation());
	m_Body[2].color = sf::Color::Red;
}