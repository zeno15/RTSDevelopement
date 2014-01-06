#ifndef INCLUDED_WORLDBUILDINGMILITARY_H
#define INCLUDED_WORLDBUILDINGMILITARY_H

#include "WorldBuilding.h"

class WorldBuildingMilitary : public WorldBuilding
{
public:
	enum MilitaryBuildingType {TEST,
							   NUM_TYPES};

	WorldBuildingMilitary(WorldBuildingMilitary::MilitaryBuildingType _type, sf::Vector2f _position, sf::Vector2f _size);
	~WorldBuildingMilitary(void);	
	
	virtual void update(sf::Time _delta) = 0;	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const = 0;

	virtual void modifyPathfinding(bool _onConstruction) = 0;

	MilitaryBuildingType getMilitaryBuildingType(void);

protected:
	MilitaryBuildingType							m_MilitaryBuildingType;

};

#endif //~ INCLUDED_WORLDBUILDINGMILITARY_H