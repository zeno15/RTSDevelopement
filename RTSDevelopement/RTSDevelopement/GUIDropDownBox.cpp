#include "GUIDropDownBox.h"

#include "Game.h"

#define GUI_DROPDOWNBOX_CHAR_DIFF	6.0f
#define GUI_DROPDOWNBOX_INSET		1.0f
#define GUI_DROPDOWNBOX_EXT_SPEED	500.0f

GUIDropDownBox::GUIDropDownBox(sf::Vector2f _position, sf::Vector2f _size) :
	m_Extended(false),
	m_OptionsToDraw(0u),
	m_ExtendedState(extendState::CLOSED),
	m_Position(_position),
	m_Size(_size),
	m_BackgroundQuads(sf::Quads, 12),
	m_ActiveIcon(sf::Quads, 8),
	m_ExtendedBackground(sf::Quads, 8),
	m_SelectedOption("EMPTY BOX", *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), (unsigned int)(_size.y - GUI_DROPDOWNBOX_CHAR_DIFF))
{
	m_BackgroundQuads[0]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												    _position.y - _size.y / 2.0f),
									   sf::Color(94, 155, 255, 255));
	m_BackgroundQuads[1]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												    _position.y - _size.y / 2.0f),
									   sf::Color(94, 155, 255, 255));
	m_BackgroundQuads[2]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												    _position.y + _size.y / 2.0f),
									   sf::Color(94, 155, 255, 255));
	m_BackgroundQuads[3]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												    _position.y + _size.y / 2.0f),
									   sf::Color(94, 155, 255, 255));

	m_BackgroundQuads[4]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_DROPDOWNBOX_INSET,
												    _position.y - _size.y / 2.0f + GUI_DROPDOWNBOX_INSET),
									   sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[5]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_DROPDOWNBOX_INSET * 2.0f - _size.y,
												    _position.y - _size.y / 2.0f + GUI_DROPDOWNBOX_INSET),
									   sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[6]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_DROPDOWNBOX_INSET * 2.0f - _size.y,
												    _position.y + _size.y / 2.0f - GUI_DROPDOWNBOX_INSET),
									   sf::Color(125, 125, 125, 255));
	m_BackgroundQuads[7]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_DROPDOWNBOX_INSET,
												    _position.y + _size.y / 2.0f - GUI_DROPDOWNBOX_INSET),
									   sf::Color(125, 125, 125, 255));

	m_BackgroundQuads[8]  = sf::Vertex(sf::Vector2f(m_BackgroundQuads[5].position.x + GUI_DROPDOWNBOX_INSET,
												    m_BackgroundQuads[5].position.y),
									   sf::Color(105, 105, 105, 255));
	m_BackgroundQuads[9]  = sf::Vertex(sf::Vector2f(m_BackgroundQuads[1].position.x - GUI_DROPDOWNBOX_INSET,
												    m_BackgroundQuads[1].position.y + GUI_DROPDOWNBOX_INSET),
									   sf::Color(105, 105, 105, 255));
	m_BackgroundQuads[10] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[2].position.x - GUI_DROPDOWNBOX_INSET,
												    m_BackgroundQuads[2].position.y - GUI_DROPDOWNBOX_INSET),
									   sf::Color(105, 105, 105, 255));
	m_BackgroundQuads[11] = sf::Vertex(sf::Vector2f(m_BackgroundQuads[6].position.x + GUI_DROPDOWNBOX_INSET,
												    m_BackgroundQuads[6].position.y),
									   sf::Color(105, 105, 105, 255));

	m_ActivatorBounds = sf::FloatRect(m_BackgroundQuads[8].position.x, 
									  m_BackgroundQuads[8].position.y, 
									  m_BackgroundQuads[9].position.x  - m_BackgroundQuads[8].position.x, 
									  m_BackgroundQuads[10].position.y - m_BackgroundQuads[9].position.y);

	setActiveIcon();

	sGame.m_InputManager.registerButton(sf::Mouse::Left);
}

GUIDropDownBox::~GUIDropDownBox(void)
{
	for (unsigned int i = 0; i < m_ExtendedOptions.size(); i += 1)
	{
		mDebugDelete(m_ExtendedOptions.at(i))
		delete m_ExtendedOptions.at(i);
	}

	sGame.m_InputManager.unregisterButton(sf::Mouse::Left);
}


void GUIDropDownBox::update(sf::Time _delta)
{
	if (!m_Update) return;

	if (!sGame.m_InputManager.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_ActivatorBounds.contains((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)))
		{
			if (m_ExtendedState == extendState::CLOSED || m_ExtendedState == extendState::EXTENDED) 
			{
				changeExtension();
			}
		}
	}

	if (m_ExtendedState != extendState::CLOSED && m_ExtendedState != extendState::EXTENDED)
	{
		updateExtension(_delta);
	}

	if (m_ExtendedState == extendState::EXTENDED)
	{
		for (unsigned int i = 0; i < m_ExtendedOptions.size(); i += 1)
		{
			if (m_ExtendedOptions.at(i)->getGlobalBounds().contains((float)(sf::Mouse::getPosition(sGame.m_Window).x), (float)(sf::Mouse::getPosition(sGame.m_Window).y)))
			{
				m_ExtendedOptions.at(i)->setColor(sf::Color::Cyan);
				if (!sGame.m_InputManager.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					m_SelectedOption.setString(m_ExtendedOptions.at(i)->getString());
					changeExtension();
				}
			}
			else
			{
				m_ExtendedOptions.at(i)->setColor(sf::Color::White);
			}
		}

	}
}
void GUIDropDownBox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_BackgroundQuads,			_states);
	_target.draw(m_SelectedOption,			_states);

	_target.draw(m_ActiveIcon,				_states);
	_target.draw(m_ExtendedBackground,		_states);
	
	for (unsigned int i = 0; i < m_OptionsToDraw; i += 1)
	{
		_target.draw(*m_ExtendedOptions.at(i),			_states);
	}
}

void GUIDropDownBox::addOption(std::string _option)
{
	m_ExtendedOptions.push_back(new sf::Text(_option, *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), (unsigned int)(m_Size.y - GUI_DROPDOWNBOX_CHAR_DIFF)));
	mDebugNew(m_ExtendedOptions.back());

	if (m_ExtendedOptions.size() == 1u)
	{
		locateActiveText(0);
	}

	locateListText(m_ExtendedOptions.size());
	
}
std::string GUIDropDownBox::getActiveOption(void)
{
	return m_SelectedOption.getString().toAnsiString();
}

void GUIDropDownBox::changeExtension(void)
{
	m_Extended = !m_Extended;
	setActiveIcon();
	extend();
}
void GUIDropDownBox::extend(void)
{
	if (m_ExtendedState != extendState::CLOSED && m_ExtendedState != extendState::EXTENDED) return;

	if (!m_Extended)
	{
		m_ExtendedState = extendState::RETRACTING;
	}
	else
	{
		m_ExtendedState = extendState::EXTENDINGUP;
		m_ExtendedBackground.resize(4);
		m_ExtendedBackground[0].position = m_BackgroundQuads[3].position;
		m_ExtendedBackground[1].position = m_ExtendedBackground[0].position + sf::Vector2f(m_Size.x - m_Size.y - GUI_DROPDOWNBOX_INSET, 0.0f);
		m_ExtendedBackground[2].position = m_ExtendedBackground[1].position;
		m_ExtendedBackground[3].position = m_ExtendedBackground[0].position;
		m_ExtendedBackground[0].color = sf::Color(125, 125, 125, 255);
		m_ExtendedBackground[1].color = sf::Color(125, 125, 125, 255);
		m_ExtendedBackground[2].color = sf::Color(125, 125, 125, 255);
		m_ExtendedBackground[3].color = sf::Color(125, 125, 125, 255);
	}
}
void GUIDropDownBox::updateExtension(sf::Time _delta)
{
	if (m_ExtendedState == extendState::EXTENDINGUP)
	{
		m_ExtendedBackground[2].position = m_ExtendedBackground[2].position + sf::Vector2f(0.0f, GUI_DROPDOWNBOX_EXT_SPEED * _delta.asSeconds());
		m_ExtendedBackground[3].position = m_ExtendedBackground[3].position + sf::Vector2f(0.0f, GUI_DROPDOWNBOX_EXT_SPEED * _delta.asSeconds());

		if (m_ExtendedBackground[3].position.y - m_ExtendedBackground[0].position.y > m_Size.y * m_ExtendedOptions.size())
		{
			m_ExtendedBackground[2].position = sf::Vector2f(m_ExtendedBackground[2].position.x, m_ExtendedBackground[1].position.y + m_Size.y * m_ExtendedOptions.size());
			m_ExtendedBackground[3].position = sf::Vector2f(m_ExtendedBackground[3].position.x, m_ExtendedBackground[0].position.y +m_Size.y * m_ExtendedOptions.size());
			m_ExtendedState = extendState::EXTENDED;
			m_OptionsToDraw = m_ExtendedOptions.size();
		}
	}
	else if (m_ExtendedState == extendState::RETRACTING)
	{
		m_ExtendedBackground[2].position = m_ExtendedBackground[2].position - sf::Vector2f(0.0f, GUI_DROPDOWNBOX_EXT_SPEED * _delta.asSeconds());
		m_ExtendedBackground[3].position = m_ExtendedBackground[3].position - sf::Vector2f(0.0f, GUI_DROPDOWNBOX_EXT_SPEED * _delta.asSeconds());
		m_OptionsToDraw = 0;

		if (m_ExtendedBackground[3].position.y - m_ExtendedBackground[0].position.y < 0.0f)
		{
			m_ExtendedBackground.resize(0);
			m_ExtendedState = extendState::CLOSED;
		}
	}
}

void GUIDropDownBox::locateActiveText(unsigned int _index)
{
	m_SelectedOption.setString(m_ExtendedOptions.at(_index)->getString().toAnsiString());
	m_SelectedOption.setOrigin(0.0f, m_SelectedOption.getGlobalBounds().height / 2.0f);
	m_SelectedOption.setPosition(m_Position.x - m_Size.x / 2.0f, m_Position.y - 5.0f);
}
void GUIDropDownBox::locateListText(unsigned int _index)
{
	m_ExtendedOptions.back()->setOrigin(0.0f, m_ExtendedOptions.back()->getGlobalBounds().height / 2.0f);
	m_ExtendedOptions.back()->setPosition(m_Position.x - m_Size.x / 2.0f, m_Position.y - 5.0f + _index * m_Size.y);
}

void GUIDropDownBox::setNormalColour(void)
{
}
void GUIDropDownBox::setHoverColour(void)
{
}
void GUIDropDownBox::setClickColour(void)
{
}

void GUIDropDownBox::setActiveIcon(void)
{
	sf::Vector2f  iconPosition = m_Position + sf::Vector2f(m_Size.x / 2.0f - m_Size.y / 2.0f + GUI_DROPDOWNBOX_INSET, 0.0f);

	m_ActiveIcon[0] = sf::Vertex(sf::Vector2f(iconPosition.x - 8.0f,
											  iconPosition.y - 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[1] = sf::Vertex(sf::Vector2f(iconPosition.x - 4.0f,
											  iconPosition.y - 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[2] = sf::Vertex(sf::Vector2f(iconPosition.x + 0.0f,
											  iconPosition.y + 0.0f),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[3] = sf::Vertex(sf::Vector2f(iconPosition.x + 0.0f,
											  iconPosition.y + 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[4] = sf::Vertex(sf::Vector2f(iconPosition.x + 0.0f,
											  iconPosition.y + 0.0f),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[5] = sf::Vertex(sf::Vector2f(iconPosition.x + 4.0f,
											  iconPosition.y - 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[6] = sf::Vertex(sf::Vector2f(iconPosition.x + 8.0f,
											  iconPosition.y - 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
	m_ActiveIcon[7] = sf::Vertex(sf::Vector2f(iconPosition.x + 0.0f,
											  iconPosition.y + 8.0f * (m_Extended ? - 1.0f : 1.0f)),
								 sf::Color(0, 0, 0, 255));
}

