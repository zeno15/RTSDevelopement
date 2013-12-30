#include "Map.h"

Map::Map(void) :
	m_BackgroundTiles(sf::Quads, 0)
{
	loadTileInformation();
}

Map::~Map(void)
{
}


void Map::load(std::string _filename)
{
}
void Map::create(sf::Vector2u _mapDimensions)
{
	m_MapDimensions = _mapDimensions;
	m_BackgroundTiles.resize(m_MapDimensions.x * m_MapDimensions.y * 4);
}

void Map::update(sf::Time _delta)
{
}
void Map::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_BackgroundTiles,		_states);
}

void Map::loadTileInformation(void)
{
	std::fstream file("../../Resources/Maps/Map Data/Tile Information.RTSD");

	std::string line;

	std::vector<std::string>		tileInfoStrings;

	while (file.good())
	{
		std::getline(file, line);

		if (line.size() == 0) continue;
		if (line.at(0) == '~') continue;

		if (line.substr(1, line.size()) == "-TILE_INFO_BEGIN")
		{
			continue;
		}
		else if (line.substr(1, line.size()) == "-TILE_INFO_END")
		{
			loadIndividualTileInfo(&tileInfoStrings);
			tileInfoStrings.clear();
			continue;
		}

		tileInfoStrings.push_back(line);
	}
}
void Map::loadIndividualTileInfo(std::vector<std::string> *_info)
{
	m_TileInformation.push_back(Tile());
	m_TileInformation.back().m_TileName = _info->at(0);
	m_TileInformation.back().m_TileTextureCoordinates.x = (float)(std::stoi(_info->at(1)));
	m_TileInformation.back().m_TileTextureCoordinates.y = (float)(std::stoi(_info->at(2)));
}