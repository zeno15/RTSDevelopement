#ifndef INCLUDED_WORLDBUILDINGFOOTPRINT_H
#define INCLUDED_WORLDBUILDINGFOOTPRINT_H

#include "WorldObject.h"

#include "Tile.h"

//~ Need to add what terrain the building has to go on etc (water/land)

class WorldBuildingFootprint : public WorldObject
{
public:
	WorldBuildingFootprint(sf::Vector2f _size, Tile::Type _desiredTerrain);
	~WorldBuildingFootprint(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void relocateOnPosition(void);

	void changeColour(sf::Color _colour);

private:
	sf::VertexArray								m_Footprint;

	sf::Vector2u								m_FootprintSizeTiles;

	Tile::Type									m_Type;

};

#endif //~ INCLUDED_WORLDBUILDINGFOOTPRINT_H