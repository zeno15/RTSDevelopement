#ifndef INCLUDED_WORLD_H
#define INCLUDED_WORLD_H

#define TILESIZE_f 32.0f
#define TILESIZE_u 32u
#define TILESIZE_i 32

#include <SFML/Graphics.hpp>
#include <string>

#include "WorldDataTables.h"
#include "CollisionGrid.h"
#include "PathfindingGrid.h"
#include "Tile.h"

class World : public sf::Drawable
{
public:
	World(void);
	~World(void);

	void setInterfaceSized(float _sideBarWidth, float _topBarHeight);

	virtual void update(sf::Time _delta);	//~ Used to update animated tiles and move map
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void load(std::string _filename);

	Tile getTileFromCoords(sf::Vector2f _pixelCoords);
	Tile getTileFromCoords(sf::Vector2u _tileCoords);

private:
	void loadToVertex(sf::Vector2u _position, Tile _tile);

	void ensureMapWithinBounds(void);

	void updateSelectionBox(sf::Vector2f _currentCoords);

public:
	WorldDataTables								m_WorldDataTables;

	CollisionGrid								m_CollisionGrid;

	PathfindingGrid								m_PathfindingGrid;
private:
	sf::VertexArray								m_MapBackgroundVertices;

	sf::Vector2u								m_MapTileDimensions;

	float										m_SideBarWidth;
	float										m_TopBarHeight;

	std::vector<Tile>							m_TileInformation;

	sf::Vector2f								m_MouseDownCoordinates;
	sf::RectangleShape							m_SelectionBox;

	bool										m_RenderSelectionBox;
};

#endif //~ INCLUDED_WORLD_H