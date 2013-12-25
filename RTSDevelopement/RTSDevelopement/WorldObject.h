#ifndef INCLUDED_WORLDOBJECT_H
#define INCLUDED_WORLDOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>

class CollisionCell;

class WorldObject : public sf::Drawable
{
public:
	enum ObjectType {TEST, NUMTYPES};

	WorldObject(ObjectType _type, sf::Vector2f _position, sf::Vector2f _size);
	~WorldObject(void);

	virtual void update(sf::Time _delta) = 0;	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const = 0;

	ObjectType getType(void);

	sf::Vector2f getPosition(void);
	sf::Vector2f getSize(void);

	void kill(void);
	bool isAlive(void);

	std::vector<CollisionCell *> *getTouchingCells(void);

protected:
	ObjectType									m_WorldObjectType;

	sf::Vector2f								m_WorldObjectPosition;
	sf::Vector2f								m_WorldObjectSize;

	bool										m_Alive;		

	std::vector<CollisionCell *>				m_TouchingCells;

};

#endif //~ INCLUDED_WORLDOBJECT_H