#include "CollisionGrid.h"

#include <cmath>

#include "Game.h"

/*

	Each world object has a vector of collision cells that it is touching

	Each collision cell has a vector of world objects that are touching it

	When you move a world object you check which collison cells it is now touching,
	then compare that vector to the one that is stored for the world object, if
	the vectors differ, then you update both the world objects vector of 
	collision cells, and the collision cells that were and now are being touched

*/

CollisionGrid::CollisionGrid(void) :
	m_CellSize(64.0f, 64.0f)
{
}

CollisionGrid::~CollisionGrid(void)
{
	for (unsigned int i = 0; i < m_Cells.size(); i += 1)
	{
		mDebugDelete(m_Cells.at(i));
		delete m_Cells.at(i);
	}
}


void CollisionGrid::setCollisionArea(sf::Vector2u _collisionArea)
{
	m_CollisionArea = sf::Vector2u((unsigned int)(_collisionArea.x * TILESIZE_f), (unsigned int)(_collisionArea.y * TILESIZE_f));

	for (unsigned int i = 0; i < m_CollisionArea.x; i += (unsigned int)(m_CellSize.x))
	{
		for (unsigned int j = 0; j < m_CollisionArea.y; j += (unsigned int)(m_CellSize.y))
		{
			CollisionCell *cell = new CollisionCell(sf::FloatRect((float)(j), (float)(i), m_CellSize.x, m_CellSize.y));
			mDebugNew(cell);
			m_Cells.push_back(cell);
		}
	}
}

void CollisionGrid::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	for (CollisionCell *cell : m_Cells)
	{
		_target.draw(*cell,				_states);
	}
}

void CollisionGrid::updateTouchingCells(WorldObject *_wObj)
{
	sf::FloatRect wObjBounds = sf::FloatRect(_wObj->getPosition() - _wObj->getSize() / 2.0f, _wObj->getSize());

	std::vector<CollisionCell *> *wObjCurrentCells = _wObj->getTouchingCells();

	for (unsigned int i = 0; i < wObjCurrentCells->size(); i += 1)
	{
		wObjCurrentCells->at(i)->removeWorldObject(_wObj);
	}

	wObjCurrentCells->clear();

	for (float i = wObjBounds.top; i <= wObjBounds.top + wObjBounds.height; i += wObjBounds.height)
	{
		for (float j = wObjBounds.left; j <= wObjBounds.left + wObjBounds.width; j += wObjBounds.width)
		{
			wObjCurrentCells->push_back(m_Cells.at((unsigned int)(i / m_CellSize.y) * (unsigned int)(m_CollisionArea.x / m_CellSize.x) + (unsigned int)(j / m_CellSize.x)));
			wObjCurrentCells->back()->addWorldObject(_wObj);
		}
	}
}

sf::Vector2u CollisionGrid::pixelsToCells(sf::Vector2f _pixelCoordinates)
{
	return sf::Vector2u((unsigned int)(_pixelCoordinates.x / m_CellSize.x), (unsigned int)(_pixelCoordinates.y / m_CellSize.y));
}

bool CollisionGrid::checkCollisions(std::vector<WorldObject *> *_outputCollisions, WorldObject *_wObj)
{
	std::vector<CollisionCell *> *collisionCells = _wObj->getTouchingCells();

	bool collisions = false;

	for (unsigned int i = 0; i < collisionCells->size(); i += 1)
	{
		if (collisionCells->at(i)->checkCollisionsWithin(_outputCollisions, _wObj))
		{
			collisions = true;
		}
	}
	return collisions;
}