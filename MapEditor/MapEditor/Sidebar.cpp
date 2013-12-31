#include "Sidebar.h"

#include "Game.h"

Sidebar::Sidebar(void) :
	m_BackgroundQuads(sf::Quads, 4)
{
}

Sidebar::~Sidebar(void)
{
}


void Sidebar::initialise(sf::FloatRect _bounds)
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

void Sidebar::update(sf::Time _delta)
{
}
void Sidebar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_BackgroundQuads,		_states);

	_target.setView(sGame.m_View);
}