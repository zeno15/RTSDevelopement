#include "World.h"

#define WORLD_SCROLL_SPEED 500.0f

#include <fstream>
#include <string>

#include "Game.h"

World::World(void) :
	m_MapBackgroundVertices(sf::Quads, 0)
{
	Tile::loadTilesToTileInfoVector(&m_TileInformation);

	sInput.registerButton(sf::Mouse::Left);
}

World::~World(void)
{
	m_CollisionGrid.~CollisionGrid();

	sInput.unregisterButton(sf::Mouse::Left);
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

	if (!sInput.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::vector<WorldObject *> selectionObjects = std::vector<WorldObject *>();

		if (m_CollisionGrid.checkCollisions(&selectionObjects, MOUSE_POSITION_VIEW))
		{
			std::cout << "Selected " << selectionObjects.size() << " objects" << std::endl;
		}
	}
}
void World::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(TextureManager::TextureID::TILESHEET);

	_target.draw(m_MapBackgroundVertices,		_states);

	_target.draw(m_CollisionGrid,				_states);
	_target.draw(m_PathfindingGrid,				_states);
}

void World::load(std::string _filename)
{
	std::ifstream input(_filename);
	std::string line;

	if (!input.is_open())
	{
		std::cout << "Failed to load: " << _filename << std::endl;
		return;
	}

	std::getline(input, line);
	unsigned int found = line.find_first_of("0123456789");
	m_MapTileDimensions.y = (unsigned int)(std::stoi(line.substr(found, line.size())));

	std::getline(input, line);
	found = line.find_first_of("0123456789");
	m_MapTileDimensions.x = (unsigned int)(std::stoi(line.substr(found, line.size())));

	m_CollisionGrid.setCollisionArea(m_MapTileDimensions);
	m_PathfindingGrid.initialise(m_MapTileDimensions);

	m_MapBackgroundVertices.resize(4 * m_MapTileDimensions.x * m_MapTileDimensions.y);

	for (unsigned int i = 0; i < m_MapTileDimensions.y; i += 1)
	{
		for (unsigned int j = 0; j < m_MapTileDimensions.x; j += 1)
		{
			std::getline(input, line);

			Tile tile = m_TileInformation.at(Tile::getTileIndexFromName(line, m_TileInformation));

			loadToVertex(sf::Vector2u(j, i), tile);

			m_PathfindingGrid.setupAddTile(j, i, tile);
		}
	}

	
}

void World::loadToVertex(sf::Vector2u _position, Tile _tile)
{
	m_MapBackgroundVertices[4 * (_position.y * m_MapTileDimensions.x + _position.x) + 0]
						= sf::Vertex(sf::Vector2f((float)(_position.x + 0) * TILESIZE_f,
												  (float)(_position.y + 0) * TILESIZE_f),
									 sf::Color::White,
									 sf::Vector2f(_tile.m_TileTextureCoordinates.x,
												  _tile.m_TileTextureCoordinates.y));

	m_MapBackgroundVertices[4 * (_position.y * m_MapTileDimensions.x + _position.x) + 1]
						= sf::Vertex(sf::Vector2f((float)(_position.x + 1) * TILESIZE_f,
												  (float)(_position.y + 0) * TILESIZE_f),
									 sf::Color::White,
									 sf::Vector2f(_tile.m_TileTextureCoordinates.x + TILESIZE_f,
												  _tile.m_TileTextureCoordinates.y));

	m_MapBackgroundVertices[4 * (_position.y * m_MapTileDimensions.x + _position.x) + 2]
						= sf::Vertex(sf::Vector2f((float)(_position.x + 1) * TILESIZE_f,
												  (float)(_position.y + 1) * TILESIZE_f),
									 sf::Color::White,
									 sf::Vector2f(_tile.m_TileTextureCoordinates.x + TILESIZE_f,
												  _tile.m_TileTextureCoordinates.y + TILESIZE_f));

	m_MapBackgroundVertices[4 * (_position.y * m_MapTileDimensions.x + _position.x) + 3]
						= sf::Vertex(sf::Vector2f((float)(_position.x + 0) * TILESIZE_f,
												  (float)(_position.y + 1) * TILESIZE_f),
									 sf::Color::White,
									 sf::Vector2f(_tile.m_TileTextureCoordinates.x,
												  _tile.m_TileTextureCoordinates.y + TILESIZE_f));
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

Tile World::getTileFromCoords(sf::Vector2f _pixelCoords)
{
	return getTileFromCoords(sf::Vector2u((unsigned int)(_pixelCoords.x / TILESIZE_f), (unsigned int)(_pixelCoords.y / TILESIZE_f)));
}
Tile World::getTileFromCoords(sf::Vector2u _tileCoords)
{
	sf::Vector2f texCoords = m_MapBackgroundVertices[4 * (_tileCoords.y * m_MapTileDimensions.x + _tileCoords.x)].texCoords;

	for (unsigned int i = 0; i < m_TileInformation.size(); i += 1)
	{
		if (texCoords == m_TileInformation.at(i).m_TileTextureCoordinates)
		{
			return m_TileInformation.at(i);
		}
	}

	return m_TileInformation.front();
}