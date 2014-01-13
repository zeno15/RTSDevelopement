#include "Map.h"

#include "Game.h"
#include "NewMapInterface.h"
#include "SaveMapInterface.h"
#include "LoadMapInterface.h"

#include <algorithm>

#define MAP_SCROLL_SPEED	500.0f

Map::Map(void) :
	m_BackgroundTiles(sf::Quads, 0),
	m_OverlayQuads(sf::Quads, 0),
	m_OverlayToDraw(Tile::Type::NUM_TYPES),
	m_Selecting(false),
	m_MenubarIsActive(false),
	DEBUG_initial(true)
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
	std::ifstream input(_filename);

	std::string line;
	unsigned int found;

	if (!input.good())
	{
		std::cout << "Failed to load map: " << _filename << ". Do something else" << std::endl;
		return;
	}

	std::getline(input, line);
	found = line.find_first_of("0123456789");
	m_MapDimensions.y = (unsigned int)(std::stoi(line.substr(found, line.size())));

	std::getline(input, line);
	found = line.find_first_of("0123456789");
	m_MapDimensions.x = (unsigned int)(std::stoi(line.substr(found, line.size())));

	std::vector<unsigned int> mapTileIndecies = std::vector<unsigned int>();

	for (unsigned int i = 0; i < m_MapDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapDimensions.x; j += 1)
		{
			unsigned int index = 0;

			std::getline(input, line);

			for (unsigned int k = 0; k < m_TileInformation.size(); k += 1)
			{
				if (line == m_TileInformation.at(k).m_TileName)
				{
					index = k;
					break;
				}
			}

			mapTileIndecies.push_back(index);
		}
	}

	create(m_MapDimensions, mapTileIndecies);
}
void Map::save(std::string _filename)
{
	std::ofstream output( _filename);

	output << "Map Height: " << m_MapDimensions.y << std::endl;
	output << "Map Width: "  << m_MapDimensions.x << std::endl;

	for (unsigned int i = 0; i < m_MapDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapDimensions.x; j += 1)
		{
			output << getTileFromCoords(j, i).m_TileName << std::endl;
		}
	}

	output.close();
}
void Map::create(sf::Vector2u _mapDimensions, std::vector<unsigned int> _tileIndecies/* = std::vector<unsigned int>()*/)
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

	if (_tileIndecies == std::vector<unsigned int>())
	{
		_tileIndecies.resize(_mapDimensions.x * _mapDimensions.y, 0);
	}

	m_MapDimensions = _mapDimensions;
	m_BackgroundTiles.resize(m_MapDimensions.x * m_MapDimensions.y * 4);
	m_OverlayQuads.resize(m_MapDimensions.x * m_MapDimensions.y * 4);
	
	m_Minimap.initialise(sf::FloatRect((float)(sGame.m_ScreenSize.x - m_SideBarWidth), 
										0.0f, 
										m_SideBarWidth, 
										m_SideBarWidth),
										m_MapDimensions);
	if (DEBUG_initial)
	{

		m_SideBar.initialise(sf::FloatRect((float)(sGame.m_ScreenSize.x - m_SideBarWidth),
										   m_SideBarWidth,
										   m_SideBarWidth,
										   (float)(sGame.m_ScreenSize.y - m_SideBarWidth)),
										   &m_TileInformation);

		m_TopBar.initialise(sf::FloatRect(0.0f,
										  0.0f,
										  (float)(sGame.m_ScreenSize.x - m_SideBarWidth),
										  m_TopBarHeight));
	}

	for (unsigned int i = 0; i < m_MapDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapDimensions.x; j += 1)
		{
			changeTile(j, i, m_TileInformation.at(_tileIndecies.at(i * m_MapDimensions.x + j)));

			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 0] = sf::Vertex(sf::Vector2f((j + 0) * TILESIZE_f,
																						  (i + 0) * TILESIZE_f));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 1] = sf::Vertex(sf::Vector2f((j + 1) * TILESIZE_f,
																						  (i + 0) * TILESIZE_f));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 2] = sf::Vertex(sf::Vector2f((j + 1) * TILESIZE_f,
																						  (i + 1) * TILESIZE_f));
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 3] = sf::Vertex(sf::Vector2f((j + 0) * TILESIZE_f,
																						  (i + 1) * TILESIZE_f));
		}
	}

	if (DEBUG_initial)
	{
		GUIFrame *topBarFrame = new GUIFrame();

		std::vector<std::vector<std::string>> fileMenuNames = std::vector<std::vector<std::string>>(4);

		fileMenuNames.at(0) = std::vector<std::string>(1);
		fileMenuNames.at(0).at(0) = "New Map";
		fileMenuNames.at(1) = std::vector<std::string>(1);
		fileMenuNames.at(1).at(0) = "Save Map";
		fileMenuNames.at(2) = std::vector<std::string>(1);
		fileMenuNames.at(2).at(0) = "Load Map";
		fileMenuNames.at(3) = std::vector<std::string>(1);
		fileMenuNames.at(3).at(0) = "Exit Editor";

		GUIDropDownMenu *fileMenu = new GUIDropDownMenu(sf::Vector2f(40.0f, 10.0f),
														80.0f,
														"File",
														fileMenuNames);
		fileMenu->registerReceiver(this);

		std::vector<std::vector<std::string>> toolMenuNames = std::vector<std::vector<std::string>>(1);

		toolMenuNames.at(0) = std::vector<std::string>(Tile::Type::NUM_TYPES + 2);
		toolMenuNames.at(0).at(0) = "Overlay Types";
		toolMenuNames.at(0).at(1) = "Infantry";
		toolMenuNames.at(0).at(2) = "Light Vehicle";
		toolMenuNames.at(0).at(3) = "Heavy Vehicle";
		toolMenuNames.at(0).at(4) = "Naval";
		toolMenuNames.at(0).at(5) = "Air";
		toolMenuNames.at(0).at(6) = "Normal";

		GUIDropDownMenu *toolMenu = new GUIDropDownMenu(sf::Vector2f(136.0f, 10.0f),
														110.0f,
														"Tools",
														toolMenuNames);
		toolMenu->registerReceiver(this);

		topBarFrame->addObject(fileMenu);
		topBarFrame->addObject(toolMenu);

		sGUIMANAGER.addFrame(topBarFrame);
		DEBUG_initial = false;
	}
}

void Map::update(sf::Time _delta)
{
	while (m_Messages.size() > 0)
	{
		if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_ACTIVE)
		{
			m_MenubarIsActive = true;
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_UNACTIVE)
		{
			m_MenubarIsActive = false;
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::DROPDOWN_MENU_SELECT)
		{
			handleDropMenuChoices(m_Messages.front().s_StringData);
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::NEW_MAP_BOUNDS)
		{
			unsigned int found = m_Messages.front().s_StringData.find("x");
			
			unsigned int width  = std::stoi(m_Messages.front().s_StringData.substr(0, found));
			unsigned int height = std::stoi(m_Messages.front().s_StringData.substr(found + 1, m_Messages.front().s_StringData.size()));

			std::vector<unsigned int> terrain = std::vector<unsigned int>(width * height, (unsigned int)(m_Messages.front().s_FloatData));

			create(sf::Vector2u(width, height), terrain);
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::SAVE_MAP_DATA)
		{
			save(m_Messages.front().s_StringData);
		}
		else if (m_Messages.front().s_MessageType == MessageData::MessageType::LOAD_MAP_DATA)
		{
			load(m_Messages.front().s_StringData);
		}

		m_Messages.erase(m_Messages.begin());
	}



	if (m_MenubarIsActive)
	{
		return;
	}

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
	_states.texture = sTexture.getTexture(0);

	_target.draw(m_BackgroundTiles,		_states);

	if (m_OverlayToDraw != Tile::Type::NUM_TYPES)
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
	Tile::loadTilesToTileInfoVector(&m_TileInformation);
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

void Map::activateOverlay(Tile::Type _type)
{
	m_OverlayToDraw = _type;

	if (m_OverlayToDraw == Tile::Type::NUM_TYPES) return;

	for (unsigned int i = 0; i < m_MapDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapDimensions.x; j += 1)
		{
			sf::Color overlayColour;

			if (getTileFromCoords(j, i).m_TileUnitPassValues.at(m_OverlayToDraw))
			{
				overlayColour = sf::Color(0, 255, 0, 175);
			}
			else
			{
				overlayColour = sf::Color(255, 0, 0, 175);
			}

			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 0].color = overlayColour;
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 1].color = overlayColour;
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 2].color = overlayColour;
			m_OverlayQuads[4 * (i * m_MapDimensions.x + j) + 3].color = overlayColour;
		}
	}
}

void Map::handleDropMenuChoices(std::string _choice)
{
	std::vector<std::string> choicesSplit = std::vector<std::string>();

	unsigned int found = _choice.find("-");

	while (found != std::string::npos)
	{
		choicesSplit.push_back(_choice.substr(0, found));

		_choice = _choice.substr(found + 1, _choice.size());
		
		found = _choice.find("-");
	}

	choicesSplit.push_back(_choice);



	if (choicesSplit.at(0) == "File")
	{
		if (choicesSplit.at(1) == "New Map")
		{
			NewMapInterface *newMap = new NewMapInterface(sf::Vector2f((float)(sGame.m_ScreenSize.x), (float)(sGame.m_ScreenSize.y)));
			newMap->registerReceiver(this);

			sGUIMANAGER.addFrame(newMap);
		}
		else if (choicesSplit.at(1) == "Load Map")
		{
			LoadMapInterface *loadMap = new LoadMapInterface(sf::Vector2f((float)(sGame.m_ScreenSize.x), (float)(sGame.m_ScreenSize.y)));
			loadMap->registerReceiver(this);

			sGUIMANAGER.addFrame(loadMap);
		}
		else if (choicesSplit.at(1) == "Save Map")
		{
			SaveMapInterface *saveMap = new SaveMapInterface(sf::Vector2f((float)(sGame.m_ScreenSize.x), (float)(sGame.m_ScreenSize.y)));
			saveMap->registerReceiver(this);

			sGUIMANAGER.addFrame(saveMap);
		}
		else if (choicesSplit.at(1) == "Exit Editor")
		{
			sGame.m_Running = false;
		}
	}
	else if (choicesSplit.at(0) == "Tools")
	{
		if (choicesSplit.at(1) == "Overlay Types")
		{
			if (choicesSplit.at(2) == "Infantry")
			{
				activateOverlay(Tile::Type::INFANTRY);
			}
			else if (choicesSplit.at(2) == "Light Vehicle")
			{
				activateOverlay(Tile::Type::LIGHT_VEHICLE);
			}
			else if (choicesSplit.at(2) == "Heavy Vehicle")
			{
				activateOverlay(Tile::Type::HEAVY_VEHICLE);
			}
			else if (choicesSplit.at(2) == "Naval")
			{
				activateOverlay(Tile::Type::NAVAL);
			}
			else if (choicesSplit.at(2) == "Air")
			{
				activateOverlay(Tile::Type::AIR);
			}
			else if (choicesSplit.at(2) == "Normal")
			{
				activateOverlay(Tile::Type::NUM_TYPES);
			}
		}
	}
}