#include "PathfindingGrid.h"

#include "Game.h"

PathfindingGrid::PathfindingGrid(void)
{
	timer = sf::Time::Zero;
	timer2 = sf::Time::Zero;
	timer3 = sf::Time::Zero;
}

PathfindingGrid::~PathfindingGrid(void)
{
}


void PathfindingGrid::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	sf::RectangleShape temp = sf::RectangleShape(sf::Vector2f(TILESIZE_f, TILESIZE_f));
	temp.setFillColor(sf::Color(255, 0, 0, 125));

	for (unsigned int i = 0; i < m_GridSize.y; i += 1)
	{
		for (unsigned int j = 0; j < m_GridSize.x; j += 1)
		{
			if (m_ObstacleGrid.at(i * m_GridSize.x + j).s_CanPass == cellStates::INVALID)
			{
				temp.setPosition((float)(j * TILESIZE_f), (float)(i * TILESIZE_f));
				_target.draw(temp,		_states);
			}
		}
	}
}

void PathfindingGrid::initialise(sf::Vector2u _size)
{
	m_GridSize = _size;
	
	m_ObstacleGrid.resize(_size.x * _size.y);

	for (unsigned int i = 0; i < m_GridSize.y; i += 1)
	{
		for (unsigned int j = 0; j < m_GridSize.x; j += 1)
		{
			m_ObstacleGrid.at(i * m_GridSize.x + j).s_CanPass = PathfindingGrid::VALID;
			m_ObstacleGrid.at(i * m_GridSize.x + j).s_Count   = 0;

			m_AllNodes.push_back(PathfindingNode(sf::Vector2u(j * TILESIZE_u, i * TILESIZE_u), sf::Vector2u()));
		}
	}

	addObstacle(5, 5);
	addObstacle(6, 5);
	addObstacle(7, 5);
	addObstacle(5, 6);
	addObstacle(6, 6);
	addObstacle(7, 6);
	addObstacle(5, 7);
	addObstacle(6, 7);
	addObstacle(7, 7);

	for (unsigned int i = 8; i < m_GridSize.x; i += 1)
	{
		addObstacle(i, 7);
	}

	for (unsigned int i = 0; i < m_GridSize.x - 8; i += 1)
	{
		addObstacle(i, 10);
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
	sf::Clock clock;

	for (unsigned int i = 0; i < m_AllNodes.size(); i += 1)
	{
		m_AllNodes.at(i).changePathEnd(sf::Vector2u((unsigned int)(_endPos.x), (unsigned int)(_endPos.y)));
	}

	//~ Input is in pixels, convert to tiles
	sf::Vector2u startNodeCoords  = sf::Vector2u((unsigned int)(_startPos.x / TILESIZE_f), (unsigned int)(_startPos.y / TILESIZE_f));
	sf::Vector2u finishNodeCoords = sf::Vector2u((unsigned int)(_endPos.x / TILESIZE_f), (unsigned int)(_endPos.y / TILESIZE_f));

	PathfindingNode *endNode = &m_AllNodes.at(finishNodeCoords.y * m_GridSize.x + finishNodeCoords.x);

	m_OpenList.push_back(&m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x));
	m_AllNodes.at(startNodeCoords.y * m_GridSize.x + startNodeCoords.x).m_ListOption = PathfindingNode::ListOption::OPEN;
	bool pathfindingComplete = false;

	PathfindingNode *lowFScore = nullptr;
	
	while (!pathfindingComplete)
	{
		lowFScore = findLowestFScoreOnOpenListAndRemove();
		m_ClosedList.push_back(lowFScore);
		lowFScore->m_ListOption = PathfindingNode::ListOption::CLOSED;

		for (unsigned int i = 0; i < 8; i += 1)
		{
			sf::Vector2i coords = returnCoordsAroundCentre(i, lowFScore->getGridCoords());

			if (coords.x < 0 || coords.y < 0 || coords.x >= (int)m_GridSize.x || coords.y >= (int)m_GridSize.y) continue;

			if ((m_ObstacleGrid.at(coords.y * m_GridSize.x + coords.x).s_CanPass == cellStates::INVALID) ||
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
				//~ Not on the open list
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
		//_output->push_back(routeNode);

		routeNode->setFillColour(sf::Color(0, 255, 0, 125));

		routeNode = routeNode->getParent();
		count += 1;
	}

	
	float seconds = clock.getElapsedTime().asSeconds();

	std::cout << "Time taken for a " << count << " long path: " << seconds << " seconds, " << seconds / (float)count << "seconds/cell" << std::endl;

	std::cout << "Time in finding lowest f score: " << timer.asSeconds() << " seconds, " << 100.0f * timer.asSeconds() / seconds << "% of total time." << std::endl;
	std::cout << "Time in finding nodes in lists: " << timer2.asSeconds() << " seconds, " << 100.0f * timer2.asSeconds() / seconds << "% of total time." << std::endl;

	for (unsigned int i = 0; i < m_AllNodes.size(); i += 1)
	{
		_output->push_back(&m_AllNodes.at(i));
	}

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
	mclock.restart();

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
	timer += mclock.getElapsedTime();
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
		return sf::Vector2i(_startCoords.x + 1, - 1);
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

