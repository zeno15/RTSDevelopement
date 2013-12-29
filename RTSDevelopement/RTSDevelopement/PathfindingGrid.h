#ifndef INCLUDED_PATHFINDINGGRID_H
#define INCLUDED_PATHFINDINGGRID_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldObject.h"
#include "PathfindingNode.h"



class PathfindingGrid
{
public:
	PathfindingGrid(void);
	~PathfindingGrid(void);

	void initialise(sf::Vector2u _size);

	void addObstacle(unsigned int _x, unsigned int _y);
	void removeObstacle(unsigned int _x, unsigned int _y);

	void requestPath(sf::Vector2f _startPos, sf::Vector2f _endPos, std::vector<PathfindingNode *> *_output);

private:
	enum cellStates {VALID,			//~ Will eventually use things like naval vessel, air, if it can crush etc
					 INVALID,
					 NUMSTATES};

	std::vector<PathfindingNode *>			m_OpenList;
	std::vector<PathfindingNode *>			m_ClosedList;

	struct Obstacle
	{
		cellStates		s_CanPass;
		unsigned int	s_Count;
	};

	std::vector<Obstacle>					m_ObstacleGrid;

	sf::Vector2u							m_GridSize;
};

#endif //~ INCLUDED_PATHFINDINGGRID_H