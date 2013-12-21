#include "GUIDropDownMenu.h"

#include "Game.h"

#define GUI_DROPDOWNMENU_CHAR_SIZE		16u
#define GUI_DROPDOWNMENU_CHAR_OFFSET	2.0f

GUIDropDownMenu::GUIDropDownMenu(std::string _text, sf::Vector2f _position, float _length) :
	m_Activated(false),
	m_IsChild(false),
	m_BackgroundQuads(sf::Quads, 0),
	m_SubMenuArrows(sf::Triangles, 0),
	m_SubMenuBackground(sf::Quads, 0),
	m_Description(_text, *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNMENU_CHAR_SIZE),
	m_Position(_position)
{
	m_Description.setOrigin((m_Description.getGlobalBounds().left + m_Description.getGlobalBounds().width) / 2.0f, (m_Description.getGlobalBounds().top + m_Description.getGlobalBounds().height) / 2.0f);
	m_Description.setPosition(_position);

	m_BackgroundQuads.append(sf::Vertex(sf::Vector2f(_position.x - _length / 2.0f,
													 _position.y - (float)(GUI_DROPDOWNMENU_CHAR_SIZE / 2.0f) + GUI_DROPDOWNMENU_CHAR_OFFSET),
										sf::Color(155, 155, 155, 255)));
	m_BackgroundQuads.append(sf::Vertex(sf::Vector2f(_position.x + _length / 2.0f,
													 _position.y - (float)(GUI_DROPDOWNMENU_CHAR_SIZE / 2.0f) + GUI_DROPDOWNMENU_CHAR_OFFSET),
										sf::Color(155, 155, 155, 255)));
	m_BackgroundQuads.append(sf::Vertex(sf::Vector2f(_position.x + _length / 2.0f,
													 _position.y + (float)(GUI_DROPDOWNMENU_CHAR_SIZE / 2.0f) + GUI_DROPDOWNMENU_CHAR_OFFSET),
										sf::Color(155, 155, 155, 255)));
	m_BackgroundQuads.append(sf::Vertex(sf::Vector2f(_position.x - _length / 2.0f,
													 _position.y + (float)(GUI_DROPDOWNMENU_CHAR_SIZE / 2.0f) + GUI_DROPDOWNMENU_CHAR_OFFSET),
										sf::Color(155, 155, 155, 255)));
}

GUIDropDownMenu::~GUIDropDownMenu(void)
{
	for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
	{
		mDebugDelete(m_SubMenus.at(i))
		delete m_SubMenus.at(i);
	}
}


void GUIDropDownMenu::update(sf::Time _delta)
{
	if (m_BackgroundQuads.getBounds().contains((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)))
	{
		if (!sGame.m_InputManager.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//~ Activate :D
		}
		else
		{
			setState(mouseState::HOVER);
		}
	}
	else
	{
		setState(mouseState::NORMAL);
	}

	for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
	{
		m_SubMenus.at(i)->update(_delta);
	}
}
	
void GUIDropDownMenu::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_BackgroundQuads,			_states);
	_target.draw(m_Description,				_states);

	for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
	{
		_target.draw(*m_SubMenus.at(i),				_states);
	}
}

void GUIDropDownMenu::addSubMenu(GUIDropDownMenu *_subMenu)
{
	_subMenu->m_IsChild = true;
	m_SubMenus.push_back(_subMenu);
}

void GUIDropDownMenu::setState(mouseState _state)
{
	if (_state == m_State) return;

	m_State = _state;

	switch(_state)
	{
	case (mouseState::HOVER):
		setHoverColour();
		return;
	case (mouseState::NORMAL):
	default:
		setNormalColour();
		return;
	};
}

void GUIDropDownMenu::setNormalColour(void)
{
	m_BackgroundQuads[0].color = sf::Color(155, 155, 155, 255);
	m_BackgroundQuads[1].color = sf::Color(155, 155, 155, 255);
	m_BackgroundQuads[2].color = sf::Color(155, 155, 155, 255);
	m_BackgroundQuads[3].color = sf::Color(155, 155, 155, 255);

	m_Description.setColor(sf::Color::White);
}
void GUIDropDownMenu::setHoverColour(void)
{
	m_BackgroundQuads[0].color = sf::Color(55, 55, 55, 255);
	m_BackgroundQuads[1].color = sf::Color(55, 55, 55, 255);
	m_BackgroundQuads[2].color = sf::Color(55, 55, 55, 255);
	m_BackgroundQuads[3].color = sf::Color(55, 55, 55, 255);

	m_Description.setColor(sf::Color::White);
}