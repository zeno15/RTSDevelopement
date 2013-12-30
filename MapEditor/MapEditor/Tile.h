#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SFML/System/Vector2.hpp>
#include <string>

class Tile
{
public:
	Tile(void);
	~Tile(void);

public:
	std::string							m_TileName;
	sf::Vector2f						m_TileTextureCoordinates;
};

#endif //~ INCLUDED_TILE_H