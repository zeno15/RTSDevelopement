#ifndef INCLUDED_WORLDUNIT_H
#define INCLUDED_WORLDUNIT_H

#include "WorldObject.h"
#include "Tile.h"
#include "Game.h"
#include "SteeringBehaviourUnitBase.h"


class WorldUnit : public WorldObject, public SteeringBehaviourUnitBase
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
	virtual void updatePosition(void) = 0;

	Tile::Type getType(void);

	virtual float getMass(void);
	virtual float getMaxSpeed(void);
	virtual float getSightDistance(void);
	virtual float getTooCloseDistance(void);
	virtual float getMaxForce(void);
	virtual float getWanderCircleRadius(void);
	virtual float getSlowingDistance(void);
	virtual float getAngleChange(void);
	virtual float getRadius(void);

	virtual float getRotation(void);
	virtual unsigned int getWaypointIndex(void);
	virtual sf::Vector2f getVelocity(void);
	virtual sf::Vector2f getPosition(void);

	virtual void setRotation(float _Rotation);
	virtual void setWaypointIndex(unsigned int _index);
	virtual void setVelocity(sf::Vector2f _vel);
	virtual void setPosition(sf::Vector2f _pos);

protected:
	float getAngleFromDirection(MovementDirection _dir);

	sf::Vector2f getUnitVectorFromDirection(MovementDirection _dir);

protected:
	float								m_WorldUnitMaxSpeed;
	float								m_WorldUnitRotation;
	float								m_WorldUnitMass;
	float								m_WorldUnitSightDistance;
	float								m_WorldUnitTooCloseDistance;
	float								m_WorldUnitMaxForce;
	float								m_WorldUnitWanderCircleRadius;
	float								m_WorldUnitSlowingDistance;
	float								m_WorldUnitRotationChange;

	sf::Vector2f						m_WorldUnitDestination;
	sf::Vector2f						m_WorldUnitVelocity;

	unsigned int						m_WorldUnitWaypointIndex;

	Tile::Type							m_WorldUnitType;

	MovementDirection					m_WorldUnitDirectionToMove;
};

#endif //~ INCLUDED_WORLDUNIT_H