#include "GUIDropDownMenu.h"

#include "Game.h"

#define GUI_DROPDOWNMENU_CHAR_SIZE		16u
#define GUI_DROPDOWNMENU_CHAR_OFFSET	2.0f
#define GUI_DROPDOWNMENU_HEIGHT			20.0f

GUIDropDownMenu::GUIDropDownMenu(std::string _text, sf::Vector2f _position, float _length, bool _isRoot/* = false*/) :
	m_Extended(false),
	m_IsRoot(_isRoot),
	m_State(menuState::NORMAL),
	m_MenuBackground(sf::Quads, 0),
	m_Position(_position),
	m_Length(_length),
	m_Text(_text, *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNMENU_CHAR_SIZE)
{
	m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_Position.x - m_Length / 2.0f,
													m_Position.y - GUI_DROPDOWNMENU_HEIGHT / 2.0f),
									   sf::Color(155, 155, 155, 255)));
	m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_MenuBackground[0].position.x + m_Length,
													m_MenuBackground[0].position.y),
									   sf::Color(155, 155, 155, 255)));
	m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_MenuBackground[1].position.x,
													m_MenuBackground[1].position.y + GUI_DROPDOWNMENU_HEIGHT),
									   sf::Color(155, 155, 155, 255)));
	m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_MenuBackground[0].position.x,
													m_MenuBackground[0].position.y + GUI_DROPDOWNMENU_HEIGHT),
									   sf::Color(155, 155, 155, 255)));

	m_Text.setOrigin(m_Text.getGlobalBounds().left + (m_Text.getGlobalBounds().width)  / 2.0f,
					 m_Text.getGlobalBounds().top  + (m_Text.getGlobalBounds().height) / 2.0f);
	m_Text.setPosition(m_Position);

	findExtensionPosition();
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
	if (m_MenuBackground.getBounds().contains((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)))
	{
		if (!sGame.m_InputManager.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setState(menuState::EXTEND);
			extend();
		}
		else if (!m_Extended)
		{
			setState(menuState::HOVER);
		}
	}
	else
	{
		setState(menuState::NORMAL);
	}

	if (m_Extended)
	{
		for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
		{
			m_SubMenus.at(i)->update(_delta);
		}
	}
}
	
void GUIDropDownMenu::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_MenuBackground,			_states);
	_target.draw(m_Text,			_states);

	if (m_Extended)
	{
		for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
		{
			_target.draw(*m_SubMenus.at(i),				_states);
		}
	}
}

void GUIDropDownMenu::extend(void)
{
	if (m_SubMenus.size() == 0u) return;

	m_Extended = !m_Extended;

	if (m_Extended)
	{
		m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_ExtendPosition.x - m_Length / 2.0f,
														m_ExtendPosition.y - GUI_DROPDOWNMENU_HEIGHT / 2.0f),
										   sf::Color(155, 155, 155, 255)));
		m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_ExtendPosition.x + m_Length / 2.0f,
														m_ExtendPosition.y - GUI_DROPDOWNMENU_HEIGHT / 2.0f),
										   sf::Color(155, 155, 155, 255)));
		m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_ExtendPosition.x + m_Length / 2.0f,
														m_ExtendPosition.y + GUI_DROPDOWNMENU_HEIGHT * (m_SubMenus.size() - 0.5f)),
										   sf::Color(155, 155, 155, 255)));
		m_MenuBackground.append(sf::Vertex(sf::Vector2f(m_ExtendPosition.x - m_Length / 2.0f,
														m_ExtendPosition.y + GUI_DROPDOWNMENU_HEIGHT * (m_SubMenus.size() - 0.5f)),
										   sf::Color(155, 155, 155, 255)));
	}
	else
	{
		m_MenuBackground.resize(4);
	}
}

void GUIDropDownMenu::setState(menuState _state)
{
	if (m_State == _state) return;

	m_State = _state;

	switch (_state)
	{
	case (menuState::EXTEND):
		m_MenuBackground[0].color = sf::Color(55, 55, 55, 255);
		m_MenuBackground[1].color = sf::Color(55, 55, 55, 255);
		m_MenuBackground[2].color = sf::Color(55, 55, 55, 255);
		m_MenuBackground[3].color = sf::Color(55, 55, 55, 255);
		return;
	case (menuState::HOVER):
		m_MenuBackground[0].color = sf::Color(105, 105, 105, 255);
		m_MenuBackground[1].color = sf::Color(105, 105, 105, 255);
		m_MenuBackground[2].color = sf::Color(105, 105, 105, 255);
		m_MenuBackground[3].color = sf::Color(105, 105, 105, 255);
		return;
	case (menuState::NORMAL):
	default:
		m_MenuBackground[0].color = sf::Color(155, 155, 155, 255);
		m_MenuBackground[1].color = sf::Color(155, 155, 155, 255);
		m_MenuBackground[2].color = sf::Color(155, 155, 155, 255);
		m_MenuBackground[3].color = sf::Color(155, 155, 155, 255);
		return;
	}
}

void GUIDropDownMenu::findExtensionPosition(void)
{
	if (m_IsRoot)
	{
		m_ExtendPosition = m_Position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT);
	}
	else
	{

	}
}

void GUIDropDownMenu::addSubMenu(GUIDropDownMenu *_subMenu)
{
	m_SubMenus.push_back(_subMenu);
}

void GUIDropDownMenu::rootFinaliseMenuPositions(void)
{
	for (unsigned int i = 0; i < m_SubMenus.size(); i += 1)
	{
		m_SubMenus.at(i)->m_Position = m_Position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT * (i + 1));
	}
}