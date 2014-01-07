#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Tile
{
public:
	enum Type  {INFANTRY,
				LIGHT_VEHICLE,
				HEAVY_VEHICLE,
				NAVAL,
				AIR,
				NUM_TYPES};

	Tile(void);
	~Tile(void);

	static void loadTilesToTileInfoVector(std::vector<Tile> *_tileInfo);

	static unsigned int getTileIndexFromName(std::string _tileName, const std::vector<Tile> &_tileInfo);

public:
	std::string							m_TileName;
	sf::Vector2f						m_TileTextureCoordinates;
	sf::Color							m_TileMinimapColour;
	std::vector<bool>					m_TileUnitPassValues;
};

#endif //~ INCLUDED_TILE_H