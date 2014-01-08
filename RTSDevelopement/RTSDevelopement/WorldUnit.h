#ifndef INCLUDED_WORLDUNIT_H
#define INCLUDED_WORLDUNIT_H

#include "WorldObject.h"
#include "Tile.h"

class WorldUnit : public WorldObject
{
public:
	enum MovementDirection {NORTH,
							NORTH_EAST,
							EAST,
							SOUTH_EAST,
							SOUTH,
							SOUTH_WEST,
							WEST,
							NORTH_WEST,
							NONE,
							NUM_DIRECTIONS};

	WorldUnit(Tile::Type _type, sf::Vector2f _position, sf::Vector2f _size, int _maxHP, float _currentHP = 1.0f);
	~WorldUnit(void);

	virtual void update(sf::Time _delta) = 0;	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const = 0;

	void move(MovementDirection _dir);

	void setSpeed(float _speed);
	float getSpeed(void);

	Tile::Type getType(void);

protected:
	float								m_WorldUnitSpeed;

	Tile::Type							m_WorldUnitType;

	MovementDirection					m_WorldUnitDirectionToMove;
};

#endif //~ INCLUDED_WORLDUNIT_H