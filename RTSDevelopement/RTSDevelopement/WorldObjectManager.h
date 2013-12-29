#ifndef INCLUDED_WORLDOBJECTMANAGER_H
#define INCLUDED_WORLDOBJECTMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "WorldObject.h"

class WorldObjectManager : public sf::Drawable
{
public:
	WorldObjectManager(void);
	~WorldObjectManager(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addWorldObject(WorldObject *_worldObject);

	WorldObject *getObject(unsigned int _index);

	unsigned int getWorldObjectCount(void);

private:
	std::vector<WorldObject *>					m_WorldObjects;

};

#endif //~ INCLUDED_WORLDOBJECTMANAGER_H