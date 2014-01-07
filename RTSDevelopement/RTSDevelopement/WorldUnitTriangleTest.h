#ifndef INCLUDED_WORLDUNITTRIANGLETEST_H
#define INCLUDED_WORLDUNITTRIANGLETEST_H

#include "WorldUnit.h"

class WorldUnitTriangleTest : public WorldUnit
{
public:
	WorldUnitTriangleTest(sf::Vector2f _position); //~ Position relates to center of the tile
	~WorldUnitTriangleTest(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::VertexArray									m_Body;
};

#endif //~ INCLUDED_WORLDUNITTRIANGLETEST_H