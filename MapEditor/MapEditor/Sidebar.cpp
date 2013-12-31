#include "Sidebar.h"

#include "Game.h"

Sidebar::Sidebar(void) :
	m_BackgroundQuads(sf::Quads, 4),
	m_SelectableTileQuads(sf::Quads, 0),
	m_SelectButtonActive(false),
	m_EraseButtonActive(false),
	m_PaintButtonActive(false),
	m_RightArrowButtonActive(false),
	m_LeftArrowButtonActive(false)
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

	GUIFrame *ToolButtons = new GUIFrame(); 

	GUIButtonTextured *selectButton = new GUIButtonTextured(sf::Vector2f(_bounds.left + 32.0f, _bounds.top + 32.0f), 
															sf::Vector2f(32.0f, 32.0f), 
															&m_SelectButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(0.0f, 256.0f, TILESIZE_f, TILESIZE_f)); 

	GUIButtonTextured *paintButton =  new GUIButtonTextured(sf::Vector2f(_bounds.left + _bounds.width / 2.0f, _bounds.top + 32.0f), 
															sf::Vector2f(32.0f, 32.0f), 
															&m_PaintButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(64.0f, 256.0f, TILESIZE_f, TILESIZE_f)); 

	GUIButtonTextured *eraseButton =  new GUIButtonTextured(sf::Vector2f(_bounds.left + _bounds.width - 32.0f, _bounds.top + 32.0f), 
															sf::Vector2f(32.0f, 32.0f), 
															&m_EraseButtonActive, 
															sGUITEX->getTexture(TextureManager::TextureID::TILESHEET), 
															sf::FloatRect(32.0f, 256.0f, TILESIZE_f, TILESIZE_f));

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

	ToolButtons->addObject(selectButton);
	ToolButtons->addObject(paintButton);
	ToolButtons->addObject(eraseButton);
	ToolButtons->addObject(leftButton);
	ToolButtons->addObject(rightButton);

	sGUIMANAGER.addFrame(ToolButtons);

	initialiseTileSelection();
}

void Sidebar::update(sf::Time _delta)
{
	if (m_SelectButtonActive)
	{
		sCursor.changeCursor(CursorManager::CursorType::DEFAULT);
	}
	else if (m_EraseButtonActive)
	{
		sCursor.changeCursor(CursorManager::CursorType::ERASE);
	}
	else if (m_PaintButtonActive)
	{
		sCursor.changeCursor(CursorManager::CursorType::PAINT);
	}
	else if (m_LeftArrowButtonActive)
	{
		std::cout << "Left arrow" << std::endl;
	}
	else if (m_RightArrowButtonActive)
	{
		std::cout << "Right arrow" << std::endl;
	}
}
void Sidebar::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(_target.getDefaultView());

	_target.draw(m_BackgroundQuads,		_states);

	_target.setView(sGame.m_View);
}

void Sidebar::initialiseTileSelection(void)
{
	std::cout << "There are " << m_TileInfo->size() << " tiles to select from" << std::endl;

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

	int numTileRows = (int)(m_BackgroundQuads.getBounds().height - 64 - 64 - 32) / 64;
	int numTileColumns = (200 - 32) / 64;

	std::cout << "For a screen height of " << sGame.m_ScreenSize.y << ", we can have " << numTileRows << " rows of tiles per page." << std::endl;
	std::cout << "And in the 200 wide sidebar we can have " << numTileColumns << " columns of tiles per page" << std::endl;
	std::cout << "So we will need " << (float)m_TileInfo->size() / (float)(numTileColumns * numTileRows) << " pages." << std::endl;



}