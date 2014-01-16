#include "PathfindingGrid.h"

#include "Game.h"

PathfindingGrid::PathfindingGrid(void) :
	m_OverlayType(Tile::Type::NUM_TYPES)
{
}

PathfindingGrid::~PathfindingGrid(void)
{
}


void PathfindingGrid::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	sf::RectangleShape temp = sf::RectangleShape(sf::Vector2f(TILESIZE_f, TILESIZE_f));
	temp.setFillColor(sf::Color(255, 0, 0, 255));

	for (unsigned int i = 0; i < m_GridSize.y; i += 1)
	{
		for (unsigned int j = 0; j < m_GridSize.x; j += 1)
		{
			if (m_OverlayType != Tile::Type::NUM_TYPES &&
				!m_ObstacleGrid.at(i * m_GridSize.x + j).s_CanPass.at(m_OverlayType))
			{
				temp.setPosition((float)(j * TILESIZE_f), (float)(i * TILESIZE_f));
				_target.draw(temp,		_states);
			}
		}
	}
}

void PathfindingGrid::changeOverlay(Tile::Type _type)
{
	m_OverlayType = _type;
}

void PathfindingGrid::initialise(sf::Vector2u _size)
{
	m_GridSize = _size;
	
	m_ObstacleGrid.resize(_size.x * _size.y);

	for (unsigned int i = 0; i < m_GridSize.y; i += 1)
	{
		for (unsigned int j = 0; j < m_GridSize.x; j += 1)
		{
			m_ObstacleGrid.at(i * m_GridSize.x + j).s_CanPass.resize(Tile::Type::NUM_TYPES, true);
			m_ObstacleGrid.at(i * m_GridSize.x + j).s_Count.resize(Tile::Type::NUM_TYPES, 0);

			m_AllNodes.push_back(PathfindingNode(sf::Vector2u(j * TILESIZE_u, i * TILESIZE_u), sf::Vector2u()));
		}
	}

}

void PathfindingGrid::setupAddTile(unsigned int _x, unsigned int _y, Tile _tile)
{
	for (unsigned int i = 0; i < Tile::Type::NUM_TYPES; i += 1)
	{
		if (!_tile.m_TileUnitPassValues.at(i))
		{
			addObstacle(_x, _y, (Tile::Type)(i));
		}
	}
}
void PathfindingGrid::addObstacle(unsigned int _x, unsigned int _y, Tile::Type _type)
{
	m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_CanPass.at(_type) = false;
	m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count.at(_type) += 1;
}
void PathfindingGrid::removeObstacle(unsigned int _x, unsigned int _y, Tile::Type _type)
{
	if (m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count.at(_type) == 0)
	{
		m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_CanPass.at(_type) = true;
	}
	else
	{
		m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_Count.at(_type) -= 1;
	}
}

void PathfindingGrid::requestPath(sf::Vector2f _startPos, sf::Vector2f _endPos, Tile::Type _type, std::vector<PathfindingNode *> *_output)
{
	//~ Implement something to check if the destination is traversable, if not return immediately

	sf::Clock clock;

	m_OpenList.clear();
	m_ClosedList.clear();

	unsigned int initTime = (unsigned int)(time(nullptr));

	//~ Input is in pixels, convert to tiles
	sf::Vector2u startNodeCoords  = sf::Vector2u((unsigned int)(_startPos.x / TILESIZE_f), (unsigned int)(_startPos.y / TILESIZE_f));
	sf::Vector2u finishNodeCoords = sf::Vector2u((unsigned int)(_endPos.x / TILESIZE_f), (unsigned int)(_endPos.y / TILESIZE_f));

	PathfindingNode *endNode = &m_AllNodes.at(finishNodeCoords.y * m_GridSize.x + finishNodeCoords.x);

	m_OpenList.push_back(&m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x));
	m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x).m_ListOption = PathfindingNode::ListOption::OPEN;
	m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x).changePathEnd(sf::Vector2u((unsigned int)(_endPos.x), (unsigned int)(_endPos.y)));
	m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x).setInitialisationTime(initTime);
	bool pathfindingComplete = false;

	PathfindingNode *lowFScore = nullptr;

	std::vector<sf::Time> whileLoopTimes = std::vector<sf::Time>();

	while (!pathfindingComplete)
	{
		lowFScore = findLowestFScoreOnOpenListAndRemove();
		m_ClosedList.push_back(lowFScore);
		lowFScore->m_ListOption = PathfindingNode::ListOption::CLOSED;

		for (unsigned int i = 0; i < 8; i += 1)
		{
			sf::Vector2i coords = returnCoordsAroundCentre(i, lowFScore->getGridCoords());

			if (coords.x < 0 || coords.y < 0 || coords.x >= (int)m_GridSize.x || coords.y >= (int)m_GridSize.y) continue;

			if (m_AllNodes.at(coords.y * m_GridSize.x + coords.x).getInitalisationTime() != initTime)
			{
				m_AllNodes.at(coords.y * m_GridSize.x + coords.x).setInitialisationTime(initTime);
				m_AllNodes.at(coords.y * m_GridSize.x + coords.x).changePathEnd(sf::Vector2u((unsigned int)(_endPos.x), (unsigned int)(_endPos.y)));
				m_AllNodes.at(coords.y * m_GridSize.x + coords.x).m_ListOption = PathfindingNode::ListOption::NONE;
			}

			if ((!m_ObstacleGrid.at(coords.y * m_GridSize.x + coords.x).s_CanPass.at(_type)) ||
				(isNodeOnList(&m_AllNodes.at(coords.y * m_GridSize.x + coords.x), PathfindingNode::ListOption::CLOSED)))
			{
				//~ If on the closed list or you cannot traverse it.
				continue;
			}

			if (isNodeOnList(&m_AllNodes.at(coords.y * m_GridSize.x + coords.x), PathfindingNode::ListOption::OPEN))
			{
				//~ On the open list
				if (m_AllNodes.at(coords.y * m_GridSize.x + coords.x).changeParent(lowFScore))
				{
					m_AllNodes.at(coords.y * m_GridSize.x + coords.x).setParent(lowFScore);
				}
			}
			else
			{
				m_AllNodes.at(coords.y * m_GridSize.x + coords.x).setParent(lowFScore);
				m_OpenList.push_back(&m_AllNodes.at(coords.y * m_GridSize.x + coords.x));
				m_AllNodes.at(coords.y * m_GridSize.x + coords.x).m_ListOption = PathfindingNode::ListOption::OPEN;
			}
			
		}

		if (m_OpenList.size() == 0 || isNodeOnList(endNode, PathfindingNode::ListOption::CLOSED))
		{
			pathfindingComplete = true;
			continue;
		}
		
	}

	PathfindingNode *routeNode = endNode;
	int count = 0;

	while (routeNode != nullptr)
	{
		_output->push_back(routeNode);

		routeNode->setFillColour(sf::Color(0, 255, 0, 125));

		routeNode = routeNode->getParent();
		count += 1;
	}

	if (count == 1)
	{
		_output->clear();
	}

	std::cout << "Time taken for a " << count << " long path: " << clock.getElapsedTime().asSeconds() << " seconds." << std::endl;
}

PathfindingNode *PathfindingGrid::findLowestFScoreOnOpenList(void)
{
	unsigned int lowF = m_OpenList.at(0)->getFValue();
	unsigned int lowIndex = 0u;

	for (unsigned int i = 0; i < m_OpenList.size(); i += 1)
	{
		if (lowF > m_OpenList.at(i)->getFValue())
		{
			lowF = m_OpenList.at(i)->getFValue();
			lowIndex = i;
		}
	}

	return m_OpenList.at(lowIndex);
}
PathfindingNode *PathfindingGrid::findLowestFScoreOnOpenListAndRemove(void)
{
	unsigned int lowF = m_OpenList.at(0)->getFValue();
	unsigned int lowIndex = 0u;

	for (unsigned int i = 0; i < m_OpenList.size(); i += 1)
	{
		if (lowF > m_OpenList.at(i)->getFValue())
		{
			lowF = m_OpenList.at(i)->getFValue();
			lowIndex = i;
		}
	}


	PathfindingNode *lowest = m_OpenList.at(lowIndex);

	m_OpenList.erase(m_OpenList.begin() + lowIndex);

	return lowest;
}

sf::Vector2i PathfindingGrid::returnCoordsAroundCentre(unsigned int _index, sf::Vector2u _startCoords/* = sf::Vector2u()*/)
{
	_startCoords /= TILESIZE_u;

	switch (_index)
	{
	case (0):
		return sf::Vector2i(_startCoords.x - 1, _startCoords.y - 1);
	case (1):
		return sf::Vector2i(_startCoords.x + 0, _startCoords.y - 1);
	case (2):
		return sf::Vector2i(_startCoords.x + 1, _startCoords.y - 1);
	case (3):
		return sf::Vector2i(_startCoords.x - 1, _startCoords.y + 0);
	case (4):
		return sf::Vector2i(_startCoords.x + 1, _startCoords.y + 0);
	case (5):
		return sf::Vector2i(_startCoords.x - 1, _startCoords.y + 1);
	case (6):
		return sf::Vector2i(_startCoords.x + 0, _startCoords.y + 1);
	case (7):
		return sf::Vector2i(_startCoords.x + 1, _startCoords.y + 1);
	default:
		return sf::Vector2i(_startCoords.x + 0, _startCoords.y + 0);
	};
}

bool PathfindingGrid::isNodeOnList(PathfindingNode *_node, PathfindingNode::ListOption _type)
{
	return _type == _node->m_ListOption;
}

