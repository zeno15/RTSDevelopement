#include "Map.h"

#include "Game.h"

#include <algorithm>

#define MAP_SCROLL_SPEED	500.0f

Map::Map(void) :
	m_BackgroundTiles(sf::Quads, 0),
	m_OverlayQuads(sf::Quads, 0),
	m_OverlayToDraw(Tile::unitType::NUM_TYPES),
	m_Selecting(false)
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
	m_OverlayQuads.resize(m_MapDimensions.x * m_MapDimensions.y * 4);

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

			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 0] = sf::Vertex(sf::Vector2f((j + 0) * TILESIZE_f,
																						  (i + 0) * TILESIZE_f),
																			 sf::Color(255, 0, 0, 105));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 1] = sf::Vertex(sf::Vector2f((j + 1) * TILESIZE_f,
																						  (i + 0) * TILESIZE_f),
																			 sf::Color(255, 0, 0, 105));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 2] = sf::Vertex(sf::Vector2f((j + 1) * TILESIZE_f,
																						  (i + 1) * TILESIZE_f),
																			 sf::Color(255, 0, 0, 105));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 3] = sf::Vertex(sf::Vector2f((j + 0) * TILESIZE_f,
																						  (i + 1) * TILESIZE_f),
																			 sf::Color(255, 0, 0, 105));
		}
	}

	GUIFrame *topBarFrame = new GUIFrame();

	std::vector<std::vector<std::string>> fileMenuNames = std::vector<std::vector<std::string>>(4);

	fileMenuNames.at(0) = std::vector<std::string>(1);
	fileMenuNames.at(0).at(0) = "New Map";
	fileMenuNames.at(1) = std::vector<std::string>(1);
	fileMenuNames.at(1).at(0) = "Save Map";
	fileMenuNames.at(2) = std::vector<std::string>(1);
	fileMenuNames.at(2).at(0) = "Load Map";
	fileMenuNames.at(3) = std::vector<std::string>(1);
	fileMenuNames.at(3).at(0) = "Exit Map";

	GUIDropDownMenu *fileMenu = new GUIDropDownMenu(sf::Vector2f(50.0f, 10.0f),
													100.0f,
													"File",
													fileMenuNames);

	topBarFrame->addObject(fileMenu);

	sGUIMANAGER.addFrame(topBarFrame);
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

			if (m_SelectionBox.size() > 0)
			{
				for (unsigned int i = 0; i < m_SelectionBox.size(); i += 1)
				{
					if (m_SelectionBox.at(i).getGlobalBounds().contains(MOUSE_POSITION_VIEW))
					{
						for (unsigned int j = 0; j < m_TileInformation.size(); j += 1)
						{
							if (colour == m_TileInformation.at(j).m_TileMinimapColour)
							{
								fillRect(m_TileInformation.at(j), m_SideBar.getCurrentTile(), sf::Vector2u((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_u), (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_u)), m_SelectionBox.at(i));
								return;
							}
						}
					}
				}
			}

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
			m_Selecting = true;
			m_DisplaySelectionBox = true;
			m_InitialSelectedPosition = sf::Vector2f((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_f) * TILESIZE_f,
													 (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_f) * TILESIZE_f);
		}
	}
	if (m_Selecting && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//~ Update selection
		updateSelectionBox(false);
	}
	else if (m_Selecting && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//~ Finished selecting
		m_Selecting = false;
		updateSelectionBox(true);
	}

	if (m_DisplaySelectionBox)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_DisplaySelectionBox = false;
		}
	}
}
void Map::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(TextureManager::TextureID::TILESHEET);

	_target.draw(m_BackgroundTiles,		_states);

	if (m_OverlayToDraw != Tile::unitType::NUM_TYPES)
	{
		_target.draw(m_OverlayQuads);
	}
	if (m_DisplaySelectionBox)
	{
		for (unsigned int i = 0; i < m_SelectionBox.size(); i += 1)
		{
			_target.draw(m_SelectionBox.at(i));
		}
	}

	_target.draw(m_Minimap,				_states);
	_target.draw(m_SideBar,				_states);

	_target.draw(m_TopBar);

	

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
	m_TileInformation.back().m_TileUnitPassValues.at(Tile::unitType::INFANTRY)		= _info->at(6)  == "true";
	m_TileInformation.back().m_TileUnitPassValues.at(Tile::unitType::LIGHT_VEHICLE) = _info->at(7)  == "true";
	m_TileInformation.back().m_TileUnitPassValues.at(Tile::unitType::HEAVY_VEHICLE) = _info->at(8)  == "true";
	m_TileInformation.back().m_TileUnitPassValues.at(Tile::unitType::NAVAL)			= _info->at(8)  == "true";
	m_TileInformation.back().m_TileUnitPassValues.at(Tile::unitType::AIR)			= _info->at(10) == "true";
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
void Map::fillRect(Tile _replacingTile, Tile _newTile, sf::Vector2u _tileCoords, sf::RectangleShape _rect)
{
	if (getTileFromCoords(_tileCoords.x, _tileCoords.y).m_TileName == _newTile.m_TileName) return;

	std::vector<sf::Vector2u> coordstoCheck = std::vector<sf::Vector2u>();
	coordstoCheck.push_back(_tileCoords);

	sf::Rect<unsigned int> rectBounds = sf::Rect<unsigned int>();

	rectBounds.left   = (unsigned int)(_rect.getGlobalBounds().left  / TILESIZE_i);
	rectBounds.top    = (unsigned int)(_rect.getGlobalBounds().top   / TILESIZE_i);

	rectBounds.width  = (unsigned int)(_rect.getGlobalBounds().width  / TILESIZE_i);
	rectBounds.height = (unsigned int)(_rect.getGlobalBounds().height / TILESIZE_i);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		for (unsigned int i = rectBounds.top; i < rectBounds.top + rectBounds.height; i += 1)
		{
			for (unsigned int j = rectBounds.left; j < rectBounds.left + rectBounds.width; j += 1)
			{
				changeTile(j, i, _newTile);
			}
		}

		return;
	}

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

		if ((coordstoCheck.at(0).x > 0) && (coordstoCheck.at(0).x > rectBounds.left))
		{
			if (getTileFromCoords(coordstoCheck.at(0).x - 1, coordstoCheck.at(0).y).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x - 1, coordstoCheck.at(0).y));
			}
		}
		if ((coordstoCheck.at(0).y > 0) && (coordstoCheck.at(0).y > rectBounds.top))
		{
			if (getTileFromCoords(coordstoCheck.at(0).x, coordstoCheck.at(0).y - 1).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x, coordstoCheck.at(0).y - 1));
			}
		}
		if ((coordstoCheck.at(0).x + 1 < m_MapDimensions.x) && (coordstoCheck.at(0).x + 1 < rectBounds.left + rectBounds.width))
		{
			if (getTileFromCoords(coordstoCheck.at(0).x + 1, coordstoCheck.at(0).y).m_TileName == _replacingTile.m_TileName)
			{
				coordstoCheck.push_back(sf::Vector2u(coordstoCheck.at(0).x + 1, coordstoCheck.at(0).y));
			}
		}
		if ((coordstoCheck.at(0).y + 1 < m_MapDimensions.y) && (coordstoCheck.at(0).y + 1 < rectBounds.top + rectBounds.height))
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

void Map::createSavedMapFrame(void)
{
}
void Map::saveMap(std::string _filename)
{
}

void Map::updateSelectionBox(bool _finalise)
{
	static bool createNew = true;


	m_InitialSelectedPosition;

	sf::Vector2f newPosition = sf::Vector2f((unsigned int)(MOUSE_POSITION_VIEW.x / TILESIZE_f) * TILESIZE_f,
										    (unsigned int)(MOUSE_POSITION_VIEW.y / TILESIZE_f) * TILESIZE_f);

	sf::Vector2f size(fabsf(m_InitialSelectedPosition.x - newPosition.x) - 2.0f + TILESIZE_f,
					  fabsf(m_InitialSelectedPosition.y - newPosition.y) - 2.0f + TILESIZE_f);

	sf::Vector2f pos(std::min(m_InitialSelectedPosition.x, newPosition.x) + 1.0f,
					 std::min(m_InitialSelectedPosition.y, newPosition.y) + 1.0f);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && createNew)
	{
		m_SelectionBox.clear();
	}

	if (createNew)
	{
		m_SelectionBox.push_back(sf::RectangleShape());
	}
	
	m_SelectionBox.back().setPosition(pos);
	m_SelectionBox.back().setSize(size);

	m_SelectionBox.back().setFillColor(sf::Color::Transparent);
	m_SelectionBox.back().setOutlineThickness(1.0f);
	m_SelectionBox.back().setOutlineColor(sf::Color::White);

	createNew = _finalise;
}