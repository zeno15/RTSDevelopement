#include "GUICheckbox.h"

#include "GUIManager.h"

#define GUI_CHECKBIX_CHAR_SIZE		20
#define GUI_CHECKBOX_TEXT_OFFSET	sf::Vector2f(15.0f, - 5.0f)
#define GUI_CHECKBOX_SIZE			16.0f
#define GUI_CHECKBOX_INSET			1.0f
#define GUI_CHECKBOX_CHECK_SIZE		10.0f

GUICheckbox::GUICheckbox(sf::Vector2f _position, bool * _selected, std::string _string/* = std::string()*/) :
	m_Position(_position),
	m_Selected(_selected),
	m_HasDescription(false),
	m_SelectedCheckbox(false),
	m_Vertices(sf::Quads, 12)
{
	if (_string != std::string())
	{
		m_HasDescription = true;
		m_Description = sf::Text(_string, *sGUIFONTS->getFont(FontManager::FontID::OPENSANS_REGULAR), GUI_CHECKBIX_CHAR_SIZE);
		m_Description.setOrigin(0.0f, m_Description.getGlobalBounds().height / 2.0f);
		m_Description.setPosition(m_Position + GUI_CHECKBOX_TEXT_OFFSET);
	}

	m_Vertices[0] = sf::Vertex(sf::Vector2f(_position.x - GUI_CHECKBOX_SIZE / 2.0f,
											_position.y - GUI_CHECKBOX_SIZE / 2.0f),
							   sf::Color(55, 55, 55, 255));
	m_Vertices[1] = sf::Vertex(sf::Vector2f(_position.x + GUI_CHECKBOX_SIZE / 2.0f,
											_position.y - GUI_CHECKBOX_SIZE / 2.0f),
							   sf::Color(55, 55, 55, 255));
	m_Vertices[2] = sf::Vertex(sf::Vector2f(_position.x + GUI_CHECKBOX_SIZE / 2.0f,
											_position.y + GUI_CHECKBOX_SIZE / 2.0f),
							   sf::Color(55, 55, 55, 255));
	m_Vertices[3] = sf::Vertex(sf::Vector2f(_position.x - GUI_CHECKBOX_SIZE / 2.0f,
											_position.y + GUI_CHECKBOX_SIZE / 2.0f),
							   sf::Color(55, 55, 55, 255));

	m_Vertices[4] = sf::Vertex(sf::Vector2f(_position.x - GUI_CHECKBOX_SIZE / 2.0f + GUI_CHECKBOX_INSET,
											_position.y - GUI_CHECKBOX_SIZE / 2.0f + GUI_CHECKBOX_INSET),
							   sf::Color(255, 255, 255, 255));
	m_Vertices[5] = sf::Vertex(sf::Vector2f(_position.x + GUI_CHECKBOX_SIZE / 2.0f - GUI_CHECKBOX_INSET,
											_position.y - GUI_CHECKBOX_SIZE / 2.0f + GUI_CHECKBOX_INSET),
							   sf::Color(255, 255, 255, 255));
	m_Vertices[6] = sf::Vertex(sf::Vector2f(_position.x + GUI_CHECKBOX_SIZE / 2.0f - GUI_CHECKBOX_INSET,
											_position.y + GUI_CHECKBOX_SIZE / 2.0f - GUI_CHECKBOX_INSET),
							   sf::Color(255, 255, 255, 255));
	m_Vertices[7] = sf::Vertex(sf::Vector2f(_position.x - GUI_CHECKBOX_SIZE / 2.0f + GUI_CHECKBOX_INSET,
											_position.y + GUI_CHECKBOX_SIZE / 2.0f - GUI_CHECKBOX_INSET),
							  sf::Color(255, 255, 255, 255));

	m_Vertices[8].color  = sf::Color::Black;
	m_Vertices[9].color  = sf::Color::Black;
	m_Vertices[10].color = sf::Color::Black;
	m_Vertices[11].color = sf::Color::Black;

	setCheckbox();

	sGUIINPUT->registerButton(sf::Mouse::Left);
}

GUICheckbox::~GUICheckbox(void)
{
	sGUIINPUT->unregisterButton(sf::Mouse::Left);
}


void GUICheckbox::update(sf::Time _delta)
{
	if (!m_Update) return;

	if (m_Vertices.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
	{
		if (m_SelectedCheckbox)
		{
			if (sGUIINPUT->getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				*m_Selected = !(*m_Selected);
				setCheckbox();
			}
		}
		else
		{
			if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_SelectedCheckbox = true;
			}
		}
	}

}
	
void GUICheckbox::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_Vertices,			_states);

	if (m_HasDescription)	_target.draw(m_Description,			_states);
}

void GUICheckbox::setCheckbox(void)
{
	if (*m_Selected)
	{
		//~ Add select mark
		m_Vertices[8].position  = sf::Vector2f(m_Position.x - GUI_CHECKBOX_CHECK_SIZE / 2.0f,
											   m_Position.y - GUI_CHECKBOX_CHECK_SIZE / 2.0f);
		m_Vertices[9].position  = sf::Vector2f(m_Position.x + GUI_CHECKBOX_CHECK_SIZE / 2.0f,
											   m_Position.y - GUI_CHECKBOX_CHECK_SIZE / 2.0f);
		m_Vertices[10].position = sf::Vector2f(m_Position.x + GUI_CHECKBOX_CHECK_SIZE / 2.0f,
											   m_Position.y + GUI_CHECKBOX_CHECK_SIZE / 2.0f);
		m_Vertices[11].position = sf::Vector2f(m_Position.x - GUI_CHECKBOX_CHECK_SIZE / 2.0f,
											   m_Position.y + GUI_CHECKBOX_CHECK_SIZE / 2.0f);
	}
	else
	{
		//~ Remove select mark
		m_Vertices[8].position  = m_Vertices[0].position;
		m_Vertices[9].position  = m_Vertices[0].position;
		m_Vertices[10].position = m_Vertices[0].position;
		m_Vertices[11].position = m_Vertices[0].position;
	}

	m_SelectedCheckbox = false;
}