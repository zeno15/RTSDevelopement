#include "GUISlider.h"

#include "GUIManager.h"


#define GUI_SLIDE_INSET 1.0f
#define GUI_SLIDE_SIZE  sf::Vector2f(12.0f, 20.0f)

GUISlider::GUISlider(bool _horizontal, sf::Vector2f _position, float _size, unsigned int _gradiated/* = 0*/) :
	m_Lines(sf::Lines, 6 + _gradiated * 4),
	m_Slide(sf::Quads, 8),
	m_State(slideColourState::NORMAL),
	m_Gradiated(_gradiated > 1),		//~ Can have a no middle ground 0 or 100 option
	m_Position(_position),
	m_Size(_size),
	m_Horizontal(_horizontal)
{

	m_Lines[0] = sf::Vertex(sf::Vector2f(_position.x - (_size / 2.0f) * m_Horizontal, 
										 _position.y - (_size / 2.0f) * !m_Horizontal),	
										 sf::Color(155, 155, 155, 255));
	m_Lines[1] = sf::Vertex(sf::Vector2f(_position.x + (_size / 2.0f) * m_Horizontal, 
										 _position.y + (_size / 2.0f) * !m_Horizontal),	
										 sf::Color(155, 155, 155, 255));

	m_Lines[2] = sf::Vertex(m_Lines[0].position + sf::Vector2f(- 1.0f * !m_Horizontal, - 1.0f * m_Horizontal),		
							sf::Color(215, 215, 215, 255));
	m_Lines[3] = sf::Vertex(m_Lines[1].position + sf::Vector2f(- 1.0f * !m_Horizontal, - 1.0f * m_Horizontal),		
							sf::Color(215, 215, 215, 255));

	m_Lines[4] = sf::Vertex(m_Lines[0].position + sf::Vector2f(+ 1.0f * !m_Horizontal, + 1.0f * m_Horizontal),		
							sf::Color(75, 75, 75, 255));
	m_Lines[5] = sf::Vertex(m_Lines[1].position + sf::Vector2f(+ 1.0f * !m_Horizontal, + 1.0f * m_Horizontal),		
							sf::Color(75, 75, 75, 255));

	if (m_Gradiated)
	{
		m_Offset = m_Size / (float)(_gradiated - 1u);

		for (unsigned int i = 6; i < m_Lines.getVertexCount(); i += 4)
		{
			float currentOffset = m_Offset * ((i - 6u) / 4u);

			m_Lines[i + 0] = sf::Vertex(sf::Vector2f((_position.x  - m_Size / 2.0f + currentOffset + 0.0f) * m_Horizontal + (_position.x + 4.0f) * !m_Horizontal, 
										(_position.y + 4.0f) * m_Horizontal + (_position.y  - m_Size / 2.0f + currentOffset + 0.0f) * !m_Horizontal), 
										sf::Color(215, 215, 215, 255));
			m_Lines[i + 1] = sf::Vertex(sf::Vector2f((_position.x  - m_Size / 2.0f + currentOffset + 0.0f) * m_Horizontal + (_position.x + 8.0f) * !m_Horizontal, 
										(_position.y + 8.0f) * m_Horizontal + (_position.y  - m_Size / 2.0f + currentOffset + 0.0f) * !m_Horizontal), 
										sf::Color(215, 215, 215, 255));

			m_Lines[i + 2] = sf::Vertex(sf::Vector2f((_position.x  - m_Size / 2.0f + currentOffset + 1.0f) * m_Horizontal + (_position.x + 4.0f) * !m_Horizontal, 
										(_position.y + 4.0f) * m_Horizontal + (_position.y  - m_Size / 2.0f + currentOffset + 1.0f) * !m_Horizontal), 
										sf::Color(75, 75, 75, 255));
			m_Lines[i + 3] = sf::Vertex(sf::Vector2f((_position.x  - m_Size / 2.0f + currentOffset + 1.0f) * m_Horizontal + (_position.x + 8.0f) * !m_Horizontal, 
										(_position.y + 8.0f) * m_Horizontal + (_position.y  - m_Size / 2.0f + currentOffset + 1.0f) * !m_Horizontal), 
										sf::Color(75, 75, 75, 255));
		}
	}

	

	setSlidePosition(_position - sf::Vector2f(m_Horizontal * (m_Size / 2.0f), !m_Horizontal * (m_Size / 2.0f)));

	setNormalColour();

	sGUIINPUT->registerButton(sf::Mouse::Left);
}

GUISlider::~GUISlider(void)
{
	sGUIINPUT->unregisterButton(sf::Mouse::Left);
}


void GUISlider::update(sf::Time _delta)
{
	if (!m_Update) return;

	slideColourState prevState = m_State;
	

	if (m_State == slideColourState::CLICKED)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//~ Continue updating position
			sf::Vector2f newPosition;

			if (m_Horizontal)
			{
				newPosition = sf::Vector2f(clamp((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), m_Position.x - m_Size / 2.0f, m_Position.x + m_Size / 2.0f), m_Position.y);
			}
			else
			{
				newPosition = sf::Vector2f(m_Position.x, clamp((float)(sf::Mouse::getPosition(*sGUIWINDOW).y), m_Position.y - m_Size / 2.0f, m_Position.y + m_Size / 2.0f));
			}
			
			if (m_Gradiated)
			{
				if (m_Horizontal)
				{
					newPosition.x = (int)((newPosition.x - m_Position.x + m_Size / 2.0f + m_Offset / 2.0f) / m_Offset) * (float)(m_Offset) + m_Position.x - m_Size / 2.0f;
				}
				else
				{
					newPosition.y = (int)((newPosition.y - m_Position.y + m_Size / 2.0f + m_Offset / 2.0f) / m_Offset) * (float)(m_Offset) + m_Position.y - m_Size / 2.0f;
				}
			}

			setSlidePosition(newPosition);
		}
		else
		{
			setSlideColour(slideColourState::NORMAL);
		}
	}
	else
	{
		if (m_Slide.getBounds().contains(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				setSlideColour(slideColourState::CLICKED);
			}
			else
			{
				setSlideColour(slideColourState::HOVERED);
			}
		}
		else
		{
			setSlideColour(slideColourState::NORMAL);
		}
	}

	if (prevState != m_State && prevState == slideColourState::CLICKED)
	{
		if (m_Horizontal)
		{
			float percentage = ((m_Slide.getBounds().left + m_Slide.getBounds().width / 2.0f) - (m_Position.x - m_Size / 2.0f)) / m_Size;
			notifyReceivers(MessageData::MessageType::SLIDER_UPDATED, percentage);
		}
		else
		{
			float percentage = ((m_Slide.getBounds().top + m_Slide.getBounds().height / 2.0f) - (m_Position.y - m_Size / 2.0f)) / m_Size;
			notifyReceivers(MessageData::MessageType::SLIDER_UPDATED, percentage);
		}
	}
}
	
void GUISlider::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_Lines,		_states);
	_target.draw(m_Slide,		_states);
}

void GUISlider::setSlidePosition(sf::Vector2f _position)
{
	if (m_Horizontal)
	{
		m_Slide[0].position = sf::Vector2f(- GUI_SLIDE_SIZE.x / 2.0f, - GUI_SLIDE_SIZE.y / 2.0f) + _position;
		m_Slide[1].position = sf::Vector2f(+ GUI_SLIDE_SIZE.x / 2.0f, - GUI_SLIDE_SIZE.y / 2.0f) + _position;
		m_Slide[2].position = sf::Vector2f(+ GUI_SLIDE_SIZE.x / 2.0f, + GUI_SLIDE_SIZE.y / 2.0f) + _position;
		m_Slide[3].position = sf::Vector2f(- GUI_SLIDE_SIZE.x / 2.0f, + GUI_SLIDE_SIZE.y / 2.0f) + _position;
	}
	else
	{
		m_Slide[0].position = sf::Vector2f(- GUI_SLIDE_SIZE.y / 2.0f, - GUI_SLIDE_SIZE.x / 2.0f) + _position;
		m_Slide[1].position = sf::Vector2f(+ GUI_SLIDE_SIZE.y / 2.0f, - GUI_SLIDE_SIZE.x / 2.0f) + _position;
		m_Slide[2].position = sf::Vector2f(+ GUI_SLIDE_SIZE.y / 2.0f, + GUI_SLIDE_SIZE.x / 2.0f) + _position;
		m_Slide[3].position = sf::Vector2f(- GUI_SLIDE_SIZE.y / 2.0f, + GUI_SLIDE_SIZE.x / 2.0f) + _position;
	}

	m_Slide[4].position = m_Slide[0].position + sf::Vector2f(+ GUI_SLIDE_INSET, + GUI_SLIDE_INSET);
	m_Slide[5].position = m_Slide[1].position + sf::Vector2f(- GUI_SLIDE_INSET, + GUI_SLIDE_INSET);
	m_Slide[6].position = m_Slide[2].position + sf::Vector2f(- GUI_SLIDE_INSET, - GUI_SLIDE_INSET);
	m_Slide[7].position = m_Slide[3].position + sf::Vector2f(+ GUI_SLIDE_INSET, - GUI_SLIDE_INSET);
}

void GUISlider::setSlideColour(slideColourState _state)
{
	if (_state == m_State) return;

	m_State = _state;

	switch (m_State)
	{
	case (slideColourState::HOVERED):
		setHoverColour();
		break;
	case (slideColourState::CLICKED):
		setClickedColour();
		break;
	case (slideColourState::NORMAL):
		setNormalColour();
	default:
		break;
	}
}

void GUISlider::setNormalColour(void)
{
	m_Slide[0].color = sf::Color(94, 155, 255, 255);
	m_Slide[1].color = sf::Color(94, 155, 255, 255);
	m_Slide[2].color = sf::Color(94, 155, 255, 255);
	m_Slide[3].color = sf::Color(94, 155, 255, 255);

	m_Slide[4].color = sf::Color(100, 100, 100, 255);
	m_Slide[5].color = sf::Color(100, 100, 100, 255);
	m_Slide[6].color = sf::Color(100, 100, 100, 255);
	m_Slide[7].color = sf::Color(100, 100, 100, 255);
}
void GUISlider::setHoverColour(void)
{
	m_Slide[0].color = sf::Color::Yellow;
	m_Slide[1].color = sf::Color::Yellow;
	m_Slide[2].color = sf::Color::Yellow;
	m_Slide[3].color = sf::Color::Yellow;

	m_Slide[4].color = sf::Color(100, 100, 100, 255);
	m_Slide[5].color = sf::Color(100, 100, 100, 255);
	m_Slide[6].color = sf::Color(100, 100, 100, 255);
	m_Slide[7].color = sf::Color(100, 100, 100, 255);
}
void GUISlider::setClickedColour(void)
{
	m_Slide[0].color = sf::Color::Green;
	m_Slide[1].color = sf::Color::Green;
	m_Slide[2].color = sf::Color::Green;
	m_Slide[3].color = sf::Color::Green;

	m_Slide[4].color = sf::Color(70, 70, 70, 255);
	m_Slide[5].color = sf::Color(70, 70, 70, 255);
	m_Slide[6].color = sf::Color(70, 70, 70, 255);
	m_Slide[7].color = sf::Color(70, 70, 70, 255);
}