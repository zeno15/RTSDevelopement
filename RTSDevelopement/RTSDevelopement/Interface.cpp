#include "Interface.h"

#include <iostream>

#include "Game.h"

Interface::Interface(sf::FloatRect _topBarBounds, sf::FloatRect _sideBarBounds) :
	DEBUG_InterfaceBackground(sf::Quads, 8)
{
	DEBUG_BuildBar = new TempBuildBar(_sideBarBounds);

	DEBUG_InterfaceBackground[0].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[0].position = sf::Vector2f(_topBarBounds.left,
														 _topBarBounds.top);
	DEBUG_InterfaceBackground[1].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[1].position = sf::Vector2f(_topBarBounds.left + _topBarBounds.width,
														 _topBarBounds.top);
	DEBUG_InterfaceBackground[2].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[2].position = sf::Vector2f(_topBarBounds.left + _topBarBounds.width,
														 _topBarBounds.top + _topBarBounds.height);
	DEBUG_InterfaceBackground[3].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[3].position = sf::Vector2f(_topBarBounds.left,
														 _topBarBounds.top + _topBarBounds.height);


	DEBUG_InterfaceBackground[4].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[4].position = sf::Vector2f(_sideBarBounds.left,
														 _sideBarBounds.top);
	DEBUG_InterfaceBackground[5].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[5].position = sf::Vector2f(_sideBarBounds.left + _sideBarBounds.width,
														 _sideBarBounds.top);
	DEBUG_InterfaceBackground[6].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[6].position = sf::Vector2f(_sideBarBounds.left + _sideBarBounds.width,
														 _sideBarBounds.top + _sideBarBounds.height);
	DEBUG_InterfaceBackground[7].color = sf::Color(175, 175, 175, 255);
	DEBUG_InterfaceBackground[7].position = sf::Vector2f(_sideBarBounds.left,
														 _sideBarBounds.top + _sideBarBounds.height);

}

Interface::~Interface(void)
{
}


void Interface::update(sf::Time _delta)
{
	DEBUG_BuildBar->update(_delta);
}
void Interface::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(DEBUG_InterfaceBackground,			_states);

	_target.draw(*DEBUG_BuildBar,					_states);
}