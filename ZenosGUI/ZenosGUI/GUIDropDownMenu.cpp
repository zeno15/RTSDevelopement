#include "GUIDropDownMenu.h"

#include "GUIManager.h"

#define GUI_DROPDOWNMENU_CHAR_SIZE			16u
#define GUI_DROPDOWNMENU_CHAR_OFFSET		2.0f
#define GUI_DROPDOWNMENU_HEIGHT				20.0f
#define GUI_DROPDOWNMENU_TEXT_DEFAULT_COL	sf::Color::White
#define GUI_DROPDOWNMENU_TEXT_SELECT_COL	sf::Color::Black

GUIDropDownMenu::GUIDropDownMenu(sf::Vector2f _position, float _length, std::string _menuName, std::vector<std::vector<std::string>> _menuNames) :
	m_MenuNames(_menuNames),
	m_BackgroundQuads(sf::Quads, 4),
	m_MenuExtended(0),
	m_Extended(false),
	m_DoubleExtended(false)
{
	m_BackgroundQuads[0] = sf::Vertex(sf::Vector2f(_position.x - _length / 2.0f,
												   _position.y - GUI_DROPDOWNMENU_HEIGHT / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[1] = sf::Vertex(sf::Vector2f(_position.x + _length / 2.0f,
												   _position.y - GUI_DROPDOWNMENU_HEIGHT / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[2] = sf::Vertex(sf::Vector2f(_position.x + _length / 2.0f,
												   _position.y + GUI_DROPDOWNMENU_HEIGHT / 2.0f),
									  sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[3] = sf::Vertex(sf::Vector2f(_position.x - _length / 2.0f,
												   _position.y + GUI_DROPDOWNMENU_HEIGHT / 2.0f),
									  sf::Color(125, 125, 125, 255));

	m_Texts.push_back(sf::Text(_menuName, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNMENU_CHAR_SIZE));
	m_Texts.at(0).setOrigin(m_Texts.at(0).getGlobalBounds().left,
							m_Texts.at(0).getGlobalBounds().top + m_Texts.at(0).getGlobalBounds().height / 2.0f);
	m_Texts.at(0).setPosition(_position - sf::Vector2f(_length / 2.0f - GUI_DROPDOWNMENU_CHAR_OFFSET, 0.0f));
	m_Texts.at(0).setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);

	for (unsigned int i = 0; i < m_MenuNames.size(); i += 1)
	{
		m_Texts.push_back(sf::Text(m_MenuNames.at(i).at(0), *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNMENU_CHAR_SIZE));
		m_Texts.back().setOrigin(m_Texts.back().getGlobalBounds().left,
									m_Texts.back().getGlobalBounds().top + m_Texts.back().getGlobalBounds().height / 2.0f);
		m_Texts.back().setPosition(sf::Vector2f(_position.x - _length / 2.0f,
												_position.y + 20.0f * (i + 1)));
		m_Texts.back().setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);
		for (unsigned int j = 1; j < m_MenuNames.at(i).size(); j += 1)
		{
			m_Texts.push_back(sf::Text(m_MenuNames.at(i).at(j), *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNMENU_CHAR_SIZE));
			m_Texts.back().setOrigin(m_Texts.back().getGlobalBounds().left,
										m_Texts.back().getGlobalBounds().top + m_Texts.back().getGlobalBounds().height / 2.0f);
			m_Texts.back().setPosition(sf::Vector2f(_position.x + _length / 2.0f,
													_position.y + 20.0f * (i + j)));
			m_Texts.back().setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);
		}
	}

	

	m_MenuDraws.resize(m_Texts.size(), false);


	setMenuDraws(0);
}

GUIDropDownMenu::~GUIDropDownMenu(void)
{
}


void GUIDropDownMenu::update(sf::Time _delta)
{
	if (!m_Update) return;


	if (m_DoubleExtended)
	{
		sf::FloatRect mainMenuBounds(m_BackgroundQuads[0].position.x,
									 m_BackgroundQuads[0].position.y + GUI_DROPDOWNMENU_HEIGHT,
									 m_BackgroundQuads[1].position.x - m_BackgroundQuads[0].position.x,
									 GUI_DROPDOWNMENU_HEIGHT * m_MenuNames.size());

		if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			mainMenuBounds.contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			m_DoubleExtended = false;
			setMenuDraws(0);
			return;
		}

		sf::FloatRect subMenuBounds(m_BackgroundQuads[4].position.x,
									m_BackgroundQuads[4].position.y,
									m_BackgroundQuads[5].position.x - m_BackgroundQuads[4].position.x,
									GUI_DROPDOWNMENU_HEIGHT * m_MenuNames.at(m_MenuExtended - 1).size());

		if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			!subMenuBounds.contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			m_DoubleExtended = false;
			m_Extended = false;
			setMenuDraws(0);
			notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);
			return;
		}

		unsigned int count = 1;

		for (unsigned int i = 0; i < m_MenuExtended - 1; i += 1)
		{
			count += m_MenuNames.at(i).size();
		}

		subMenuBounds = sf::FloatRect(m_BackgroundQuads[4].position.x,
									  m_BackgroundQuads[4].position.y - GUI_DROPDOWNMENU_HEIGHT,
									  m_BackgroundQuads[5].position.x - m_BackgroundQuads[4].position.x,
									  GUI_DROPDOWNMENU_HEIGHT);

		for (unsigned int i = 1; i < m_MenuNames.at(m_MenuExtended - 1).size(); i += 1)
		{
			subMenuBounds.top += GUI_DROPDOWNMENU_HEIGHT;
			

			if (subMenuBounds.contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
			{
				if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					notifyReceivers(MessageData::MessageType::DROPDOWN_MENU_SELECT, 0.0f, m_Texts.at(0).getString().toAnsiString() + "-" + m_MenuNames.at(m_MenuExtended - 1).at(0) + "-" + m_MenuNames.at(m_MenuExtended - 1).at(i));
					notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);
					m_Extended = false;
					m_DoubleExtended = false;
					setMenuDraws(0);
					return;
				}
				else
				{
					m_Texts.at(count + i).setColor(GUI_DROPDOWNMENU_TEXT_SELECT_COL);
				}
			}
			else
			{
				m_Texts.at(count + i).setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);
			}
		}
	}
	else if (m_Extended)
	{
		sf::FloatRect subMenuBounds(m_BackgroundQuads[0].position.x,
									m_BackgroundQuads[0].position.y + GUI_DROPDOWNMENU_HEIGHT,
									m_BackgroundQuads[1].position.x - m_BackgroundQuads[0].position.x,
									GUI_DROPDOWNMENU_HEIGHT * m_MenuNames.size());

		if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			!subMenuBounds.contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			m_Extended = false;
			setMenuDraws(0);
			notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);
		}

		unsigned int count = 0;

		subMenuBounds = sf::FloatRect(m_BackgroundQuads[0].position.x,
									  m_BackgroundQuads[0].position.y,
									  m_BackgroundQuads[1].position.x - m_BackgroundQuads[0].position.x,
									  GUI_DROPDOWNMENU_HEIGHT);

		for (unsigned int i = 0; i < m_MenuNames.size(); i += 1)
		{
			subMenuBounds.top += GUI_DROPDOWNMENU_HEIGHT;

			if (subMenuBounds.contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
			{
				if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (m_MenuNames.at(i).size() == 1)
					{
						m_Extended = false;
						setMenuDraws(0);
						notifyReceivers(MessageData::MessageType::DROPDOWN_MENU_SELECT, 0.0f, m_Texts.at(0).getString().toAnsiString() + "-" + m_MenuNames.at(i).at(0));
						notifyReceivers(MessageData::MessageType::DROPDOWN_UNACTIVE);
					}
					else
					{
						m_DoubleExtended = true;
						setMenuDraws(i + 1);
					}
				}
				else 
				{
					m_Texts.at(count + 1).setColor(GUI_DROPDOWNMENU_TEXT_SELECT_COL);
				}
			}
			else
			{
				m_Texts.at(count + 1).setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);
			}

			count += m_MenuNames.at(i).size();
		}
	}
	else
	{
		// sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))

		if (m_BackgroundQuads.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_Extended = true;
				notifyReceivers(MessageData::MessageType::DROPDOWN_ACTIVE);
				setMenuDraws(0);
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_Texts.at(0).setColor(GUI_DROPDOWNMENU_TEXT_SELECT_COL);
			}
		}
		else
		{
			m_Texts.at(0).setColor(GUI_DROPDOWNMENU_TEXT_DEFAULT_COL);
		}
	}

}
	
void GUIDropDownMenu::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_BackgroundQuads,			_states);
	

	for (unsigned int i = 0; i < m_Texts.size(); i += 1)
	{
		if (m_MenuDraws.at(i))
		{
			_target.draw(m_Texts.at(i),			_states);
		}
	}
}

void GUIDropDownMenu::setMenuDraws(unsigned int _menu)
{
	unsigned int count = 0;

	m_MenuExtended = _menu;

	if (m_Extended)
	{
		for (unsigned int i = 0; i < m_MenuNames.size(); i += 1)
		{
			count += 1;

			m_MenuDraws.at(count) = true;

			for (unsigned int j = 1; j < m_MenuNames.at(i).size(); j += 1)
			{
				count += 1;

				if ((int)i == (int)_menu - 1)
				{
					m_MenuDraws.at(count) = true;
				}
				else
				{
					m_MenuDraws.at(count) = false;
				}
			}
		}

		//~ append first menu background

		m_BackgroundQuads[2].position = m_BackgroundQuads[1].position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT * (m_MenuNames.size() + 1));
		m_BackgroundQuads[3].position = m_BackgroundQuads[0].position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT * (m_MenuNames.size() + 1));
		m_BackgroundQuads.resize(4);

		if (_menu != 0)
		{
			m_BackgroundQuads.resize(8);
			//~ append _menu-th background
			m_BackgroundQuads[4] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[1].position.x,
														   m_BackgroundQuads[1].position.y + GUI_DROPDOWNMENU_HEIGHT * _menu),
											  sf::Color(175, 175, 175, 255));
			m_BackgroundQuads[5] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[4].position.x + (m_BackgroundQuads[1].position.x - m_BackgroundQuads[0].position.x),
														   m_BackgroundQuads[4].position.y),
											  sf::Color(175, 175, 175, 255));
			m_BackgroundQuads[6] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[5].position.x,
														   m_BackgroundQuads[5].position.y + (m_MenuNames.at(_menu - 1).size() - 1) * GUI_DROPDOWNMENU_HEIGHT),
											  sf::Color(175, 175, 175, 255));
			m_BackgroundQuads[7] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[4].position.x,
														   m_BackgroundQuads[4].position.y + (m_MenuNames.at(_menu - 1).size() - 1) * GUI_DROPDOWNMENU_HEIGHT),
											  sf::Color(175, 175, 175, 255));
		}
	}
	else
	{
		for (unsigned int i = 0; i < m_MenuDraws.size(); i += 1)
		{
			m_MenuDraws.at(i) = false;
		}

		m_BackgroundQuads.resize(4);
		m_BackgroundQuads[2].position = m_BackgroundQuads[1].position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT);
		m_BackgroundQuads[3].position = m_BackgroundQuads[0].position + sf::Vector2f(0.0f, GUI_DROPDOWNMENU_HEIGHT);
	}

	m_MenuDraws.at(0) = true;
}