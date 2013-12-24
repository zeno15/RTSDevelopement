#include "WorldDataTables.h"

WorldDataTables::WorldDataTables(void)
{
	m_TileColourComparableVector.push_back(sf::Color(0, 0, 0, 255));
	m_TileTextureStartingCoordinates.push_back(std::pair<float, float>(0.0f, 0.0f));
	m_TilePassableLandSeaAir.push_back(std::tuple<bool, bool, bool>(true, true, true));

	m_TileColourComparableVector.push_back(sf::Color(255, 0, 0, 255));
	m_TileTextureStartingCoordinates.push_back(std::pair<float, float>(32.0f, 0.0f));
	m_TilePassableLandSeaAir.push_back(std::tuple<bool, bool, bool>(true, true, true));

	m_TileColourComparableVector.push_back(sf::Color(0, 255, 0, 255));
	m_TileTextureStartingCoordinates.push_back(std::pair<float, float>(64.0f, 0.0f));
	m_TilePassableLandSeaAir.push_back(std::tuple<bool, bool, bool>(true, true, true));

	m_TileColourComparableVector.push_back(sf::Color(0, 0, 255, 255));
	m_TileTextureStartingCoordinates.push_back(std::pair<float, float>(96.0f, 0.0f));
	m_TilePassableLandSeaAir.push_back(std::tuple<bool, bool, bool>(true, true, true));
}

WorldDataTables::~WorldDataTables(void)
{
}

int WorldDataTables::findTileColourIndex(sf::Color _colour)
{
	for (unsigned int i = 0; i < m_TileColourComparableVector.size(); i += 1)
	{
		if (_colour == m_TileColourComparableVector.at(i))
		{
			return i;
		}
	}

	return -1;
}