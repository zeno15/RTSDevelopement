#include "GUIFrame.h"

#define BORDER_THICKNESS 1.0f

GUIFrame::GUIFrame(sf::FloatRect _bounds/* = sf::FloatRect()*/) :
	m_ToRemove(false),
	m_Display(true),
	m_Update(true)
{
	if (_bounds == sf::FloatRect())
	{
		//~ Just a manager for all the objects, not a visible frame for them to sit on
	}
	else
	{
		sf::Color borderColour		= sf::Color(45, 45, 45, 255);
		sf::Color backgroundColour	= sf::Color(125, 125, 125, 255);

		m_VerticesBackground = sf::VertexArray(sf::Quads, 4);

		m_VerticesBackground[0] = sf::Vertex(sf::Vector2f(_bounds.left,						_bounds.top),					backgroundColour);
		m_VerticesBackground[1] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,		_bounds.top),					backgroundColour);
		m_VerticesBackground[2] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,		_bounds.top + _bounds.height),	backgroundColour);
		m_VerticesBackground[3] = sf::Vertex(sf::Vector2f(_bounds.left,						_bounds.top + _bounds.height),	backgroundColour);
		
		if (_bounds.width > 2.0f * BORDER_THICKNESS && _bounds.height > 2.0f * BORDER_THICKNESS)
		{
			m_VerticesBorder     = sf::VertexArray(sf::LinesStrip, 5);

			m_VerticesBorder[0] = sf::Vertex(sf::Vector2f(_bounds.left + BORDER_THICKNESS,								_bounds.top + BORDER_THICKNESS * 2.0f),						borderColour);
			m_VerticesBorder[1] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width - BORDER_THICKNESS * 2.0f,		_bounds.top + BORDER_THICKNESS * 2.0f),						borderColour);
			m_VerticesBorder[2] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width - BORDER_THICKNESS * 2.0f,		_bounds.top + _bounds.height - BORDER_THICKNESS * 2.0f),	borderColour);
			m_VerticesBorder[3] = sf::Vertex(sf::Vector2f(_bounds.left + BORDER_THICKNESS,								_bounds.top + _bounds.height - BORDER_THICKNESS * 2.0f),	borderColour);
			m_VerticesBorder[4] = sf::Vertex(sf::Vector2f(_bounds.left + BORDER_THICKNESS,								_bounds.top + BORDER_THICKNESS * 2.0f),						borderColour);
		}
	}
}

GUIFrame::~GUIFrame(void)
{
}


void GUIFrame::addObject(GUIObject *_object)
{
	m_Objects.push_back(_object);
}
void GUIFrame::update(sf::Time _delta)
{
	if (!m_Update) return;
	for (unsigned int i = 0; i < m_Objects.size(); i += 1)
	{
		m_Objects.at(i)->update(_delta);
	}
}
void GUIFrame::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_VerticesBackground,		_states);
	_target.draw(m_VerticesBorder,			_states);

	for (unsigned int i = 0; i < m_Objects.size(); i += 1)
	{
		_target.draw(*m_Objects.at(i),		_states);
	}
}

bool GUIFrame::toRemove(void)
{
	return m_ToRemove;
}
void GUIFrame::toggleVisibility(void)
{
	m_Display = !m_Display;
}