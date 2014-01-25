#ifndef INCLUDED_WORLDUNITFOOTPRINT_H
#define INCLUDED_WORLDUNITFOOTPRINT_H

#include "WorldObject.h"
#include "Tile.h"

class WorldUnitFootprint : public WorldObject
{
public:
	WorldUnitFootprint(sf::Vector2f _position);
	~WorldUnitFootprint(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void relocateOnPosition(void);

	void changeColour(sf::Color _colour);

private:
	sf::VertexArray											m_Vertex;

	Tile::Type												m_Type;
};

#endif //~ INCLUDED_WORLDUNITFOOTPRINT_H