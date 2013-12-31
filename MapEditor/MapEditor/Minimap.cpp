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

	m_ViewportOutline.setSize(sf::Vector2f((sGame.m_ScreenSize.x - m_MapImage.getSize().x) / TILESIZE_f, (sGame.m_ScreenSize.y - 20.0f) / TILESIZE_f));
	m_ViewportOutline.setFillColor(sf::Color::Transparent);
	m_ViewportOutline.setOutlineThickness(1.0f);
}

void Minimap::update(sf::Time _delta)
{
	if (m_RefreshMap)
	{
		m_RefreshMap = false;
		m_MapTexture.loadFromImage(m_MapImage);
		m_MapSprite.setTexture(m_MapTexture);
	}

	updateViewPortOutlinePosition();
}
void Minimap::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_MapSprite,			_states);
	_target.draw(m_ViewportOutline,		_states);

	_target.setView(sGame.m_View);
}

void Minimap::updateColour(unsigned int _x, unsigned int _y, sf::Color _colour)
{
	m_MapImage.setPixel(m_MapStartX + _x, m_MapStartY + _y, _colour);
	m_RefreshMap = true;
}

void Minimap::updateViewPortOutlinePosition(void)
{
	static sf::Vector2f viewPortCentre = sGame.m_View.getCenter();

	if (viewPortCentre == sGame.m_View.getCenter()) return;
	viewPortCentre = sGame.m_View.getCenter();

	m_ViewportOutline.setPosition(m_MapSprite.getPosition() + sf::Vector2f((float)(m_MapStartX), (float)(m_MapStartY)) + sf::Vector2f((viewPortCentre - sGame.m_View.getSize() / 2.0f) / TILESIZE_f + sf::Vector2f(0.0f, 1.0f)));
}