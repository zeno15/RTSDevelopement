#ifndef INCLUDED_WORLDDATATABLES_H
#define INCLUDED_WORLDDATATABLES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>

class WorldDataTables
{
public: 
	WorldDataTables(void);
	~WorldDataTables(void);

	int findTileColourIndex(sf::Color _colour);

public:
	enum TerrainTravellers {LAND,
							SEA,
							AIR,
							NUMTYPES};

	std::vector<sf::Color>									m_TileColourComparableVector;
	std::vector<std::pair<float, float>>					m_TileTextureStartingCoordinates;
	std::vector<std::tuple<bool, bool, bool>>				m_TilePassableLandSeaAir;

};

#endif //~ INCLUDED_WORLDDATATABLES_H