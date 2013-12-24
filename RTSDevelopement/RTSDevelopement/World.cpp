#include "World.h"

#define WORLD_SCROLL_SPEED 400.0f

#include "Game.h"

World::World(void) :
	m_MapBackgroundVertices(sf::Quads, 0)
{
}

World::~World(void)
{
}


void World::setInterfaceSized(float _sideBarWidth, float _topBarHeight)
{
	m_SideBarWidth = _sideBarWidth;
	m_TopBarHeight = _topBarHeight;
}

void World::update(sf::Time _delta)	//~ Used to update animated tiles
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sGame.m_View.move(- WORLD_SCROLL_SPEED * _delta.asSeconds(), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sGame.m_View.move(+ WORLD_SCROLL_SPEED * _delta.asSeconds(), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sGame.m_View.move(0.0f, - WORLD_SCROLL_SPEED * _delta.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sGame.m_View.move(0.0f, + WORLD_SCROLL_SPEED * _delta.asSeconds());
	}

	ensureMapWithinBounds();
}
void World::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(TextureManager::TextureID::TILESHEET);

	_target.draw(m_MapBackgroundVertices,		_states);
}

void World::load(std::string _filename)
{
	sf::Image map = sf::Image();

	map.loadFromFile(_filename);

	m_MapTileDimensions = map.getSize();

	for (unsigned int i = 0; i < m_MapTileDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapTileDimensions.x; j += 1)
		{
			loadToVertex(sf::Vector2f(TILESIZE_f * j, TILESIZE_f * i), map.getPixel(j, i));
		}
	}
}

void World::loadToVertex(sf::Vector2f _position, sf::Color _colour)
{
	int index = m_WorldDataTables.findTileColourIndex(_colour);

	index = index == - 1 ? 0 : index;

	m_MapBackgroundVertices.append(sf::Vertex(sf::Vector2f(_position.x,
														   _position.y),
											  sf::Color::White,
											  sf::Vector2f(m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).first,
											               m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).second)));
	m_MapBackgroundVertices.append(sf::Vertex(sf::Vector2f(_position.x + TILESIZE_f,
														   _position.y),
											  sf::Color::White,
											  sf::Vector2f(m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).first + TILESIZE_f,
											               m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).second)));
	m_MapBackgroundVertices.append(sf::Vertex(sf::Vector2f(_position.x + TILESIZE_f,
														   _position.y + TILESIZE_f),
											  sf::Color::White,
											  sf::Vector2f(m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).first + TILESIZE_f,
											               m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).second + TILESIZE_f)));
	m_MapBackgroundVertices.append(sf::Vertex(sf::Vector2f(_position.x,
														   _position.y + TILESIZE_f),
											  sf::Color::White,
											  sf::Vector2f(m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).first,
											               m_WorldDataTables.m_TileTextureStartingCoordinates.at(index).second + TILESIZE_f)));
}

void World::ensureMapWithinBounds(void)
{
	if (sGame.m_View.getCenter().x - sGame.m_View.getSize().x / 2.0f < 0.0f)
	{
		sGame.m_View.setCenter(sGame.m_View.getSize().x / 2.0f, sGame.m_View.getCenter().y);
	}
	else if (sGame.m_View.getCenter().x + sGame.m_View.getSize().x / 2.0f - m_SideBarWidth > m_MapTileDimensions.x * TILESIZE_f)
	{
		sGame.m_View.setCenter(m_MapTileDimensions.x * TILESIZE_f - sGame.m_View.getSize().x / 2.0f + m_SideBarWidth, sGame.m_View.getCenter().y);
	}

	if (sGame.m_View.getCenter().y - sGame.m_View.getSize().y / 2.0f + m_TopBarHeight < 0.0f)
	{
		sGame.m_View.setCenter(sGame.m_View.getCenter().x, sGame.m_View.getSize().y / 2.0f - m_TopBarHeight);
	}
	else if (sGame.m_View.getCenter().y + sGame.m_View.getSize().y / 2.0f > m_MapTileDimensions.y * TILESIZE_f)
	{
		sGame.m_View.setCenter(sGame.m_View.getCenter().x, m_MapTileDimensions.y * TILESIZE_f - sGame.m_View.getSize().y / 2.0f);
	}
}