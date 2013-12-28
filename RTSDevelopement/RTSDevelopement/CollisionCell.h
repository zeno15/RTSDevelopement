#ifndef INCLUDED_COLLISIONCELL_H
#define INCLUDED_COLLISIONCELL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldObject.h"

class CollisionCell : public sf::Drawable
{
public:
	CollisionCell(sf::FloatRect _bounds);
	~CollisionCell(void);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	sf::FloatRect getBounds(void);

	void addWorldObject(WorldObject *_wObj);
	void removeWorldObject(WorldObject *_wObj);

	bool checkCollisionsWithin(std::vector<WorldObject *> *_outputCollisions, WorldObject *_wObj);

private:
	sf::FloatRect					m_Bounds;

	sf::RectangleShape				m_Rectangle;

	std::vector<WorldObject *>		m_TouchingWorldObjects;

};

#endif //~ INCLUDED_COLLISIONCELL_H