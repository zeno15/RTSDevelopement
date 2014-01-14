#include "WorldBuildingMilitaryTest.h"

#include "Game.h"

#include <iostream>

WorldBuildingMilitaryTest::WorldBuildingMilitaryTest(sf::Vector2f _position) :
	WorldBuildingMilitary(MilitaryBuildingType::TEST, _position, sf::Vector2f(64.0f, 96.0f), 1200),
	m_Vertices(sf::Quads, 4)
{
	updateCollisions();


	m_Vertices[0].position = sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f, 
										  m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f);
	m_Vertices[0].color    = sf::Color(255, 255, 255, 155);

	m_Vertices[1].position = sf::Vector2f(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f, 
										  m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f);
	m_Vertices[1].color    = sf::Color(255, 255, 255, 155);

	m_Vertices[2].position = sf::Vector2f(m_WorldObjectPosition.x + m_WorldObjectSize.x / 2.0f, 
										  m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f);
	m_Vertices[2].color    = sf::Color(255, 255, 255, 155);

	m_Vertices[3].position = sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f, 
										  m_WorldObjectPosition.y + m_WorldObjectSize.y / 2.0f);
	m_Vertices[3].color    = sf::Color(255, 255, 255, 155);


	updateHealthPosition(m_WorldObjectPosition);
}

WorldBuildingMilitaryTest::~WorldBuildingMilitaryTest(void)
{
	//~ Remove from collision grid
}


void WorldBuildingMilitaryTest::update(sf::Time _delta)
{
}
void WorldBuildingMilitaryTest::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Vertices,				_states);

	if (m_Selected)
	{
		_target.draw(m_HealthBar,			_states);
		_target.draw(m_SelectedCorners,		_states);
	}
}