#include "Minimap.h"

#include "Game.h"

Minimap::Minimap(void) :
	m_RefreshMap(false)
{
}

Minimap::~Minimap(void)
{
}


void Minimap::initialise(sf::FloatRect _bounds, sf::Vector2u _mapSize)
{
	m_MapImage.create((unsigned int)(_bounds.width), (unsigned int)(_bounds.height), sf::Color(75, 75, 75, 255));

	m_MapStartX = (m_MapImage.getSize().x - _mapSize.x) / 2;
	m_MapStartY = (m_MapImage.getSize().y - _mapSize.y) / 2;

	m_MapTexture.loadFromImage(m_MapImage);
	m_MapSprite.setTexture(m_MapTexture);
	m_MapSprite.setPosition(_bounds.left, _bounds.top);
}

void Minimap::update(sf::Time _delta)
{
	if (m_RefreshMap)
	{
		m_RefreshMap = false;
		m_MapTexture.loadFromImage(m_MapImage);
		m_MapSprite.setTexture(m_MapTexture);
	}

}
void Minimap::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_MapSprite,			_states);

	_target.setView(sGame.m_View);
}

void Minimap::updateColour(unsigned int _x, unsigned int _y, sf::Color _colour)
{
	m_MapImage.setPixel(m_MapStartX + _x, m_MapStartY + _y, _colour);
	m_RefreshMap = true;
}