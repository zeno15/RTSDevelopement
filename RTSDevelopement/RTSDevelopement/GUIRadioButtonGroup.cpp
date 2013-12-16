#include "GUIRadioButtonGroup.h"

#include "Game.h"

GUIRadioButtonGroup::GUIRadioButtonGroup(sf::Vector2f _position, float _separation, bool _horizontal/* = false*/) :
	m_Position(_position),
	m_Separation(_separation),
	m_Horizontal(_horizontal),
	m_ActiveButton(0u)
{
	sGame.m_InputManager.registerButton(sf::Mouse::Left);
}

GUIRadioButtonGroup::~GUIRadioButtonGroup(void)
{
	sGame.m_InputManager.unregisterButton(sf::Mouse::Left);

	for (GUIRadioButton *radio : m_RadioButtons)
	{
		delete radio;
	}
}


void GUIRadioButtonGroup::addRadioButton(std::string _text)
{
	sf::Vector2f position = sf::Vector2f(m_Position.x  +  m_Horizontal * (m_Separation * m_RadioButtons.size()), 
										 m_Position.y  + !m_Horizontal * (m_Separation * m_RadioButtons.size()));

	m_RadioButtons.push_back(new GUIRadioButton(position, _text, (m_RadioButtons.size() == 0)));
}

void GUIRadioButtonGroup::update(sf::Time _delta)
{
	if (!m_Update) return;
	for (unsigned int i = 0; i < m_RadioButtons.size(); i += 1)
	{
		m_RadioButtons.at(i)->update(_delta);

		if (m_RadioButtons.at(i)->isActive() && i != m_ActiveButton)
		{
			m_RadioButtons.at(m_ActiveButton)->reset();
			m_ActiveButton = i;
		}
	}
}
	
void GUIRadioButtonGroup::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;
	for (GUIRadioButton *radio : m_RadioButtons)
	{
		_target.draw(*radio,			_states);
	}
}

std::string  GUIRadioButtonGroup::getActiveString(void)
{
	return m_RadioButtons.at(m_ActiveButton)->getStringRepresentation();
}
unsigned int GUIRadioButtonGroup::getActiveIndex(void)
{
	return m_ActiveButton;
}