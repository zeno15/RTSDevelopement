#ifndef INCLUDED_TESTRANDOMWANDERER_H
#define INCLUDED_TESTRANDOMWANDERER_H

#include "WorldObject.h"

class TestRandomWanderer : public WorldObject
{
public:
	TestRandomWanderer(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size);
	~TestRandomWanderer(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void move(WorldObject::MovementDirection _dir, sf::Time _delta);

	sf::Vector2f getUnitVector(WorldObject::MovementDirection _dir);

private:
	sf::Time									m_CurrentMovementTime;

	WorldObject::MovementDirection				m_MovementDirection;

	sf::RectangleShape							m_Rectangle;

};

#endif //~ INCLUDED_TESTRANDOMWANDERER_H