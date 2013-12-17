#include "GUIDropDownBox.h"

#include "Game.h"

#define GUI_DROPDOWNBOX_CHAR_DIFF	6.0f
#define GUI_DROPDOWNBOX_INSET		1.0f

GUIDropDownBox::GUIDropDownBox(sf::Vector2f _position, sf::Vector2f _size) :
	m_Extended(false),
	m_Position(_position),
	m_Size(_size),
	m_BackgroundQuads(sf::Quads, 12)
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
			std::cout << "Active" << std::endl;
		}
	}
}
void GUIDropDownBox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_BackgroundQuads,			_states);
	_target.draw(*m_SelectedOption,			_states);

	if (m_Extended)
	{
		//~ Draw extended icon

		for (unsigned int i = 0; i < m_ExtendedOptions.size(); i += 1)
		{
			_target.draw(*m_ExtendedOptions.at(i),			_states);
		}
	}
	else
	{
		//~ Draw non extended icon
	}
}

void GUIDropDownBox::addOption(std::string _option)
{
	m_ExtendedOptions.push_back(new sf::Text(_option, *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), (unsigned int)(m_Size.y - GUI_DROPDOWNBOX_CHAR_DIFF)));
	mDebugNew(m_ExtendedOptions.back());

	m_SelectedOption = m_ExtendedOptions.front();
	locateActiveText();
}
std::string GUIDropDownBox::getActiveOption(void)
{
	return m_SelectedOption->getString().toAnsiString();
}

void GUIDropDownBox::extend(void)
{
}

void GUIDropDownBox::locateActiveText(void)
{
	m_SelectedOption->setOrigin(0.0f, m_SelectedOption->getGlobalBounds().height / 2.0f);
	m_SelectedOption->setPosition(m_Position.x - m_Size.x / 2.0f, m_Position.y - 5.0f);
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