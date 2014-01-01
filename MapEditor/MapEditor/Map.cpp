#include "Map.h"

#include "Game.h"

#define MAP_SCROLL_SPEED	500.0f

Map::Map(void) :
	m_BackgroundTiles(sf::Quads, 0)
{
	loadTileInformation();
	m_SideBarWidth = 200.0f;
	m_TopBarHeight = 20.0f;
}

Map::~Map(void)
{
}


void Map::load(std::string _filename)
{
}
void Map::create(sf::Vector2u _mapDimensions)
{
	if (_mapDimensions.x > 192) 
	{
		_mapDimensions.x = 192; 
		std::cout << "Map width limited to 192 Tiles." << std::endl;
	}
	if (_mapDimensions.y > 192) 
	{
		_mapDimensions.x = 192; 
		std::cout << "Map height limited to 192 Tiles." << std::endl;
	}

	m_MapDimensions = _mapDimensions;
	m_BackgroundTiles.resize(m_MapDimensions.x * m_MapDimensions.y * 4);

	m_Minimap.initialise(sf::FloatRect((float)(sGame.m_ScreenSize.x - m_SideBarWidth), 
									   0.0f, 
									   m_SideBarWidth, 
									   m_SideBarWidth),
									   m_MapDimensions);

	m_SideBar.initialise(sf::FloatRect((float)(sGame.m_ScreenSize.x - m_SideBarWidth),
									   m_SideBarWidth,
									   m_SideBarWidth,
									   (float)(sGame.m_ScreenSize.y - m_SideBarWidth)),
									   &m_TileInformation);

	m_TopBar.initialise(sf::FloatRect(0.0f,
									  0.0f,
									  (float)(sGame.m_ScreenSize.x - m_SideBarWidth),
									  m_TopBarHeight));

	for (unsigned int i = 0; i < m_MapDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapDimensions.x; j += 1)
		{
			changeTile(j, i, m_TileInformation.at(0));
		}
	}

	
}

void Map::update(sf::Time _delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sGame.m_View.move(- MAP_SCROLL_SPEED * _delta.asSeconds(), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sGame.m_View.move(+ MAP_SCROLL_SPEED * _delta.asSeconds(), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sGame.m_View.move(0.0f, - MAP_SCROLL_SPEED * _delta.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sGame.m_View.move(0.0f, + MAP_SCROLL_SPEED * _delta.asSeconds());
	}

	m_SideBar.update(_delta);
	m_TopBar.update(_delta);

	m_Minimap.update(_delta);

	ensureWithinBounds();

	sf::FloatRect mapBounds(0.0f, m_TopBarHeight, (float)(sGame.m_ScreenSize.x - m_SideBarWidth), (float)(sGame.m_ScreenSize.y - m_TopBarHeight));

	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_SideBar.getCurrentTool() == Sidebar::PAINT && mapBounds.contains(MOUSE_POSITION_WINDOW))
		{
			changeTile((unsigned int)(sf::Mouse::getPosition(*sGUIWINDOW).x + sGame.m_View.getCenter().x - sGame.m_View.getSize().x / 2.0f) / TILESIZE_u, 
					   (unsigned int)(sf::Mouse::getPosition(*sGUIWINDOW).y + sGame.m_View.getCenter().y - sGame.m_View.getSize().y / 2.0f) / TILESIZE_u,
					   m_SideBar.getCurrentTile());
		}
	}

	if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_SideBar.getCurrentTool() == Sidebar::FILL && mapBounds.contains(MOUSE_POSITION_WINDOW))
		{
			sf::Color colour = m_Minimap.getColour((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_u), (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_u));

			for (unsigned int i = 0; i < m_TileInformation.size(); i += 1)
			{
				if (colour == m_TileInformation.at(i).m_TileMinimapColour)
				{
					fill(m_TileInformation.at(i), m_SideBar.getCurrentTile(), sf::Vector2u((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_u), (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_u)));
					break;
				}
			}		
		}
	}

	if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_SideBar.getCurrentTool() == Sidebar::SELECT && mapBounds.contains(MOUSE_POSITION_WINDOW))
		{
			std::cout << getTileFromCoords((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_u), (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_u)).m_TileName << std::endl;
		}
	}
}
void Map::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(TextureManager::TextureID::TILESHEET);

	_target.draw(m_BackgroundTiles,		_states);

	_target.draw(m_Minimap,				_states);
	_target.draw(m_SideBar,				_states);
	_target.draw(m_TopBar,				_states);
}

void Map::changeTile(unsigned int _xTile, unsigned int _yTile, Tile _type)
{
	m_BackgroundTiles[4 * (_yTile * m_MapDimensions.x + _xTile) + 0] = sf::Vertex(sf::Vector2f((_xTile + 0) * TILESIZE_f, (_yTile + 0) * TILESIZE_f), 
																				  sf::Vector2f((float)(_type.m_TileTextureCoordinates.x),				(float)(_type.m_TileTextureCoordinates.y)));
	m_BackgroundTiles[4 * (_yTile * m_MapDimensions.x + _xTile) + 1] = sf::Vertex(sf::Vector2f((_xTile + 1) * TILESIZE_f, (_yTile + 0) * TILESIZE_f), 
																				  sf::Vector2f((float)(_type.m_TileTextureCoordinates.x) + TILESIZE_f,	(float)(_type.m_TileTextureCoordinates.y)));
	m_BackgroundTiles[4 * (_yTile * m_MapDimensions.x + _xTile) + 2] = sf::Vertex(sf::Vector2f((_xTile + 1) * TILESIZE_f, (_yTile + 1) * TILESIZE_f), 
																				  sf::Vector2f((float)(_type.m_TileTextureCoordinates.x) + TILESIZE_f,	(float)(_type.m_TileTextureCoordinates.y) + TILESIZE_f));
	m_BackgroundTiles[4 * (_yTile * m_MapDimensions.x + _xTile) + 3] = sf::Vertex(sf::Vector2f((_xTile + 0) * TILESIZE_f, (_yTile + 1) * TILESIZE_f), 
																				  sf::Vector2f((float)(_type.m_TileTextureCoordinates.x),				(float)(_type.m_TileTextureCoordinates.y) + TILESIZE_f));

	m_Minimap.updateColour(_xTile, _yTile, _type.m_TileMinimapColour);
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

		int location = line.find('-');

		if (location != std::string::npos)
		{
			if (line.substr(location, line.size()) == "-TILE_INFO_BEGIN")
			{
				continue;
			}
			else if (line.substr(location, line.size()) == "-TILE_INFO_END")
			{
				loadIndividualTileInfo(&tileInfoStrings);
				tileInfoStrings.clear();
				continue;
			}
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
	m_TileInformation.back().m_TileMinimapColour.r = std::stoi(_info->at(3));
	m_TileInformation.back().m_TileMinimapColour.g = std::stoi(_info->at(4));
	m_TileInformation.back().m_TileMinimapColour.b = std::stoi(_info->at(5));
	m_TileInformation.back().m_TileMinimapColour.a = 255;
}

void Map::ensureWithinBounds(void)
{
	if (sGame.m_View.getCenter().x - sGame.m_View.getSize().x / 2.0f < 0.0f)
	{
		sGame.m_View.setCenter(sGame.m_View.getSize().x / 2.0f, sGame.m_View.getCenter().y);
	}
	else if (sGame.m_View.getCenter().x + sGame.m_View.getSize().x / 2.0f - m_SideBarWidth > m_MapDimensions.x * TILESIZE_f)
	{
		sGame.m_View.setCenter(m_MapDimensions.x * TILESIZE_f - sGame.m_View.getSize().x / 2.0f + m_SideBarWidth, sGame.m_View.getCenter().y);
	}

	if (sGame.m_View.getCenter().y - sGame.m_View.getSize().y / 2.0f + m_TopBarHeight < 0.0f)
	{
		sGame.m_View.setCenter(sGame.m_View.getCenter().x, sGame.m_View.getSize().y / 2.0f - m_TopBarHeight);
	}
	else if (sGame.m_View.getCenter().y + sGame.m_View.getSize().y / 2.0f > m_MapDimensions.y * TILESIZE_f)
	{
		sGame.m_View.setCenter(sGame.m_View.getCenter().x, m_MapDimensions.y * TILESIZE_f - sGame.m_View.getSize().y / 2.0f);
	}
}

void Map::fill(Tile _replacingTile, Tile _newTile, sf::Vector2u _tileCoords)
{
	if (getTileFromCoords(_tileCoords.x, _tileCoords.y).m_TileName == _newTile.m_TileName) return;

	std::vector<sf::Vector2u> coordstoCheck = std::vector<sf::Vector2u>();
	coordstoCheck.push_back(_tileCoords);

	while (coordstoCheck.size() > 0)
	{
		
		if (getTileFromCoords(coordstoCheck.at(0).x, coordstoCheck.at(0).y).m_TileName == _replacingTile.m_TileName)
		{
			changeTile(coordstoCheck.at(0).x, coordstoCheck.at(0).y, _newTile);
		}
		else
		{
			coordstoCheck.erase(coordstoCheck.begin());
			continue;
		}

		if (coordstoCheck.at(0).x > 0)
		{
			if (getTileFromCoords(coordstoCheck.at(0).x - 1, coordstoCheck.at(0).y).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x - 1, coordstoCheck.at(0).y));
			}
		}
		if (coordstoCheck.at(0).y > 0)
		{
			if (getTileFromCoords(coordstoCheck.at(0).x, coordstoCheck.at(0).y - 1).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x, coordstoCheck.at(0).y - 1));
			}
		}
		if (coordstoCheck.at(0).x + 1 < m_MapDimensions.x)
		{
			if (getTileFromCoords(coordstoCheck.at(0).x + 1, coordstoCheck.at(0).y).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x + 1, coordstoCheck.at(0).y));
			}
		}
		if (coordstoCheck.at(0).y + 1 < m_MapDimensions.y)
		{
			if (getTileFromCoords(coordstoCheck.at(0).x, coordstoCheck.at(0).y + 1).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x, coordstoCheck.at(0).y + 1));
			}
		}
		coordstoCheck.erase(coordstoCheck.begin());
	}
	
	
}

Tile Map::getTileFromCoords(unsigned int _x, unsigned int _y)
{
	sf::Color colour = m_Minimap.getColour(_x, _y);

	for (unsigned int i = 0; i < m_TileInformation.size(); i += 1)
	{
		if (colour == m_TileInformation.at(i).m_TileMinimapColour)
		{
			return m_TileInformation.at(i);
		}
	}	
	return m_SideBar.getCurrentTile();
}