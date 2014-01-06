#ifndef INCLUDED_WORLDBUILDING_H
#define INCLUDED_WORLDBUILDING_H

#include "WorldObject.h"

class WorldBuilding : public WorldObject
{
public:
	enum BuildingType {MILITARY,
					   TEST,
					   NUM_TYPES};

	WorldBuilding(BuildingType _type, sf::Vector2f _position, sf::Vector2f _size);
	~WorldBuilding(void);

	virtual void update(sf::Time _delta) = 0;	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const = 0;

	virtual void modifyPathfinding(bool _onConstruction) = 0;

	BuildingType getBuildingType(void);

protected:
	BuildingType									m_BuildingType;
};

#endif //~ INCLUDED_WORLDBUILDING_H