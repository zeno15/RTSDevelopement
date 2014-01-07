#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Tile.h"
#include "Minimap.h"
#include "Sidebar.h"
#include "TopBar.h"

#include "../../ZenosGUI/ZenosGUI/Receiver.h"

#define TILESIZE_f 32.0f
#define TILESIZE_u 32u
#define TILESIZE_i 32

class Map : public sf::Drawable, public Receiver
{
public:
	Map(void);
	~Map(void);

	void load(std::string _filename);
	void save(std::string _filename);
	void create(sf::Vector2u _mapDimensions, std::vector<unsigned int> _tileIndecies = std::vector<unsigned int>());	

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void changeTile(unsigned int _xTile, unsigned int _yTile, Tile _type);

private:
	void loadTileInformation(void);

	void ensureWithinBounds(void);

	void fill(Tile _replacingTile, Tile _newTile, sf::Vector2u _tileCoords);
	void fillRect(Tile _replacingTile, Tile _newTile, sf::Vector2u _tileCoords, sf::RectangleShape _rect);

	Tile getTileFromCoords(unsigned int _x, unsigned int _y);

	void createSavedMapFrame(void);

	void updateSelectionBox(bool _finalise);

	void activateOverlay(Tile::Type _type);

	void handleDropMenuChoices(std::string _choice);

private:
	bool											DEBUG_initial;

	sf::Vector2u									m_MapDimensions; //~ In 32x32 pixel tiles

	sf::VertexArray									m_BackgroundTiles;
	sf::VertexArray									m_OverlayQuads;

	std::vector<Tile>								m_TileInformation;

	float											m_SideBarWidth;
	float											m_TopBarHeight;

	bool											m_MenubarIsActive;

	bool											m_Selecting;
	bool											m_DisplaySelectionBox;
	sf::Vector2f									m_InitialSelectedPosition;
	std::vector<sf::RectangleShape>					m_SelectionBox;

	Tile::Type									m_OverlayToDraw;

	Minimap											m_Minimap;
	Sidebar											m_SideBar;
	TopBar											m_TopBar;
};

#endif //~ INCLUDED_MAP_H