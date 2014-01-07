#ifndef INCLUDED_COLLISIONGRID_H
#define INCLUDED_COLLISIONGRID_H

#include <SFML/Graphics.hpp>

#include "CollisionCell.h"

class CollisionGrid : public sf::Drawable //~ Need to change many rectangles to 1 vertex array?
{
public:
	CollisionGrid(void);
	~CollisionGrid(void);

	void setCollisionArea(sf::Vector2u _collisionArea);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void updateTouchingCells(WorldObject *_wObj);

	bool checkCollisions(std::vector<WorldObject *> *_outputCollisions, WorldObject *_wObj);
	bool checkCollisions(std::vector<WorldObject *> *_outputCollisions, sf::Vector2f _position);
	bool checkCollisions(std::vector<WorldObject *> *_outputCollisions, sf::FloatRect _bounds);

private:
	sf::Vector2u pixelsToCells(sf::Vector2f _pixelCoordinates);

private:
	std::vector<CollisionCell *>					m_Cells;

	sf::Vector2f									m_CellSize;
	sf::Vector2u									m_CollisionArea;
};

#endif //~ INCLUDED_COLLISIONGRID_H