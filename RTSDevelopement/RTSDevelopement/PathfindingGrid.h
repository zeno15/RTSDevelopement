#ifndef INCLUDED_PATHFINDINGGRID_H
#define INCLUDED_PATHFINDINGGRID_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldObject.h"
#include "PathfindingNode.h"

class PathfindingGrid : public sf::Drawable
{
public:
	PathfindingGrid(void);
	~PathfindingGrid(void);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void initialise(sf::Vector2u _size);

	void addObstacle(unsigned int _x, unsigned int _y);
	void removeObstacle(unsigned int _x, unsigned int _y);

	void requestPath(sf::Vector2f _startPos, sf::Vector2f _endPos, std::vector<PathfindingNode *> *_output);

private:
	PathfindingNode *findLowestFScoreOnOpenList(void);
	PathfindingNode *findLowestFScoreOnOpenListAndRemove(void);

	sf::Vector2i returnCoordsAroundCentre(unsigned int _index, sf::Vector2u _startCoords = sf::Vector2u());

	bool isNodeOnList(PathfindingNode *_node, PathfindingNode::ListOption _type);

private:
	enum cellStates {VALID,			//~ Will eventually use things like naval vessel, air, if it can crush etc
					 INVALID,
					 NUMSTATES};

	std::vector<PathfindingNode *>			m_OpenList;
	std::vector<PathfindingNode *>			m_ClosedList;
	std::vector<PathfindingNode>			m_AllNodes;

	struct Obstacle
	{
		cellStates		s_CanPass;
		unsigned int	s_Count;
	};

	std::vector<Obstacle>					m_ObstacleGrid;

	sf::Vector2u							m_GridSize;

	sf::Clock mclock;
	sf::Time	timer;
	sf::Time	timer2;
	sf::Time	timer3;
};

#endif //~ INCLUDED_PATHFINDINGGRID_H