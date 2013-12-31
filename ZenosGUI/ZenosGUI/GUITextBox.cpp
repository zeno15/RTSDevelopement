#include "GUITextBox.h"

#include "GUIManager.h"

#define GUI_TEXTBOX_INSET				1.0f
#define GUI_TEXTBOX_TEXT_SIZE_DIFF		6.0f
#define GUI_TEXTBOX_CURSOR_WIDTH		2.0f


GUITextBox::GUITextBox(sf::Vector2f _position, sf::Vector2f _size, TextBoxType _type, bool _scrolls/* = false*/) :
	m_Box(sf::Quads, 12),
	m_Scrolls(_scrolls),
	m_Active(false),
	m_Type(_type)
{
	m_Box[0] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
									   _position.y - _size.y / 2.0f),
						  sf::Color(94, 155, 255, 255));
	m_Box[1] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
									   _position.y - _size.y / 2.0f),
						  sf::Color(94, 155, 255, 255));
	m_Box[2] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
									   _position.y + _size.y / 2.0f),
						  sf::Color(94, 155, 255, 255));
	m_Box[3] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
									   _position.y + _size.y / 2.0f),
						  sf::Color(94, 155, 255, 255));

	m_Box[4] = sf::Vertex(sf::Vector2f(m_Box[0].position.x + GUI_TEXTBOX_INSET,
									   m_Box[0].position.y + GUI_TEXTBOX_INSET),
						  sf::Color(195, 195, 195, 255));
	m_Box[5] = sf::Vertex(sf::Vector2f(m_Box[1].position.x - GUI_TEXTBOX_INSET,
									   m_Box[1].position.y + GUI_TEXTBOX_INSET),
						  sf::Color(195, 195, 195, 255));
	m_Box[6] = sf::Vertex(sf::Vector2f(m_Box[2].position.x - GUI_TEXTBOX_INSET,
									   m_Box[2].position.y - GUI_TEXTBOX_INSET),
						  sf::Color(195, 195, 195, 255));
	m_Box[7] = sf::Vertex(sf::Vector2f(m_Box[3].position.x + GUI_TEXTBOX_INSET,
									   m_Box[3].position.y - GUI_TEXTBOX_INSET),
						  sf::Color(195, 195, 195, 255));

	m_Box[8].color  = sf::Color::Black;
	m_Box[9].color  = sf::Color::Black;
	m_Box[10].color = sf::Color::Black;
	m_Box[11].color = sf::Color::Black;


	m_Text = sf::Text("TEST_TEXT", *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), (unsigned int)(_size.y - GUI_TEXTBOX_TEXT_SIZE_DIFF));
	m_Text.setOrigin(0.0f, m_Text.getGlobalBounds().top + m_Text.getGlobalBounds().height / 2.0f);
	m_Text.setPosition(_position.x - _size.x / 2.0f + GUI_TEXTBOX_TEXT_SIZE_DIFF / 2.0f, _position.y);
	m_Text.setColor(sf::Color::Black);

	m_Text.setString(m_DisplayedString);
	updateCursorPosition();

	sGUIMANAGER.addGUITextBoxToReceiveText(this);
}

GUITextBox::~GUITextBox(void)
{
	sGUIMANAGER.removeGUITextBoxToReceiveText(this);
}


void GUITextBox::update(sf::Time _delta)
{
	if (!m_Update) return;


	if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_Box.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			m_Active = true;
		}
		else
		{
			m_Active = false;
		}
	}

	if (m_Active)
	{
		while (m_PendingChars.size() > 0)
		{
			if (m_PendingChars.front() == '\b')
			{
				if (m_DisplayedString.size() > 0) m_DisplayedString.pop_back();
			}
			else if (m_PendingChars.front() == '\r')
			{
				m_Active = false;
			}
			else
			{
				if (m_Type == TextBoxType::REGULAR)
				{
					m_DisplayedString += m_PendingChars.front();
				}
				else if (m_Type == TextBoxType::NUMERICAL)
				{
					char *numbers = "0123456789";
					for (unsigned int i = 0; i < 10; i += 1)
					{
						if (numbers[i] == m_PendingChars.front())
						{
							m_DisplayedString += m_PendingChars.front();
							break;
						}
					}
				}
			}
			m_PendingChars.erase(m_PendingChars.begin());
		}

		m_Text.setString(m_DisplayedString);

		if (m_Scrolls)
		{
			unsigned int charsRemoved = 0;
			std::string tempString = m_DisplayedString;

			while (m_Text.getGlobalBounds().width > m_Box.getBounds().width - GUI_TEXTBOX_TEXT_SIZE_DIFF)
			{
				if (tempString.size() > 0)
				{
					tempString.erase(tempString.begin());

					m_Text.setString(tempString);
				}
			}
		}
		else
		{
			while (m_Text.getGlobalBounds().width > m_Box.getBounds().width - GUI_TEXTBOX_TEXT_SIZE_DIFF)
			{
				if (m_DisplayedString.size() > 0)
				{
					m_DisplayedString.pop_back();

					m_Text.setString(m_DisplayedString);
				}
			}
		}

		
	}

	updateCursorPosition();
}
	
void GUITextBox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_Box,		_states);
	_target.draw(m_Text,	_states);
	_target.draw(m_Label,	_states);
}

bool GUITextBox::active(void)
{
	return m_Active;
}

void GUITextBox::appendTextInput(char _character)
{
	m_PendingChars.push_back(_character);
}

std::string GUITextBox::getString(void)
{
	return m_DisplayedString;
}

void GUITextBox::updateCursorPosition(void)
{
	if (m_Active)
	{
		m_Box.resize(12);
		m_Box[8].position  = sf::Vector2f(m_Text.getGlobalBounds().width,  - (float)(m_Text.getCharacterSize()) / 2.0f) + m_Text.getPosition();
		m_Box[9].position  = sf::Vector2f(GUI_TEXTBOX_CURSOR_WIDTH,			0.0f)								+ m_Box[8].position;
		m_Box[10].position = sf::Vector2f(0.0f,								(float)(m_Text.getCharacterSize())) + m_Box[9].position;
		m_Box[11].position = sf::Vector2f(0.0f,								(float)(m_Text.getCharacterSize())) + m_Box[8].position;

		m_Box[8].color  = sf::Color::Black;
		m_Box[9].color  = sf::Color::Black;
		m_Box[10].color = sf::Color::Black;
		m_Box[11].color = sf::Color::Black;
	}
	else
	{
		m_Box.resize(8);
	}
}

void GUITextBox::setLabel(std::string _text, LabelPosition _position)
{
	m_Label = sf::Text(_text, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), m_Text.getCharacterSize());

	//m_Label.setOrigin((m_Label.getGlobalBounds().left + m_Label.getGlobalBounds().width) / 2.0f, (m_Label.getGlobalBounds().top + m_Label.getGlobalBounds().height) / 2.0f);

	switch (_position)
	{
	case (LabelPosition::ABOVE):
		m_Label.setOrigin((m_Label.getGlobalBounds().left + m_Label.getGlobalBounds().width) / 2.0f, (m_Label.getGlobalBounds().top + m_Label.getGlobalBounds().height));
		m_Label.setPosition(sf::Vector2f(m_Box.getBounds().left + m_Box.getBounds().width / 2.0f, m_Box.getBounds().top + m_Box.getBounds().height / 2.0f) + sf::Vector2f(0.0f, - m_Box.getBounds().height));
		break;
	case (LabelPosition::LEFT):
		m_Label.setOrigin((m_Label.getGlobalBounds().left + m_Label.getGlobalBounds().width), (m_Label.getGlobalBounds().top + m_Label.getGlobalBounds().height) / 2.0f);
		m_Label.setPosition(sf::Vector2f(m_Box.getBounds().left + m_Box.getBounds().width / 2.0f, m_Box.getBounds().top + m_Box.getBounds().height / 2.0f) + sf::Vector2f(- m_Box.getBounds().width, 0.0f));
		break;
	case (LabelPosition::RIGHT):
		m_Label.setOrigin(m_Label.getGlobalBounds().left, (m_Label.getGlobalBounds().top + m_Label.getGlobalBounds().height) / 2.0f);
		m_Label.setPosition(sf::Vector2f(m_Box.getBounds().left + m_Box.getBounds().width / 2.0f, m_Box.getBounds().top + m_Box.getBounds().height / 2.0f) + sf::Vector2f(+ m_Box.getBounds().width, 0.0f));
		break;
	case (LabelPosition::BELOW):
	default:
		m_Label.setOrigin((m_Label.getGlobalBounds().left + m_Label.getGlobalBounds().width) / 2.0f, m_Label.getGlobalBounds().top);
		m_Label.setPosition(sf::Vector2f(m_Box.getBounds().left + m_Box.getBounds().width / 2.0f, m_Box.getBounds().top + m_Box.getBounds().height / 2.0f) + sf::Vector2f(0.0f, + m_Box.getBounds().height));
		break;
	};
}