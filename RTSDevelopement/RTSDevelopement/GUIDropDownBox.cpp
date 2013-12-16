#include "GUIDropDownBox.h"

#include "Game.h"

GUIDropDownBox::GUIDropDownBox(void)
{
	sGame.m_InputManager.registerButton(sf::Mouse::Left);
}

GUIDropDownBox::~GUIDropDownBox(void)
{
	sGame.m_InputManager.unregisterButton(sf::Mouse::Left);
}


void GUIDropDownBox::update(sf::Time _delta)
{
}
void GUIDropDownBox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
}