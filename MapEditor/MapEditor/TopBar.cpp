#include "TopBar.h"

#include "Game.h"

TopBar::TopBar(void) :
	m_BackgroundQuads(sf::Quads, 4)
{
}

TopBar::~TopBar(void)
{
}


void TopBar::initialise(sf::FloatRect _bounds)
{	
	m_BackgroundQuads[0] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[1] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[2] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[3] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));
}

void TopBar::update(sf::Time _delta)
{
}
void TopBar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_BackgroundQuads,		_states);

	_target.setView(sGame.m_View);
}