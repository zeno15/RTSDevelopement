#ifndef INCLUDED_PATHFINDINGGRID_H
#define INCLUDED_PATHFINDINGGRID_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldObject.h"
#include "PathfindingNode.h"

#include "Tile.h"

class PathfindingGrid : public sf::Drawable
{
public:
	PathfindingGrid(void);
	~PathfindingGrid(void);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void changeOverlay(Tile::Type _type);

	void initialise(sf::Vector2u _size);

	void setupAddTile(unsigned int _x, unsigned int _y, Tile _tile);
	void addObstacle(unsigned int _x, unsigned int _y, Tile::Type _type);
	void removeObstacle(unsigned int _x, unsigned int _y, Tile::Type _type);

	void requestPath(sf::Vector2f _startPos, sf::Vector2f _endPos, Tile::Type _type, std::vector<PathfindingNode *> *_output);

private:
	PathfindingNode *findLowestFScoreOnOpenList(void);
	PathfindingNode *findLowestFScoreOnOpenListAndRemove(void);

	sf::Vector2i returnCoordsAroundCentre(unsigned int _index, sf::Vector2u _startCoords = sf::Vector2u());

	bool isNodeOnList(PathfindingNode *_node, PathfindingNode::ListOption _type);

private:
	std::vector<PathfindingNode *>			m_OpenList;
	std::vector<PathfindingNode *>			m_ClosedList;
	std::vector<PathfindingNode>			m_AllNodes;

	struct Obstacle
	{
		std::vector<bool>		s_CanPass;
		std::vector<unsigned int>	s_Count;
	};

	std::vector<Obstacle>					m_ObstacleGrid;

	sf::Vector2u							m_GridSize;

	Tile::Type								m_OverlayType;
};

#endif //~ INCLUDED_PATHFINDINGGRID_H