#ifndef INCLUDED_SIDEBAR_H
#define INCLUDED_SIDEBAR_H

#include <SFML/Graphics.hpp>

#include "Tile.h"

#include "../../ZenosGUI/ZenosGUI/Receiver.h"

class Sidebar : public sf::Drawable, public Receiver
{
public:
	Sidebar(void);
	~Sidebar(void);

	enum Tool {SELECT,
			   PAINT,
			   ERASE,
			   FILL,
			   NUM_TOOLS};

	void initialise(sf::FloatRect _bounds, std::vector<Tile> *_tileInfo);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	Tile getCurrentTile(void);
	Tool getCurrentTool(void);

private:
	void initialiseTileSelection(void);
	void modifyTileSelection(unsigned int _page);

	void changeTool(std::string _toolName);

private:
	sf::VertexArray													m_BackgroundQuads;

	sf::VertexArray													m_SelectableTileQuads;
	sf::VertexArray													m_ActiveToolDisplay;

	std::string														m_ActiveToolName;

	sf::Text														m_PageNumber;

	unsigned int													m_CurrentTile;
	unsigned int													m_MaxPages;
	unsigned int													m_CurrentPage;
	unsigned int													m_TilesPerColumn;
	unsigned int													m_TilesPerRow;

	unsigned int													m_LeftButtonId;
	unsigned int													m_RightButtonId;

	Tool															m_ActiveTool;

	bool															m_PressedOverTile;
	bool															m_GUIActive;

	std::vector<Tile>  *											m_TileInfo;
};

#endif //~ INCLUDED_SIDEBAR_H