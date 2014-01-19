#include "PathfindingGrid.h"

#include <algorithm>

#include "Game.h"
#include "HelperFunctions.h"

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

	for (unsigned int i = 0; i < 28; i += 1)
	{
		for (unsigned int j = 0; j < 45; j += 1)
		{
			if (m_OverlayType != Tile::Type::NUM_TYPES &&
				!m_ObstacleGrid.at(i * m_GridSize.x + j).s_CanPass.at(m_OverlayType))
			{
				temp.setPosition((float)(j * TILESIZE_f), (float)(i * TILESIZE_f));
				_target.draw(temp,		_states);
			}

			_target.draw(m_AllNodes.at(i * m_GridSize.x + j),			_states);
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

	for (unsigned int i = 0; i < m_AllNodes.size(); i += 1)
	{
		m_AllNodes.at(i).reset();
		m_AllNodes.at(i).m_PathfindingGridCoordinates.x = i % m_GridSize.x;
		m_AllNodes.at(i).m_PathfindingGridCoordinates.y = i / m_GridSize.y;
	}
	
	sf::Vector2u startNode = sf::Vector2u((unsigned int)(_startPos.x) / TILESIZE_u, (unsigned int)(_startPos.y) / TILESIZE_u);
	sf::Vector2u endNode   = sf::Vector2u((unsigned int)(_endPos.x)   / TILESIZE_u, (unsigned int)(_endPos.y)   / TILESIZE_u);

	PathfindingNode *endNodePointer = &m_AllNodes.at(endNode.y * m_GridSize.x + endNode.x);

	m_OpenList.push_back(&m_AllNodes.at(startNode.y * m_GridSize.x + startNode.x));
	m_OpenList.front()->m_ListOption = PathfindingNode::ListOption::OPEN;

	while (true)
	{
		if (m_OpenList.size() == 0)
		{
			break;
		}

		PathfindingNode *currentNode = findLowestFScoreOnOpenListAndRemove();
		//std::cout << "Open list remove" << std::endl;
		if (currentNode == endNodePointer)
		{
			_output->clear();

			//_output->push_back(currentNode);
			
			while (true)
			{
				_output->push_back(currentNode);
				currentNode = currentNode->m_ParentNode;
				if (currentNode == nullptr)
				{
					std::reverse(_output->begin(), _output->end());
					break;
				}
			}
			break;
		}

		m_ClosedList.push_back(currentNode);
		currentNode->m_ListOption = PathfindingNode::ListOption::CLOSED;

		for (unsigned int i = 0; i < 8; i += 1)
		{
			sf::Vector2i coords = returnCoordsAroundCentre(i, currentNode->m_PathfindingGridCoordinates);

			if (coords.x < 0 || coords.y < 0 || coords.x >= (int)(m_GridSize.x) || coords.y >= (int)(m_GridSize.y)) continue;

			PathfindingNode *n = &m_AllNodes.at(coords.y * m_GridSize.x + coords.x);

			if (n == nullptr || !isTilePassable((unsigned int)(coords.x), (unsigned int)(coords.y), _type))
			{
				continue;
			}

			if (n->m_ListOption == PathfindingNode::ListOption::NONE)
			{
				m_OpenList.push_back(n);
				n->m_ListOption = PathfindingNode::ListOption::OPEN;

				if (i == 0 || i == 2 || i == 5 || i == 7)
				{
					n->m_GValue = 14;
				}
				else
				{
					n->m_GValue = 10;
				}

				n->m_ParentNode = currentNode;
				n->m_GValue += currentNode->m_GValue;

				n->m_HValue = manhatten(sf::Vector2u((unsigned int)(coords.x), (unsigned int)(coords.y)), endNode);

				n->m_FValue = n->m_GValue + n->m_HValue;
			}
			else
			{
				unsigned int test = 0;
				if (i == 0 || i == 2 || i == 5 || i == 7)
				{
					test = 14;
				}
				else
				{
					test = 10;
				}

				test += currentNode->m_GValue;
				if (test < n->m_GValue)
				{
					n->m_GValue = test;
					n->m_FValue = n->m_GValue + n->m_HValue;
					n->m_ParentNode = currentNode;
				}
			}
		}

	}
	m_OpenList.clear();
	m_ClosedList.clear();

	std::cout << "Time: " << clock.getElapsedTime().asSeconds() << " seconds, path length: " << _output->size() << std::endl;
}

bool PathfindingGrid::isTilePassable(unsigned int _x, unsigned int _y, Tile::Type _type)
{
	return m_ObstacleGrid.at(_y * m_GridSize.x + _x).s_CanPass.at(_type);
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
	//_startCoords /= TILESIZE_u;

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

unsigned int PathfindingGrid::manhatten(sf::Vector2u _current, sf::Vector2u _end)
{
	return 10 * (unsigned int)(fabs((float)(_current.x) - (float)(_end.x)) + fabs((float)(_current.y) - (float)(_end.y)));
}