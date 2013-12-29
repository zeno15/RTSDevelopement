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

	void requestPathfinding(sf::Vector2f _start, sf::Vector2f _finish, WorldObject *_wObj);

private:
	std::vector<PathfindingNode *>			m_OpenList;
	std::vector<PathfindingNode *>			m_ClosedList;
};

#endif //~ INCLUDED_PATHFINDINGGRID_H