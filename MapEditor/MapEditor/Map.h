#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Tile.h"
#include "Minimap.h"

#define TILESIZE_f 32.0f
#define TILESIZE_u 32u
#define TILESIZE_i 32

class Map : public sf::Drawable
{
public:
	Map(void);
	~Map(void);

	enum TileType {DEFAULT_GRASS,
				   STONE,
				   WATER,
				   NUM_TILES};

	void load(std::string _filename);
	void create(sf::Vector2u _mapDimensions, TileType _defaultTileType);	//~ Add in default tile type etc later

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void changeTile(unsigned int _xTile, unsigned int _yTile, TileType _type);

private:
	void loadTileInformation(void);
	void loadIndividualTileInfo(std::vector<std::string> *_info);

	void ensureWithinBounds(void);

private:
	sf::Vector2u									m_MapDimensions; //~ In 32x32 pixel tiles

	sf::VertexArray									m_BackgroundTiles;

	std::vector<Tile>								m_TileInformation;

	float											m_SideBarWidth;
	float											m_TopBarHeight;

	Minimap											m_Minimap;
};

#endif //~ INCLUDED_MAP_H