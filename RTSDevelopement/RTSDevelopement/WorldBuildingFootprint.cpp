#include "WorldBuildingFootprint.h"

#include "Game.h"

WorldBuildingFootprint::WorldBuildingFootprint(sf::Vector2f _size, Tile::Type _desiredTerrain) :
	WorldObject(WorldObject::ObjectType::FOOTPRINT, MOUSE_POSITION_VIEW, _size, 100),
	m_Footprint(sf::Quads, 0),
	m_Type(_desiredTerrain)
{
	m_FootprintSizeTiles = sf::Vector2u((unsigned int)(_size.x / TILESIZE_f), (unsigned int)(_size.y / TILESIZE_f));

	m_Footprint.resize(4 * m_FootprintSizeTiles.x * m_FootprintSizeTiles.y);

	relocateOnPosition();
}

WorldBuildingFootprint::~WorldBuildingFootprint(void)
{
}


void WorldBuildingFootprint::update(sf::Time _delta)
{
	if (MOUSE_POSITION_VIEW.x < 0.0f || MOUSE_POSITION_VIEW.y < 0.0f)
	{

	}
	else
	{
		m_WorldObjectPosition = MOUSE_TILE_POSITION_VIEW;
	}
	
	relocateOnPosition();

	updateCollisions();

	std::vector<WorldObject *> collideables = std::vector<WorldObject *>();
	bool valid = true;

	for (unsigned int i = 0; i < m_TouchingCells.size(); i += 1)
	{
		m_TouchingCells.at(i)->checkCollisionsWithin(&collideables, this);
		if (collideables.size() > 0) 
		{
			valid = false;
			break;
		}
	}

	//~ Check terrain stuff here
	
	for (unsigned int i = 0; i < m_FootprintSizeTiles.y; i += 1)
	{
		for (unsigned int j = 0; j < m_FootprintSizeTiles.x; j += 1)
		{
			sf::Vector2f f = sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f + j * TILESIZE_f,
										  m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f + i * TILESIZE_f);

			Tile tile = sWorld.getTileFromCoords(f);

			if (!tile.m_TileUnitPassValues.at(m_Type))
			{
				valid = false;
				break;
			}
		}
	}


	changeColour(valid ? sf::Color::White : sf::Color::Red);

}
void WorldBuildingFootprint::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(0);

	_target.draw(m_Footprint,			_states);


}


void WorldBuildingFootprint::relocateOnPosition(void)
{
	for (unsigned int i = 0; i < m_FootprintSizeTiles.y; i += 1)
	{
		for (unsigned int j = 0; j < m_FootprintSizeTiles.x; j += 1)
		{
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 0].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f + (j + 0) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f + (i + 0) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 0].texCoords = 
							sf::Vector2f(0.0f,
										 384.0f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 1].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f + (j + 1) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f + (i + 0) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 1].texCoords = 
							sf::Vector2f(0.0f + TILESIZE_f,
										 384.0f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 2].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f + (j + 1) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f + (i + 1) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 2].texCoords = 
							sf::Vector2f(0.0f + TILESIZE_f,
										 384.0f + TILESIZE_f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 3].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_WorldObjectSize.x / 2.0f + (j + 0) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_WorldObjectSize.y / 2.0f + (i + 1) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 3].texCoords = 
							sf::Vector2f(0.0f,
										 384.0f + TILESIZE_f);

		}
	}
}

void WorldBuildingFootprint::changeColour(sf::Color _colour)
{
	for (unsigned int i = 0; i < m_Footprint.getVertexCount(); i += 1)
	{
		m_Footprint[i].color = _colour;
	}
}