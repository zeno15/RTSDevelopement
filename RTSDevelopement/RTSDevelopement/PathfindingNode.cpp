#include "PathfindingNode.h"

#include <cstdlib>
#include <string>

#include "Game.h"
#include "HelperFunctions.h"

#define PATHFINDINGNODE_NONROOT_TEXTURE		sf::IntRect(0,  992, TILESIZE_i, TILESIZE_i)
#define PATHFINDINGNODE_ROOT_TEXTURE		sf::IntRect(32, 992, TILESIZE_i, TILESIZE_i)

PathfindingNode::PathfindingNode(sf::Vector2u _gridPosition, sf::Vector2u _finalGridPosition, PathfindingNode *_parentNode/* = nullptr*/) :
	m_PathfindingGridCoordinates(_gridPosition),
	m_EndpointGridCoordinates(_finalGridPosition),
	m_ParentNode(_parentNode),
	m_Outline(sf::Vector2f(TILESIZE_f - 2.0f, TILESIZE_f - 2.0f)),
	m_F_Text("0", *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), 8),
	m_G_Text("0", *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), 8),
	m_H_Text("0", *sGame.m_FontManager.getFont(FontManager::FontID::OPENSANS_REGULAR), 8),
	m_ParentPointer(sf::Lines, 2),
	m_ListOption(ListOption::NONE)
{
	m_Outline.setPosition((float)(m_PathfindingGridCoordinates.x) + 1.0f, (float)(m_PathfindingGridCoordinates.y) + 1.0f);
	m_Outline.setFillColor(sf::Color::Transparent);
	m_Outline.setOutlineColor(sf::Color::Blue);
	m_Outline.setOutlineThickness(1.0f);
	
	

	

	m_F_Text.setPosition(m_Outline.getPosition());

	m_G_Text.setOrigin(m_G_Text.getGlobalBounds().left, m_G_Text.getGlobalBounds().top + m_G_Text.getGlobalBounds().height);
	m_G_Text.setPosition(m_Outline.getPosition() + sf::Vector2f(0.0f, TILESIZE_f - 2.0f));

	m_H_Text.setOrigin(m_H_Text.getGlobalBounds().left, m_H_Text.getGlobalBounds().top + m_H_Text.getGlobalBounds().height);
	m_H_Text.setPosition(m_Outline.getPosition() + sf::Vector2f((TILESIZE_f - 2.0f) / 2.0f, TILESIZE_f - 2.0f));
	m_H_Text.setColor(sf::Color(205, 205, 205, 255));

	updateAndPositionText();
}


PathfindingNode::~PathfindingNode(void)
{
}


void PathfindingNode::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Outline,					_states);
	#ifdef _DEBUG
	_target.draw(m_ParentPointer,			_states);
	_target.draw(m_F_Text,					_states);
	_target.draw(m_G_Text,					_states);
	_target.draw(m_H_Text,					_states);
	#endif //~ _DEBUG
}

void PathfindingNode::updateAndPositionText(void)
{
	sf::Vector2u difference = sf::Vector2u((unsigned int)((fabsf)((float)(m_PathfindingGridCoordinates.x / TILESIZE_u) - (float)(m_EndpointGridCoordinates.x / TILESIZE_u))),
										   (unsigned int)((fabsf)((float)(m_PathfindingGridCoordinates.y / TILESIZE_u) - (float)(m_EndpointGridCoordinates.y / TILESIZE_u))));

	m_HValue = (difference.x + difference.y) * 10;

	if (m_ParentNode != nullptr)
	{
		m_GValue = generateGValue(m_ParentNode);
	}
	else
	{
		m_GValue = 0u;
		m_HValue = 0u;
	}

	m_FValue = m_GValue + m_HValue;
	#ifdef _DEBUG
	m_F_Text.setString(std::to_string(m_FValue));
	m_G_Text.setString(std::to_string(m_GValue));
	m_H_Text.setString(std::to_string(m_HValue));

	if (m_ParentNode != nullptr)
	{
		m_ParentPointer[0] = (sf::Vertex(m_Outline.getPosition() + sf::Vector2f(TILESIZE_f / 2.0f, TILESIZE_f / 2.0f), sf::Color::Green));
		m_ParentPointer[1] = (sf::Vertex(m_ParentPointer[0].position  - 0.5f * sf::Vector2f((float)(m_PathfindingGridCoordinates.x) - (float)(m_ParentNode->m_PathfindingGridCoordinates.x), 
																							 (float)(m_PathfindingGridCoordinates.y) - (float)(m_ParentNode->m_PathfindingGridCoordinates.y)),
										  sf::Color::Red));
	}
	#endif //~ _DEBUG
}

void PathfindingNode::changePathEnd(sf::Vector2u _finalGridPosition)
{
	m_EndpointGridCoordinates = _finalGridPosition;

	updateAndPositionText();
}
void PathfindingNode::setParent(PathfindingNode *_parent)
{
	m_ParentNode = _parent;

	updateAndPositionText();
}
PathfindingNode *PathfindingNode::getParent(void)
{
	return m_ParentNode;
}
bool PathfindingNode::changeParent(PathfindingNode *_parent)
{
	return generateGValue(_parent) < generateGValue(m_ParentNode);
}

void PathfindingNode::setFillColour(sf::Color _colour)
{
	m_Outline.setFillColor(_colour);
}

unsigned int PathfindingNode::getFValue(void)
{
	return m_FValue;
}
sf::Vector2u PathfindingNode::getGridCoords(void)
{
	return m_PathfindingGridCoordinates;
}

unsigned int PathfindingNode::generateGValue(PathfindingNode *_parent)
{
	if (_parent->m_PathfindingGridCoordinates.x == m_PathfindingGridCoordinates.x ||
		_parent->m_PathfindingGridCoordinates.y == m_PathfindingGridCoordinates.y)
	{
		return 10u + _parent->m_GValue;
	}
	else
	{
		return 14 + _parent->m_GValue;
	}
}