#include "Tile.h"

#include <fstream>

Tile::Tile(void) :
	m_TileUnitPassValues(unitType::NUM_TYPES, false)
{
}


Tile::~Tile(void)
{
}

void Tile::loadTilesToTileInfoVector(std::vector<Tile> *_tileInfo)
{
	std::fstream file("../../Resources/Maps/Map Data/Tile Information.RTSD");

	std::string line;

	std::vector<std::string>		tileInfoStrings;

	while (file.good())
	{
		std::getline(file, line);

		if (line.size() == 0) continue;
		if (line.at(0) == '~') continue;

		int location = line.find('-');

		if (location != std::string::npos)
		{
			if (line.substr(location, line.size()) == "-TILE_INFO_BEGIN")
			{
				continue;
			}
			else if (line.substr(location, line.size()) == "-TILE_INFO_END")
			{
				_tileInfo->push_back(Tile());
				_tileInfo->back().m_TileName = tileInfoStrings.at(0);
				_tileInfo->back().m_TileTextureCoordinates.x		= (float)(std::stoi(tileInfoStrings.at(1)));
				_tileInfo->back().m_TileTextureCoordinates.y		= (float)(std::stoi(tileInfoStrings.at(2)));
				_tileInfo->back().m_TileMinimapColour.r				= std::stoi(tileInfoStrings.at(3));
				_tileInfo->back().m_TileMinimapColour.g				= std::stoi(tileInfoStrings.at(4));
				_tileInfo->back().m_TileMinimapColour.b				= std::stoi(tileInfoStrings.at(5));
				_tileInfo->back().m_TileMinimapColour.a				= 255;
				_tileInfo->back().m_TileUnitPassValues.at(Tile::unitType::INFANTRY)			= tileInfoStrings.at(6)  == "true";
				_tileInfo->back().m_TileUnitPassValues.at(Tile::unitType::LIGHT_VEHICLE)	= tileInfoStrings.at(7)  == "true";
				_tileInfo->back().m_TileUnitPassValues.at(Tile::unitType::HEAVY_VEHICLE)	= tileInfoStrings.at(8)  == "true";
				_tileInfo->back().m_TileUnitPassValues.at(Tile::unitType::NAVAL)			= tileInfoStrings.at(9)  == "true";
				_tileInfo->back().m_TileUnitPassValues.at(Tile::unitType::AIR)				= tileInfoStrings.at(10) == "true";

				tileInfoStrings.clear();

				continue;
			}
		}

		tileInfoStrings.push_back(line);
	}
}

unsigned int Tile::getTileIndexFromName(std::string _tileName, const std::vector<Tile> &_tileInfo)
{
	unsigned int index = 0;

	for (unsigned int i = 0; i < _tileInfo.size(); i += 1)
	{
		if (_tileInfo.at(i).m_TileName == _tileName)
		{
			index = i;
			break;
		}
	}

	return index;
}