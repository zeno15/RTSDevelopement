#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Tile
{
public:
	enum unitType {INFANTRY,
				   LIGHT_VEHICLE,
				   HEAVY_VEHICLE,
				   NAVAL,
				   AIR,
				   NUM_TYPES};

	Tile(void);
	~Tile(void);

public:
	std::string							m_TileName;
	sf::Vector2f						m_TileTextureCoordinates;
	sf::Color							m_TileMinimapColour;
	std::vector<bool>					m_TileUnitPassValues;
};

#endif //~ INCLUDED_TILE_H