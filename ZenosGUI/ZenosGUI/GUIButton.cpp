#include "GUIButton.h"

#include "GUIManager.h"

#include <iostream>

#define GUI_DEFAULT_BUTTON_SIZE			sf::Vector2f(40.0f, 40.0f) 
#define GUI_BUTTON_OUTLINE				1.0f
#define GUI_TEXT_BOX_DISPLACEMENT		3.0f

GUIButton::GUIButton(std::string _text, bool *_toActivate, sf::Vector2f _position, sf::Vector2f _size/* = sf::Vector2f()*/) :
	m_Vertices(sf::Quads, 8),
	m_CurrentState(colourState::NORMAL),
	m_ToActivate(_toActivate),
	m_Unactivate(false)
{
	m_DisplayText = !(_text == "");

	sf::FloatRect bounds;

	if (m_DisplayText)
	{
		m_Text = sf::Text(_text, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), 20);
		m_Text.setOrigin(m_Text.getGlobalBounds().width / 2.0f, m_Text.getGlobalBounds().height / 2.0f);
		m_Text.setPosition(_position);
		m_Text.setColor(sf::Color::White);

		bounds = sf::FloatRect(m_Text.getGlobalBounds().left - GUI_TEXT_BOX_DISPLACEMENT,				m_Text.getGlobalBounds().top - GUI_TEXT_BOX_DISPLACEMENT, 
							   m_Text.getGlobalBounds().width + 2.0f * GUI_TEXT_BOX_DISPLACEMENT,		m_Text.getGlobalBounds().height + 2.0f * GUI_TEXT_BOX_DISPLACEMENT);
	}
	else
	{
		if (_size == sf::Vector2f()) _size = GUI_DEFAULT_BUTTON_SIZE;

		bounds = sf::FloatRect(_position.x - _size.x / 2.0f, _position.y - _size.y / 2.0f, _size.x, _size.y);
	}


	sf::Color outline = sf::Color(165, 165, 165, 255);
	sf::Color inner   = sf::Color(91, 91, 91, 255);

	m_Vertices[0] = sf::Vertex(sf::Vector2f(bounds.left,					bounds.top),					outline);
	m_Vertices[1] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width,		bounds.top),					outline);
	m_Vertices[2] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width,		bounds.top + bounds.height),	outline);
	m_Vertices[3] = sf::Vertex(sf::Vector2f(bounds.left,					bounds.top + bounds.height),	outline);

	m_Vertices[4] = sf::Vertex(sf::Vector2f(bounds.left + GUI_BUTTON_OUTLINE,					bounds.top + GUI_BUTTON_OUTLINE),					inner);
	m_Vertices[5] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width - GUI_BUTTON_OUTLINE,	bounds.top + GUI_BUTTON_OUTLINE),					inner);
	m_Vertices[6] = sf::Vertex(sf::Vector2f(bounds.left + bounds.width - GUI_BUTTON_OUTLINE,	bounds.top + bounds.height - GUI_BUTTON_OUTLINE),	inner);
	m_Vertices[7] = sf::Vertex(sf::Vector2f(bounds.left + GUI_BUTTON_OUTLINE,					bounds.top + bounds.height - GUI_BUTTON_OUTLINE),	inner);

	sGUIINPUT->registerButton(sf::Mouse::Left);
}

GUIButton::~GUIButton(void)
{
	sGUIINPUT->unregisterButton(sf::Mouse::Left);
}


void GUIButton::update(sf::Time _delta)
{
	if (!m_Update) return;
	if (*m_ToActivate && m_Unactivate)
	{
		*m_ToActivate = false;
		m_Unactivate = false;
	}

	if (m_Vertices.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
	{
		
		if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::CLICK);
		}
		else if (sGUIINPUT->getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::HOVER);
			*m_ToActivate = true;
			m_Unactivate = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changeColourState(colourState::HOVER);
		}
	}
	else
	{
		changeColourState(colourState::NORMAL);
	}
}
	
void GUIButton::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;
	_target.draw(m_Vertices,			_states);
	if (m_DisplayText)
	{
		_target.draw(m_Text,			_states);
	}
}

void GUIButton::changeColourState(colourState _state){
	if (_state == m_CurrentState) return;

	m_CurrentState = _state;

	switch (m_CurrentState)
	{
	case (colourState::HOVER):
		setHoverColours();
		return;
	case (colourState::CLICK):
		setPressedColours();
		return;
	case (colourState::NORMAL):
	default:
		setDefaultColours();
	};

}

void  GUIButton::setDefaultColours(void)
{
	m_Text.setColor(sf::Color(195, 195, 195, 195));

	m_Vertices[0].color = sf::Color(155, 155, 155, 255);
	m_Vertices[1].color = sf::Color(155, 155, 155, 255);
	m_Vertices[2].color = sf::Color(155, 155, 155, 255);
	m_Vertices[3].color = sf::Color(155, 155, 155, 255);

	m_Vertices[4].color = sf::Color(100, 100, 100, 255);
	m_Vertices[5].color = sf::Color(100, 100, 100, 255);
	m_Vertices[6].color = sf::Color(100, 100, 100, 255);
	m_Vertices[7].color = sf::Color(100, 100, 100, 255);
}
void  GUIButton::setHoverColours(void)
{
	m_Text.setColor(sf::Color(195, 195, 195, 255));

	m_Vertices[0].color = sf::Color(94, 155, 255, 255);
	m_Vertices[1].color = sf::Color(94, 155, 255, 255);
	m_Vertices[2].color = sf::Color(94, 155, 255, 255);
	m_Vertices[3].color = sf::Color(94, 155, 255, 255);

	m_Vertices[4].color = sf::Color(100, 100, 100, 255);
	m_Vertices[5].color = sf::Color(100, 100, 100, 255);
	m_Vertices[6].color = sf::Color(100, 100, 100, 255);
	m_Vertices[7].color = sf::Color(100, 100, 100, 255);
}
void  GUIButton::setPressedColours(void)
{
	m_Text.setColor(sf::Color::White);

	m_Vertices[0].color = sf::Color(94, 155, 255, 255);
	m_Vertices[1].color = sf::Color(94, 155, 255, 255);
	m_Vertices[2].color = sf::Color(94, 155, 255, 255);
	m_Vertices[3].color = sf::Color(94, 155, 255, 255);

	m_Vertices[4].color = sf::Color(65, 65, 65, 255);
	m_Vertices[5].color = sf::Color(65, 65, 65, 255);
	m_Vertices[6].color = sf::Color(65, 65, 65, 255);
	m_Vertices[7].color = sf::Color(65, 65, 65, 255);
}