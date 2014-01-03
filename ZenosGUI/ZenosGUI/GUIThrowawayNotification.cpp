#include "GUIThrowawayNotification.h"

#include "GUIManager.h"

#define GUI_THROWAWAY_BORDER_THICKNESS 2.0f

GUIThrowawayNotification::GUIThrowawayNotification(sf::Vector2f _position, sf::Vector2f _size, std::string _message) :
	/*m_OkButton("Ok.", 
			   &m_ToRemove, 
			   sf::Vector2f(_position.x + _size.x / 2.0f - (_size.x > 30.0f ? 30.0f : 0.0f), _position.y + _size.y / 2.0f - (_size.y > 30.0f ? 30.0f : 0.0f)),
			   sf::Vector2f(60.0f, 30.0f)),*/
	m_Message(_message, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), 16),
	m_BackgroundQuads(sf::Quads, 8)
{
	m_Message.setOrigin(m_Message.getGlobalBounds().left + m_Message.getGlobalBounds().width / 2.0f,
						m_Message.getGlobalBounds().top + m_Message.getGlobalBounds().height / 2.0f);
	m_Message.setPosition(_position);
	m_Message.setColor(sf::Color::Black);

	m_BackgroundQuads[0] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												   _position.y - _size.y / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[1] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												   _position.y - _size.y / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[2] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												   _position.y + _size.y / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[3] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												   _position.y + _size.y / 2.0f),
									  sf::Color(125, 125, 125, 255));

	m_BackgroundQuads[4] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_THROWAWAY_BORDER_THICKNESS,
												   _position.y - _size.y / 2.0f + GUI_THROWAWAY_BORDER_THICKNESS),
									  sf::Color(175, 175, 175, 255));
	m_BackgroundQuads[5] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_THROWAWAY_BORDER_THICKNESS,
												   _position.y - _size.y / 2.0f + GUI_THROWAWAY_BORDER_THICKNESS),
									  sf::Color(175, 175, 175, 255));
	m_BackgroundQuads[6] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_THROWAWAY_BORDER_THICKNESS,
												   _position.y + _size.y / 2.0f - GUI_THROWAWAY_BORDER_THICKNESS),
									  sf::Color(175, 175, 175, 255));
	m_BackgroundQuads[7] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_THROWAWAY_BORDER_THICKNESS,
												   _position.y + _size.y / 2.0f - GUI_THROWAWAY_BORDER_THICKNESS),
									  sf::Color(175, 175, 175, 255));
}

GUIThrowawayNotification::~GUIThrowawayNotification(void)
{
}


void GUIThrowawayNotification::update(sf::Time _delta)
{
	//m_OkButton.update(_delta);
}
void GUIThrowawayNotification::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_BackgroundQuads,	_states);
	_target.draw(m_Message,			_states);
	//_target.draw(m_OkButton,		_states);
}