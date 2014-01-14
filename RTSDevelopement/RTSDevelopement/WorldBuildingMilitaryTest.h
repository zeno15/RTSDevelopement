#ifndef INCLUDED_WORLDBUILDINGMILITARYTEST_H
#define INCLUDED_WORLDBUILDINGMILITARYTEST_H

#include "WorldBuildingMilitary.h"

class WorldBuildingMilitaryTest : public WorldBuildingMilitary
{
public:
	WorldBuildingMilitaryTest(sf::Vector2f _position);
	~WorldBuildingMilitaryTest(void);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::VertexArray								m_Vertices;

};

#endif //~ INCLUDED_WORLDBUILDINGMILITARYTEST_H