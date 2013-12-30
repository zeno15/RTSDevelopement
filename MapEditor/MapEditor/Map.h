#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Tile.h"

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
	void create(sf::Vector2u _mapDimensions);	//~ Add in default tile type etc later

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void changeTile(unsigned int _xTile, unsigned int _yTile);

private:
	void loadTileInformation(void);
	void loadIndividualTileInfo(std::vector<std::string> *_info);

private:
	sf::Vector2u									m_MapDimensions; //~ In 32x32 pixel tiles

	sf::VertexArray									m_BackgroundTiles;

	std::vector<Tile>								m_TileInformation;
};

#endif //~ INCLUDED_MAP_H