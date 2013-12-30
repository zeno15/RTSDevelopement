#include "GUIProgressBar.h"

#include "GUIManager.h"


#define GUI_PROGRESS_INSET		1.0f

GUIProgressBar::GUIProgressBar(bool _horizontal, sf::Vector2f _position, sf::Vector2f _size, float *_completedPercentage, float *_underwayPercentage/* = nullptr*/) :
	m_Vertices(sf::Quads, 16),
	m_Size(_size),
	m_CompletedPercentage(_completedPercentage)
{
	if (_underwayPercentage == nullptr)
	{
		_underwayPercentage = nullptr;
	}
	else
	{
		m_UnderwayPercentage = _underwayPercentage;
	}

	m_Vertices[0] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
											_position.y - _size.y / 2.0f),
							   sf::Color(94, 155, 255, 255));
	m_Vertices[1] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
											_position.y - _size.y / 2.0f),
							   sf::Color(94, 155, 255, 255));
	m_Vertices[2] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f,
											_position.y + _size.y / 2.0f),
							   sf::Color(94, 155, 255, 255));
	m_Vertices[3] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f,
											_position.y + _size.y / 2.0f),
							   sf::Color(94, 155, 255, 255));

	m_Vertices[4] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_PROGRESS_INSET,
											_position.y - _size.y / 2.0f + GUI_PROGRESS_INSET),
							   sf::Color(119, 20, 15, 255));
	m_Vertices[5] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_PROGRESS_INSET,
											_position.y - _size.y / 2.0f + GUI_PROGRESS_INSET),
							   sf::Color(119, 20, 15, 255));
	m_Vertices[6] = sf::Vertex(sf::Vector2f(_position.x + _size.x / 2.0f - GUI_PROGRESS_INSET,
											_position.y + _size.y / 2.0f - GUI_PROGRESS_INSET),
							   sf::Color(119, 20, 15, 255));
	m_Vertices[7] = sf::Vertex(sf::Vector2f(_position.x - _size.x / 2.0f + GUI_PROGRESS_INSET,
											_position.y + _size.y / 2.0f - GUI_PROGRESS_INSET),
							   sf::Color(119, 20, 15, 255));

	m_Vertices[8].color  = sf::Color(28, 128, 28, 255);
	m_Vertices[9].color  = sf::Color(28, 128, 28, 255);
	m_Vertices[10].color = sf::Color(28, 128, 28, 255);
	m_Vertices[11].color = sf::Color(28, 128, 28, 255);

	m_Vertices[12].color = sf::Color(255, 165, 0, 255);
	m_Vertices[13].color = sf::Color(255, 165, 0, 255);
	m_Vertices[14].color = sf::Color(255, 165, 0, 255);
	m_Vertices[15].color = sf::Color(255, 165, 0, 255);

	resizeProgressBar();
}

GUIProgressBar::~GUIProgressBar(void)
{
}


void GUIProgressBar::update(sf::Time _delta)
{
	if (!m_Update) return;

	resizeProgressBar();
}
	
void GUIProgressBar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	if (!m_Display) return;

	_target.draw(m_Vertices,				_states);
}

void GUIProgressBar::resizeProgressBar(void)
{
	m_Vertices[8].position  = sf::Vector2f(m_Vertices[0].position.x + GUI_PROGRESS_INSET, m_Vertices[0].position.y + GUI_PROGRESS_INSET);

	m_Vertices[9].position  = m_Vertices[8].position + sf::Vector2f((m_Size.x - 2.0f * GUI_PROGRESS_INSET) * (*m_CompletedPercentage), 0.0f);

	m_Vertices[10].position = m_Vertices[9].position + sf::Vector2f(0.0f, m_Size.y - 2.0f * GUI_PROGRESS_INSET);

	m_Vertices[11].position = m_Vertices[8].position + sf::Vector2f(0.0f, m_Size.y - 2.0f * GUI_PROGRESS_INSET);
		 

	if (m_UnderwayPercentage)
	{
		m_Vertices[12].position = m_Vertices[9].position;

		m_Vertices[13].position = m_Vertices[12].position + sf::Vector2f((m_Size.x - 2.0f * GUI_PROGRESS_INSET) * (*m_UnderwayPercentage), 0.0f);

		m_Vertices[14].position = m_Vertices[13].position + sf::Vector2f(0.0f, m_Size.y - 2.0f * GUI_PROGRESS_INSET);

		m_Vertices[15].position = m_Vertices[12].position + sf::Vector2f(0.0f, m_Size.y - 2.0f * GUI_PROGRESS_INSET);
	}
}