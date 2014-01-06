#ifndef INCLUDED_WORLDBUILDINGFOOTPRINT_H
#define INCLUDED_WORLDBUILDINGFOOTPRINT_H

#include "WorldObject.h"

class WorldBuildingFootprint : public WorldObject
{
public:
	WorldBuildingFootprint(sf::Vector2f _position, sf::Vector2f _size);
	~WorldBuildingFootprint(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::VertexArray								m_Footprint;

};

#endif //~ INCLUDED_WORLDBUILDINGFOOTPRINT_H