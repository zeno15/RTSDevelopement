#include "PathfindingGrid.h"


PathfindingGrid::PathfindingGrid(void)
{
}

PathfindingGrid::~PathfindingGrid(void)
{
}


void PathfindingGrid::initialise(sf::Vector2u _size)
{
	m_GridSize = _size;
	
	m_ObstacleGrid.resize(_size.x * _size.y);

	for (unsigned int i = 0; i < m_ObstacleGrid.size(); i += 1)
	{
		m_ObstacleGrid.at(i).s_CanPass = PathfindingGrid::VALID;
		m_ObstacleGrid.at(i).s_Count   = 0;
	}
}

void PathfindingGrid::addObstacle(unsigned int _x, unsigned int _y)
{
	m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_CanPass = PathfindingGrid::INVALID;
	m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count += 1;
}
void PathfindingGrid::removeObstacle(unsigned int _x, unsigned int _y)
{
	if (m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count == 0)
	{
		m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count = 0;
		m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_CanPass = PathfindingGrid::VALID;
	}
	else
	{
		m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count -= 1;
	}
}

void PathfindingGrid::requestPath(sf::Vector2f _startPos, sf::Vector2f _endPos, std::vector<PathfindingNode *> *_output)
{
	//~ Input is in pixels, convert to tiles

	//~ Create initial starting node and add it to the open list

	//~ REPEAT until destination or failure

		//~ Find the square with the lowest F value on the open list = current square, move to closed list'

		//~ For all 8 squares around the current square

			//~ If it is not passable or on the closed list, ignore it

			//~ If it isn't on the open list, add it to it, and set its parent to the current square, update F, G, H

			//~ If it is already on the open list check G, if it is lower this is a better path, change the parent to the 
			//~ current square and recalculate scores, resort list if keeping sorted one

		//~ If you add the target square to the closed list stop, found fastest path, or if you add the target square to the open
		//~ list you have found a path.  If the open list is empty, there is no path

	//~ Work your way back from the target square via each square's parent, this gives the path

}





