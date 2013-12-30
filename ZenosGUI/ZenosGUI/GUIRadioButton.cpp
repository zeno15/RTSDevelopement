#include "GUIRadioButton.h"

#include "GUIManager.h"

#include <cmath>

#ifndef PI
#define PI						3.14156
#endif //~ PI

#define GUI_RADIO_RADIUS_OUTER	10.0f
#define GUI_RADIO_OUTLINE_SIZE	3.0f
#define GUI_RADIO_RADIUS_INNER	6.0f
#define GUI_RADIO_TRIANGLES		16
#define GUI_RADIO_TEXT_OFFSET	sf::Vector2f(15.0f, - 5.0f)
#define GUI_RADIO_CHAR_SIZE		20

GUIRadioButton::GUIRadioButton(sf::Vector2f _position, std::string _text, bool _active/* = false*/) :
	m_SelectedRadioButton(false),
	m_Selected(_active),
	m_Position(_position),
	m_Description(_text, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_RADIO_CHAR_SIZE),
	m_Outline(sf::TrianglesFan, GUI_RADIO_TRIANGLES + 2),
	m_Background(sf::TrianglesFan, GUI_RADIO_TRIANGLES + 2),
	m_Selection(sf::TrianglesFan, GUI_RADIO_TRIANGLES + 2)
{
	float angleDelta = 360.0f / (float)(GUI_RADIO_TRIANGLES);

	m_Outline[0] = sf::Vertex(_position, sf::Color::Black);

	for (unsigned int i = 1; i < m_Outline.getVertexCount(); i += 1)
	{
		m_Outline[i] = sf::Vertex(sf::Vector2f(cosf(angleDelta * (i - 1) * PI / 180.0f) * GUI_RADIO_RADIUS_OUTER + _position.x,
											   sinf(angleDelta * (i - 1) * PI / 180.0f) * GUI_RADIO_RADIUS_OUTER + _position.y),
								  sf::Color::Black);
	}

	m_Background[0] = sf::Vertex(_position, sf::Color::White);

	for (unsigned int i = 1; i < m_Outline.getVertexCount(); i += 1)
	{
		m_Background[i] = sf::Vertex(sf::Vector2f(cosf(angleDelta * (i - 1) * PI / 180.0f) * (GUI_RADIO_RADIUS_OUTER - GUI_RADIO_OUTLINE_SIZE) + _position.x,
											      sinf(angleDelta * (i - 1) * PI / 180.0f) * (GUI_RADIO_RADIUS_OUTER - GUI_RADIO_OUTLINE_SIZE) + _position.y),
									 sf::Color::White);
	}

	m_Selection[0] = sf::Vertex(_position, sf::Color::Black);

	for (unsigned int i = 1; i < m_Outline.getVertexCount(); i += 1)
	{
		m_Selection[i] = sf::Vertex(sf::Vector2f(cosf(angleDelta * (i - 1) * PI / 180.0f) * GUI_RADIO_RADIUS_INNER + _position.x,
											     sinf(angleDelta * (i - 1) * PI / 180.0f) * GUI_RADIO_RADIUS_INNER + _position.y),
									sf::Color::Black);
	}

	m_Description.setOrigin(0.0f, m_Description.getGlobalBounds().height / 2.0f);
	m_Description.setPosition(_position + GUI_RADIO_TEXT_OFFSET);
}

GUIRadioButton::~GUIRadioButton(void)
{
}


void GUIRadioButton::update(sf::Time _delta)
{
	if (!m_Update) return;

	if (m_Outline.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
	{
		if (m_SelectedRadioButton)
		{
			if (sGUIINPUT->getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_Selected = true;
				m_SelectedRadioButton = false;
			}
		}
		else
		{
			if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_SelectedRadioButton = true;
			}
		}
	}
}
	
void GUIRadioButton::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_Outline,			_states);
	_target.draw(m_Background,		_states);

	if (m_Selected)		_target.draw(m_Selection,		_states);

	_target.draw(m_Description,		_states);
}

std::string GUIRadioButton::getStringRepresentation(void)
{
	return m_Description.getString().toAnsiString();
}

bool GUIRadioButton::isActive(void)
{
	return m_Selected;
}
void GUIRadioButton::reset(void)
{
	m_Selected = false;
}