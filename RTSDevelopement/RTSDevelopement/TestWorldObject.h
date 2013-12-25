#ifndef INCLUDED_TESTWORLDOBJECT_H
#define INCLUDED_TESTWORLDOBJECT_H

#include "WorldObject.h"

class TestWorldObject : public WorldObject
{
public:
	TestWorldObject(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size);
	~TestWorldObject(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::RectangleShape							m_Rect;
};

#endif //~ INCLUDED_TESTWORLDOBJECT_H