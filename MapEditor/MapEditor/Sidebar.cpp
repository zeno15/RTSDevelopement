#include "Sidebar.h"

#include "Game.h"

Sidebar::Sidebar(void) :
	m_BackgroundQuads(sf::Quads, 4),
	m_SelectableTileQuads(sf::Quads, 0),
	m_ActiveToolDisplay(sf::Quads, 4),
	m_RightArrowButtonActive(false),
	m_LeftArrowButtonActive(false),
	m_PressedOverTile(false),
	m_CurrentPage(1),
	m_CurrentTile(0),
	m_ActiveTool(Tool::SELECT),
	m_ActiveToolName("DEFAULT")
{
}

Sidebar::~Sidebar(void)
{
}


void Sidebar::initialise(sf::FloatRect _bounds, std::vector<Tile> *_tileInfo)
{
	m_BackgroundQuads[0] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[1] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[2] = sf::Vertex(sf::Vector2f(_bounds.left + _bounds.width,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));
	m_BackgroundQuads[3] = sf::Vertex(sf::Vector2f(_bounds.left,
												   _bounds.top + _bounds.height),
									  sf::Color(155, 155, 155, 255));

	m_TileInfo = _tileInfo;

	GUIFrame *interaceGUI = new GUIFrame(); 

	

	GUIButtonTextured *leftButton =   new GUIButtonTextured(sf::Vector2f(_bounds.left + 32.0f, _bounds.top + 96.0f), 
															sf::Vector2f(32.0f, 32.0f), 
															&m_LeftArrowButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(32.0f, 320.0f, - TILESIZE_f, - TILESIZE_f));

	GUIButtonTextured *rightButton =  new GUIButtonTextured(sf::Vector2f(_bounds.left + _bounds.width - 32.0f, _bounds.top + 96.0f), 
															sf::Vector2f(32.0f, 32.0f), 
															&m_RightArrowButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(0.0f, 288.0f, TILESIZE_f, TILESIZE_f));

	GUIDropDownBox *toolSelection = new GUIDropDownBox(sf::Vector2f(_bounds.left + _bounds.width / 2.0f - 32.0f,
																	_bounds.top + 32.0f),
													   sf::Vector2f(96.0f,
																	20.0f));
	toolSelection->addOption("Select");
	toolSelection->addOption("Paint");
	toolSelection->addOption("Fill");
	toolSelection->addOption("Erase");

	m_ToolSelect = toolSelection;

	interaceGUI->addObject(leftButton);
	interaceGUI->addObject(rightButton);
	interaceGUI->addObject(toolSelection);

	sGUIMANAGER.addFrame(interaceGUI);

	initialiseTileSelection();

	changeTool(toolSelection->getActiveOption());
}

void Sidebar::update(sf::Time _delta)
{
	changeTool(m_ToolSelect->getActiveOption());
	if (m_LeftArrowButtonActive)
	{
		if (m_CurrentPage > 1)
		{
			m_CurrentPage -= 1;
			modifyTileSelection(m_CurrentPage);
		}
	}
	else if (m_RightArrowButtonActive)
	{
		if (m_CurrentPage < m_MaxPages)
		{
			m_CurrentPage += 1;
			modifyTileSelection(m_CurrentPage);
		}
	}

	unsigned int tilesPresent = m_SelectableTileQuads.getVertexCount() / 4 - 1;

	sf::Vector2f initialPosition(m_BackgroundQuads.getBounds().left + (200.0f - ((2.0f * m_TilesPerRow) - 1) * TILESIZE_f) / 2.0f,
								 m_BackgroundQuads.getBounds().top + 144.0f);

	if (!sGUIINPUT->getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
		sGUIINPUT->getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (unsigned int i = 0; i < m_TilesPerColumn; i += 1)
		{
			for (unsigned int j = 0; j < m_TilesPerRow; j += 1)
			{
				if (i * m_TilesPerRow + j >= tilesPresent) break;

				sf::FloatRect tileBounds(initialPosition.x + j * 2.0f * TILESIZE_f, 
										 initialPosition.y + i * 2.0f * TILESIZE_f, 
										 TILESIZE_f, 
										 TILESIZE_f);

				if (tileBounds.contains((float)(sf::Mouse::getPosition(*sGUIWINDOW).x), (float)(sf::Mouse::getPosition(*sGUIWINDOW).y)))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						m_PressedOverTile = true;
					}
					else if (m_PressedOverTile)
					{
						m_CurrentTile = (i * m_TilesPerRow + j) + (m_CurrentPage - 1) * m_TilesPerColumn * m_TilesPerRow;
						modifyTileSelection(m_CurrentPage);
					}
				}
			}
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_PressedOverTile)
	{
		m_PressedOverTile = false;
	}
}
void Sidebar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_BackgroundQuads,			_states);
	_target.draw(m_ActiveToolDisplay,		_states);
	_target.draw(m_SelectableTileQuads,		_states);

	_target.draw(m_PageNumber,				_states);

	_target.setView(sGame.m_View);
}

Tile Sidebar::getCurrentTile(void)
{
	return m_TileInfo->at(m_CurrentTile);
}
Sidebar::Tool Sidebar::getCurrentTool(void)
{
	return m_ActiveTool;
}

void Sidebar::initialiseTileSelection(void)
{
	//~ Sidebar is the 3 tools X X X
	//~
	//~ then the 2 arrows      X Y X
	//~ Y will be current tile
	//~ then for every 64 pixels we can have another row of tiles to pick from, reserving
	//~ 32 pixels at the bottom for the current page

	/* So minimum screen height is = 200 (minimap)
									  64 (tools)
									  64 (Arrows and current)
									  32 (page number)
								      64 (min number of tile rows)
									----
									 454
	*/

	m_TilesPerColumn = (unsigned int)(m_BackgroundQuads.getBounds().height - 64 - 64 - 32) / 64;
	m_TilesPerRow = (200 - 32) / 64 + 1;

	m_MaxPages = (int)((float)m_TileInfo->size() / (float)(m_TilesPerColumn * m_TilesPerRow));
	
	if ((float)m_TileInfo->size() / (float)(m_TilesPerColumn * m_TilesPerRow) - m_MaxPages > 0)
	{
		m_MaxPages += 1;
	}
	m_PageNumber = sf::Text("1 / 1", *sFont.getFont(FontManager::FontID::OPENSANS_REGULAR), 20);
	m_PageNumber.setOrigin(m_PageNumber.getGlobalBounds().left + m_PageNumber.getGlobalBounds().width / 2.0f, 
						   m_PageNumber.getGlobalBounds().top  + m_PageNumber.getGlobalBounds().height / 2.0f);
	m_PageNumber.setPosition(m_BackgroundQuads.getBounds().left + m_BackgroundQuads.getBounds().width / 2.0f,
							 m_BackgroundQuads.getBounds().top  + m_BackgroundQuads.getBounds().height - 32.0f);

	modifyTileSelection(1);
}
void Sidebar::modifyTileSelection(unsigned int _page)
{
	sf::Vector2f initialPosition(m_BackgroundQuads.getBounds().left + (200.0f - ((2.0f * m_TilesPerRow) - 1) * TILESIZE_f) / 2.0f,
								 m_BackgroundQuads.getBounds().top + 144.0f);

	unsigned int tilesOnPage = (m_TileInfo->size() - (_page - 1) * m_TilesPerColumn * m_TilesPerRow);

	m_SelectableTileQuads.resize((m_TileInfo->size() - (_page - 1) * m_TilesPerColumn * m_TilesPerRow) * 4);

	for (unsigned int i = 0; i < m_TilesPerColumn; i += 1)
	{
		for (unsigned int j = 0; j < m_TilesPerRow; j += 1)
		{
			if (i * m_TilesPerRow + j >= tilesOnPage) continue;

			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 0].position = sf::Vector2f(0.0f,		0.0f) +			initialPosition + sf::Vector2f(64.0f * j, 64.0f * i);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 1].position = sf::Vector2f(TILESIZE_f,	0.0f) +			initialPosition + sf::Vector2f(64.0f * j, 64.0f * i);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 2].position = sf::Vector2f(TILESIZE_f,	TILESIZE_f) +	initialPosition + sf::Vector2f(64.0f * j, 64.0f * i);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 3].position = sf::Vector2f(0.0f,		TILESIZE_f) +	initialPosition + sf::Vector2f(64.0f * j, 64.0f * i);

			unsigned int tileNumber = (_page - 1) * m_TilesPerColumn * m_TilesPerRow + i * m_TilesPerRow + j;

			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 0].texCoords = sf::Vector2f(m_TileInfo->at(tileNumber).m_TileTextureCoordinates.x,					m_TileInfo->at(tileNumber).m_TileTextureCoordinates.y);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 1].texCoords = sf::Vector2f(m_TileInfo->at(tileNumber).m_TileTextureCoordinates.x + TILESIZE_f,		m_TileInfo->at(tileNumber).m_TileTextureCoordinates.y);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 2].texCoords = sf::Vector2f(m_TileInfo->at(tileNumber).m_TileTextureCoordinates.x + TILESIZE_f,		m_TileInfo->at(tileNumber).m_TileTextureCoordinates.y + TILESIZE_f);
			m_SelectableTileQuads[(i * m_TilesPerRow + j) * 4 + 3].texCoords = sf::Vector2f(m_TileInfo->at(tileNumber).m_TileTextureCoordinates.x,					m_TileInfo->at(tileNumber).m_TileTextureCoordinates.y + TILESIZE_f);
		}
	}

	m_SelectableTileQuads.append(sf::Vertex(sf::Vector2f(m_BackgroundQuads.getBounds().left + (m_BackgroundQuads.getBounds().width - TILESIZE_f) / 2.0f,
														 m_BackgroundQuads.getBounds().top + 96.0f - TILESIZE_f / 2.0f),
											sf::Vector2f(m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.x,
														 m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.y)));
	m_SelectableTileQuads.append(sf::Vertex(sf::Vector2f(m_BackgroundQuads.getBounds().left + (m_BackgroundQuads.getBounds().width + TILESIZE_f) / 2.0f,
														 m_BackgroundQuads.getBounds().top + 96.0f - TILESIZE_f / 2.0f),
											sf::Vector2f(m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.x + TILESIZE_f,
														 m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.y)));
	m_SelectableTileQuads.append(sf::Vertex(sf::Vector2f(m_BackgroundQuads.getBounds().left + (m_BackgroundQuads.getBounds().width + TILESIZE_f) / 2.0f,
														 m_BackgroundQuads.getBounds().top + 96.0f + TILESIZE_f / 2.0f),
											sf::Vector2f(m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.x + TILESIZE_f,
														 m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.y + TILESIZE_f)));
	m_SelectableTileQuads.append(sf::Vertex(sf::Vector2f(m_BackgroundQuads.getBounds().left + (m_BackgroundQuads.getBounds().width - TILESIZE_f) / 2.0f,
														 m_BackgroundQuads.getBounds().top + 96.0f + TILESIZE_f / 2.0f),
											sf::Vector2f(m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.x,
														 m_TileInfo->at(m_CurrentTile).m_TileTextureCoordinates.y + TILESIZE_f)));

	m_PageNumber.setString(std::to_string(m_CurrentPage) + " / " + std::to_string(m_MaxPages));
}

void Sidebar::changeTool(std::string _toolName)
{
	if (m_ActiveToolName == _toolName) return;

	m_ActiveToolName = _toolName;

	if (m_ActiveToolName == "Select")
	{
		sCursor.changeCursor(CursorManager::CursorType::DEFAULT);
		m_ActiveTool = Tool::SELECT;
	}
	else if (m_ActiveToolName == "Paint")
	{
		sCursor.changeCursor(CursorManager::CursorType::PAINT);
		m_ActiveTool = Tool::PAINT;
	}
	else if (m_ActiveToolName == "Fill")
	{
		//sCursor.changeCursor(CursorManager::CursorType::DEFAULT);
		//m_ActiveTool = Tool::SELECT;
	}
	else if (m_ActiveToolName == "Erase")
	{
		sCursor.changeCursor(CursorManager::CursorType::ERASE);
		m_ActiveTool = Tool::ERASE;
	}

	std::cout << "Active tool: " << m_ActiveToolName << std::endl;
}