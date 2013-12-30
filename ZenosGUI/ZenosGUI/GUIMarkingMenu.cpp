#include "GUIMarkingMenu.h"

#include "GUIManager.h"


GUIMarkingMenu::GUIMarkingMenu(void) :
	m_ActiveState(false),
	m_RawLine(sf::LinesStrip, 0),
	m_TurnPointLine(sf::LinesStrip, 0)
{
	sGUIINPUT->registerButton(sf::Mouse::Right);
}

GUIMarkingMenu::~GUIMarkingMenu(void)
{
	sGUIINPUT->unregisterButton(sf::Mouse::Right);
}


void GUIMarkingMenu::update(sf::Time _delta)
{
	if (!sGUIINPUT->getButtonState(sf::Mouse::Right) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//std::cout << "Right press" << std::endl;
		m_ActiveState = true;
		m_RawPoints.push_back(sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y)));
	}
	if (sGUIINPUT->getButtonState(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//std::cout << "Right release" << std::endl;
		m_ActiveState = false;
		
		m_RawLine.clear();

		for (unsigned int i = 0; i < m_RawPoints.size(); i += 1)
		{
			m_RawLine.append(sf::Vertex(m_RawPoints.at(i)));
		}

		calculateTurningPointLine();
		
		m_RawPoints.clear();
	}

	if (m_ActiveState)
	{
		sf::Vector2f currentPoint = sf::Vector2f((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y));

		if (distance2d(currentPoint, m_RawPoints.back()) > 25.0f)
		{
			m_RawPoints.push_back(currentPoint);
			//std::cout << "Appending point" << std::endl;
		}
	}
}
void GUIMarkingMenu::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_RawLine,				_states);
	_target.draw(m_TurnPointLine,		_states);
}

void GUIMarkingMenu::calculateTurningPointLine(void)
{
	if (m_RawLine.getVertexCount() < 3u) return;

	m_TurnPointLine.clear();

	m_TurnPointLine.append(sf::Vertex(m_RawLine[0].position, sf::Color::Red));

	for (unsigned int i = 1; i < m_RawLine.getVertexCount() - 1; i += 1)
	{
		sf::Vector2f change1 = m_RawLine[i - 1].position - m_RawLine[i].position;
		sf::Vector2f change2 = m_RawLine[i].position - m_RawLine[i + 1].position;

		if (signChange2d(change1, change2))
		{
			m_TurnPointLine.append(sf::Vertex(m_RawLine[i].position, sf::Color::Red));
		}
	}

	m_TurnPointLine.append(sf::Vertex(m_RawLine[m_RawLine.getVertexCount() - 1].position, sf::Color::Red));
}

void GUIMarkingMenu::addNode(GUIMarkingMenuNode *_node)
{
	repositionNodes();
}

void GUIMarkingMenu::repositionNodes(void)
{

}