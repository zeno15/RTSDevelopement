#include "GUIDropDownBox.h"

#include "Game.h"

#define GUI_DROPDOWNBOX_CHAR_SIZE	20u

GUIDropDownBox::GUIDropDownBox(sf::Vector2f _position, sf::Vector2f _size) :
	m_Extended(false),
	m_BackgroundQuads(sf::Quads, 4)
{
	m_BackgroundQuads[0]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												    _position.y - _size.y / 2.0f),
									   sf::Color(205, 205, 205, 255));
	m_BackgroundQuads[1]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												    _position.y - _size.y / 2.0f),
									   sf::Color(205, 205, 205, 255));
	m_BackgroundQuads[2]  = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
												    _position.y + _size.y / 2.0f),
									   sf::Color(205, 205, 205, 255));
	m_BackgroundQuads[3]  = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
												    _position.y + _size.y / 2.0f),
									   sf::Color(205, 205, 205, 255));

	//m_BackgroundQuads[4]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[5]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[6]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[7]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));

	//m_BackgroundQuads[8]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[9]  = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[10] = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));
	//m_BackgroundQuads[11] = sf::Vertex(sf::Vector2f(0.0f,
	//											    0.0f),
	//								   sf::Color(0, 0, 0, 255));

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
}
void GUIDropDownBox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_BackgroundQuads,			_states);
	_target.draw(m_SelectedOption,			_states);

	if (m_Extended)
	{
		for (unsigned int i = 0; i < m_ExtendedOptions.size(); i += 1)
		{
			_target.draw(*m_ExtendedOptions.at(i),			_states);
		}
	}
}

void GUIDropDownBox::addOption(std::string _option)
{
	m_ExtendedOptions.push_back(new sf::Text(_option, *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_DROPDOWNBOX_CHAR_SIZE));
	mDebugNew(m_ExtendedOptions.back());
}
std::string GUIDropDownBox::getActiveOption(void)
{
	return m_SelectedOption.getString().toAnsiString();
}

void GUIDropDownBox::extend(void)
{
}