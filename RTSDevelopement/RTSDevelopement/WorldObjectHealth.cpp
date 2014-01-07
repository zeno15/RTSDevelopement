#include "WorldObjectHealth.h"

#include <iostream>

WorldObjectHealth::WorldObjectHealth(sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _startPerc/* = 1.0f*/) :
	m_Size(_size),
	m_Selected(false),
	m_MaxHP(_maxHP),
	m_CurrentHP((int)(_maxHP * _startPerc)),
	m_SelectedCorners(sf::Lines, 16),
	m_HealthBar(sf::Quads, 8)
{
	updateHealthPosition(_position);
}

WorldObjectHealth::~WorldObjectHealth(void)
{
}


bool WorldObjectHealth::damage(int _amount)
{
	if (_amount == 0) return false;

	m_CurrentHP -= _amount;

	m_CurrentHP = m_CurrentHP > m_MaxHP ? m_MaxHP : (m_CurrentHP < 0 ? 0 : m_CurrentHP);

	updateHealthBar();

	return m_CurrentHP == 0;
}

void WorldObjectHealth::updateHealthPosition(sf::Vector2f _position)
{
	sf::Vector2f offset = m_Size / 8.0f;

	m_SelectedCorners[0].position  = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[1].position  = sf::Vector2f(_position.x - m_Size.x / 2.0f + offset.x,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[2].position  = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[3].position  = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f + offset.y);

	m_SelectedCorners[4].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[5].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f - offset.x,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[6].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f);
	m_SelectedCorners[7].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y - m_Size.y / 2.0f + offset.y);

	m_SelectedCorners[8].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[9].position  = sf::Vector2f(_position.x + m_Size.x / 2.0f - offset.x,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[10].position = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[11].position = sf::Vector2f(_position.x + m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f - offset.y);

	m_SelectedCorners[12].position = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[13].position = sf::Vector2f(_position.x - m_Size.x / 2.0f + offset.x,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[14].position = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f);
	m_SelectedCorners[15].position = sf::Vector2f(_position.x - m_Size.x / 2.0f,
												  _position.y + m_Size.y / 2.0f - offset.y);

	updateHealthBar();

}

bool WorldObjectHealth::select(void)
{
	bool temp = m_Selected;
	m_Selected = true;
	return temp;
}
bool WorldObjectHealth::deselect(void)
{
	bool temp = m_Selected;
	m_Selected = false;
	return temp;
}

void WorldObjectHealth::updateHealthBar(void)
{
	m_HealthBar[0].color    = sf::Color(175, 175, 175, 255);
	m_HealthBar[0].position = sf::Vector2f(m_SelectedCorners[0].position.x,
										   m_SelectedCorners[0].position.y - 7.0f);
	m_HealthBar[1].color    = sf::Color(175, 175, 175, 255);
	m_HealthBar[1].position = sf::Vector2f(m_HealthBar[0].position.x + m_Size.x,
										   m_HealthBar[0].position.y);
	m_HealthBar[2].color    = sf::Color(175, 175, 175, 255);
	m_HealthBar[2].position = sf::Vector2f(m_HealthBar[1].position.x,
										   m_HealthBar[1].position.y + 6.0f);
	m_HealthBar[3].color    = sf::Color(175, 175, 175, 255);
	m_HealthBar[3].position = sf::Vector2f(m_HealthBar[0].position.x,
										   m_HealthBar[0].position.y + 6.0f);

	float percentage = ((float)(m_CurrentHP) / (float)(m_MaxHP));
	
	sf::Color healthColour = percentage < 0.5f ? (percentage < 0.25f ? (sf::Color::Red) : sf::Color::Yellow) : sf::Color::Green;
	
	m_HealthBar[4].color    = healthColour;
	m_HealthBar[4].position = sf::Vector2f(m_HealthBar[0].position.x + 1.0f,
										   m_HealthBar[0].position.y + 1.0f);
	m_HealthBar[5].color    = healthColour;
	m_HealthBar[5].position = sf::Vector2f(m_HealthBar[4].position.x + percentage * (m_Size.x - 2.0f),
										   m_HealthBar[4].position.y);
	m_HealthBar[6].color    = healthColour;
	m_HealthBar[6].position = sf::Vector2f(m_HealthBar[4].position.x + percentage * (m_Size.x - 2.0f),
										   m_HealthBar[4].position.y + 4.0f);
	m_HealthBar[7].color    = healthColour;
	m_HealthBar[7].position = sf::Vector2f(m_HealthBar[4].position.x,
										   m_HealthBar[4].position.y + 4.0f);
}