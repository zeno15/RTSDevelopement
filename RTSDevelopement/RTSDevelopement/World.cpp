#include "World.h"

#define WORLD_SCROLL_SPEED 500.0f

#include <fstream>
#include <string>

#include "Game.h"
#include "HelperFunctions.h"
#include "WorldUnit.h"

World::World(void) :
	m_MapBackgroundVertices(sf::Quads, 0),
	DEBUG_path(sf::LinesStrip, 0)
{
	Tile::loadTilesToTileInfoVector(&m_TileInformation);

	m_SelectionBox.setFillColor(sf::Color(255, 255, 255, 25));
	m_SelectionBox.setOutlineThickness(1.0f);

	sInput.registerButton(sf::Mouse::Left);
	sInput.registerButton(sf::Mouse::Right);
}

World::~World(void)
{
	m_CollisionGrid.~CollisionGrid();

	sInput.unregisterButton(sf::Mouse::Left);
	sInput.unregisterButton(sf::Mouse::Right);
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
		m_MouseDownCoordinates = MOUSE_POSITION_VIEW;
	}
	else if (sInput.getButtonState(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			for (unsigned int i = 0; i < m_SelectedWorldObjects.size(); i += 1)
			{
				m_SelectedWorldObjects.at(i)->deselect();
			}
			m_SelectedWorldObjects.clear();
		}

		if (m_MouseDownCoordinates == MOUSE_POSITION_VIEW)
		{
			//~ Click over
			if (m_CollisionGrid.checkCollisions(&m_SelectedWorldObjects, MOUSE_POSITION_VIEW))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					m_SelectedWorldObjects.back()->toggleSelect();
				}
				else
				{
					m_SelectedWorldObjects.back()->select();
				}
			}
		}
		else
		{
			//~ Pan/drag over
			m_RenderSelectionBox = false;

			if (m_CollisionGrid.checkCollisions(&m_SelectedWorldObjects, m_SelectionBox.getGlobalBounds()))
			{
				for (unsigned int i = 0; i < m_SelectedWorldObjects.size(); i += 1)
				{
					m_SelectedWorldObjects.at(i)->select();
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_MouseDownCoordinates != MOUSE_POSITION_VIEW)
		{
			//~ Update pan/drag
			updateSelectionBox(MOUSE_POSITION_VIEW);
			m_RenderSelectionBox = true;
		}
	}

	std::vector<PathfindingNode *> path = std::vector<PathfindingNode *>();

	if (m_SelectedWorldObjects.size() > 0)
	{
		if (sInput.getButtonState(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_PathfindingGrid.requestPath(m_SelectedWorldObjects.at(0)->getPosition(), MOUSE_POSITION_VIEW, Tile::Type::HEAVY_VEHICLE, &path);
			
			std::vector<sf::Vector2f> pointPath;

			for (unsigned int i = 0; i < path.size(); i += 1)
			{
				sf::Vector2f point(path.at(i)->getGridCoords().x * TILESIZE_f + TILESIZE_f / 2.0f, path.at(i)->getGridCoords().y * TILESIZE_f + TILESIZE_f / 2.0f);

				pointPath.push_back(point);
			}

			WorldUnit *unit = (WorldUnit *)m_SelectedWorldObjects.at(0);

			unit->followPath(pointPath);
		}
	}
}
void World::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(0);

	_target.draw(m_MapBackgroundVertices,		_states);

	//_target.draw(m_CollisionGrid,				_states);
	//_target.draw(m_PathfindingGrid,				_states);

	if (m_RenderSelectionBox)
	{
		_target.draw(m_SelectionBox,			_states);
	}
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

void World::updateSelectionBox(sf::Vector2f _currentCoords)
{
	sf::Vector2f size(fabsf(m_MouseDownCoordinates.x - _currentCoords.x) - 2.0f,
					  fabsf(m_MouseDownCoordinates.y - _currentCoords.y) - 2.0f);

	sf::Vector2f pos(std::min(m_MouseDownCoordinates.x, _currentCoords.x) + 1.0f,
					 std::min(m_MouseDownCoordinates.y, _currentCoords.y) + 1.0f);

	m_SelectionBox.setSize(size);
	m_SelectionBox.setPosition(pos);
}