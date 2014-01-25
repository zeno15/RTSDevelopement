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
	}

	for (unsigned int i = 0; i < collideables.size(); i += 1)
	{
		if (collideables.at(i)->getBounds().intersects(m_Footprint.getBounds()))
		{
			valid = false;
			break;
		}
	}

	//~ Check terrain stuff here
	if (valid)
	{
		for (unsigned int i = 0; i < m_FootprintSizeTiles.y; i += 1)
		{
			for (unsigned int j = 0; j < m_FootprintSizeTiles.x; j += 1)
			{
				Tile tile = sWorld.getTileFromCoords(sf::Vector2f(m_WorldObjectPosition.x - m_SizingOffset.x + j * TILESIZE_f,
																  m_WorldObjectPosition.y - m_SizingOffset.y + i * TILESIZE_f));

				if (!tile.m_TileUnitPassValues.at(m_Type))
				{
					valid = false;
					break;
				}
			}
		}
	}


	changeColour(valid ? sf::Color::White : sf::Color::Red);

	if (valid && !sInput.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		unsigned int x = (unsigned int)(m_Footprint.getBounds().left + m_Footprint.getBounds().width / 2.0f);
		unsigned int y = (unsigned int)(m_Footprint.getBounds().top + m_Footprint.getBounds().height / 2.0f);

		notifyReceivers(MessageData::BUILDING_PLACE_DATA, 0.0f, std::to_string(x) + "x" + std::to_string(y));
		kill();
	}
}
void WorldBuildingFootprint::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(0);

	_target.draw(m_Footprint,			_states);
}


void WorldBuildingFootprint::relocateOnPosition(void)
{
	m_SizingOffset = sf::Vector2f(m_WorldObjectSize.x / 2.0f, m_WorldObjectSize.y / 2.0f);

	if ((m_WorldObjectSize.x / TILESIZE_f) / 2.0f - (int((m_WorldObjectSize.x / TILESIZE_f) / 2.0f) > 0.0f))
	{
		m_SizingOffset.x -= TILESIZE_f / 2.0f;
	}
	if ((m_WorldObjectSize.y / TILESIZE_f) / 2.0f - (int((m_WorldObjectSize.y / TILESIZE_f) / 2.0f) > 0.0f))
	{
		m_SizingOffset.y -= TILESIZE_f / 2.0f;
	}

	for (unsigned int i = 0; i < m_FootprintSizeTiles.y; i += 1)
	{
		for (unsigned int j = 0; j < m_FootprintSizeTiles.x; j += 1)
		{
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 0].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_SizingOffset.x + (j + 0) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_SizingOffset.y + (i + 0) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 0].texCoords = 
							sf::Vector2f(0.0f,
										 384.0f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 1].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_SizingOffset.x + (j + 1) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_SizingOffset.y + (i + 0) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 1].texCoords = 
							sf::Vector2f(0.0f + TILESIZE_f,
										 384.0f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 2].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_SizingOffset.x + (j + 1) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_SizingOffset.y + (i + 1) * TILESIZE_f);
			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 2].texCoords = 
							sf::Vector2f(0.0f + TILESIZE_f,
										 384.0f + TILESIZE_f);

			m_Footprint[4 * (i * m_FootprintSizeTiles.x + j) + 3].position = 
							sf::Vector2f(m_WorldObjectPosition.x - m_SizingOffset.x + (j + 0) * TILESIZE_f,
										 m_WorldObjectPosition.y - m_SizingOffset.y + (i + 1) * TILESIZE_f);
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