#ifndef INCLUDED_PATHFINDINGNODE_H
#define INCLUDED_PATHFINDINGNODE_H

#include <SFML/Graphics.hpp>

class PathfindingNode : public sf::Drawable
{
public:
	PathfindingNode(sf::Vector2u _gridPosition, sf::Vector2u _finalGridPosition, PathfindingNode *_parentNode = nullptr);
	~PathfindingNode(void);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void changePathEnd(sf::Vector2u _finalGridPosition);
	void setParent(PathfindingNode *_parent);
	PathfindingNode *getParent(void);
	bool changeParent(PathfindingNode *_parent);

	void setFillColour(sf::Color _colour);

	unsigned int getFValue(void);
	sf::Vector2u getGridCoords(void);
	sf::Vector2u getEndGridCoords(void);

	void setInitialisationTime(unsigned int _time);
	unsigned int getInitalisationTime(void);

	void reset(void);

	enum ListOption {NONE,
					 OPEN,
					 CLOSED};

	ListOption						m_ListOption;

private:
	void updateAndPositionText(void);
	unsigned int generateGValue(PathfindingNode *_parent);

public:
	sf::Vector2u					m_PathfindingGridCoordinates;
	sf::Vector2u					m_EndpointGridCoordinates;

	PathfindingNode *				m_ParentNode;

	sf::Text						m_F_Text;
	unsigned int					m_FValue;
	sf::Text						m_G_Text;
	unsigned int					m_GValue;
	sf::Text						m_H_Text;
	unsigned int					m_HValue;

	unsigned int					m_InitialisationTime;

	sf::VertexArray					m_ParentPointer;

	sf::RectangleShape				m_Outline;
};

#endif //~ INCLUDED_PATHFINDINGNODE_H