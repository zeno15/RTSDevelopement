#ifndef INCLUDED_SIDEBAR_H
#define INCLUDED_SIDEBAR_H

#include <SFML/Graphics.hpp>

#include "Tile.h"

class Sidebar : public sf::Drawable
{
public:
	Sidebar(void);
	~Sidebar(void);

	void initialise(sf::FloatRect _bounds, std::vector<Tile> *_tileInfo);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void initialiseTileSelection(void);

private:
	sf::VertexArray													m_BackgroundQuads;

	sf::VertexArray													m_SelectableTileQuads;

	bool															m_SelectButtonActive;
	bool															m_EraseButtonActive;
	bool															m_PaintButtonActive;

	bool															m_LeftArrowButtonActive;
	bool															m_RightArrowButtonActive;

	std::vector<Tile>  *											m_TileInfo;
};

#endif //~ INCLUDED_SIDEBAR_H