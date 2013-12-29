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
	m_ParentPointerSprite(*sGame.m_TextureManager.getTexture(TextureManager::TextureID::TILESHEET), PATHFINDINGNODE_NONROOT_TEXTURE)
{
	m_Outline.setPosition((float)(m_PathfindingGridCoordinates.x) + 1.0f, (float)(m_PathfindingGridCoordinates.y) + 1.0f);
	m_Outline.setFillColor(sf::Color::Transparent);
	m_Outline.setOutlineColor(sf::Color::Blue);
	m_Outline.setOutlineThickness(1.0f);
	

	m_ParentPointerSprite.setOrigin(m_ParentPointerSprite.getGlobalBounds().width / 2.0f,
									m_ParentPointerSprite.getGlobalBounds().height / 2.0f);

	m_ParentPointerSprite.setPosition(m_Outline.getPosition() + sf::Vector2f(TILESIZE_f / 2.0f, TILESIZE_f / 2.0f));


	if (m_ParentNode == nullptr)
	{
		m_ParentPointerSprite.setTextureRect(PATHFINDINGNODE_ROOT_TEXTURE);
	}
	else
	{
		float o = (float)(m_PathfindingGridCoordinates.y) - (float)(m_ParentNode->m_PathfindingGridCoordinates.y);
		float a = (float)(m_PathfindingGridCoordinates.x) - (float)(m_ParentNode->m_PathfindingGridCoordinates.x);
		float h = sqrtf(a * a + o * o);

		if (o != 0.0f && a != 0.0f)
		{
			m_ParentPointerSprite.setRotation(TO_DEGREES * (atanf(o / a)));
			std::cout << "T - Rotation: " << m_ParentPointerSprite.getRotation() << std::endl;
		}
		else if (o == 0.0f)
		{
			m_ParentPointerSprite.setRotation(TO_DEGREES * (acosf(a / h)));
			std::cout << "A - Rotation: " << m_ParentPointerSprite.getRotation() << std::endl;
		}
		else 
		{
			m_ParentPointerSprite.setRotation(TO_DEGREES * (asinf(o / h)));
			std::cout << "S - Roation: " << m_ParentPointerSprite.getRotation() << std::endl;
		}

		
		
	}

	updateAndPositionText();
}


PathfindingNode::~PathfindingNode(void)
{
}


void PathfindingNode::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Outline,					_states);
	_target.draw(m_F_Text,					_states);
	_target.draw(m_G_Text,					_states);
	_target.draw(m_H_Text,					_states);
	_target.draw(m_ParentPointerSprite,		_states);
}

void PathfindingNode::updateAndPositionText(void)
{
	m_HValue = 10u * (abs((int)(m_PathfindingGridCoordinates.x - m_EndpointGridCoordinates.x)) + abs((int)(m_PathfindingGridCoordinates.y - m_EndpointGridCoordinates.y))) / TILESIZE_u;

	if (m_ParentNode != nullptr)
	{
		if (m_ParentNode->m_PathfindingGridCoordinates.x == m_PathfindingGridCoordinates.x ||
			m_ParentNode->m_PathfindingGridCoordinates.y == m_PathfindingGridCoordinates.y)
		{
			m_GValue = 10u;
		}
		else
		{
			m_GValue = 14;
		}
	}
	else
	{
		m_GValue = 0u;
		m_HValue = 0u;
	}

	m_FValue = m_GValue + m_HValue;

	m_F_Text.setPosition(m_Outline.getPosition());
	m_F_Text.setString(std::to_string(m_FValue));

	m_G_Text.setString(std::to_string(m_GValue));
	m_G_Text.setOrigin(m_G_Text.getGlobalBounds().left, m_G_Text.getGlobalBounds().top + m_G_Text.getGlobalBounds().height);
	m_G_Text.setPosition(m_Outline.getPosition() + sf::Vector2f(0.0f, TILESIZE_f - 2.0f));

	m_H_Text.setString(std::to_string(m_HValue));
	m_H_Text.setOrigin(m_H_Text.getGlobalBounds().left + m_H_Text.getGlobalBounds().width, m_H_Text.getGlobalBounds().top + m_H_Text.getGlobalBounds().height);
	m_H_Text.setPosition(m_Outline.getPosition() + sf::Vector2f(TILESIZE_f - 2.0f, TILESIZE_f - 2.0f));
}

void PathfindingNode::changePathEnd(sf::Vector2u _finalGridPosition)
{
	m_EndpointGridCoordinates = _finalGridPosition;

	updateAndPositionText();
}