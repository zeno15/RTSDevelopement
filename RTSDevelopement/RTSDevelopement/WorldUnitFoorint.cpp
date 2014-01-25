#include "WorldUnitFootprint.h"

#include "Game.h"
#include "MessageData.h"

WorldUnitFootprint::WorldUnitFootprint(sf::Vector2f _position) : 
	WorldObject(WorldObject::ObjectType::FOOTPRINT, _position, sf::Vector2f(32.0f, 32.0f), 1),
	m_Vertex(sf::Quads, 4),
	m_Type(Tile::Type::HEAVY_VEHICLE)
{
	relocateOnPosition();
}


WorldUnitFootprint::~WorldUnitFootprint(void)
{
}


void WorldUnitFootprint::update(sf::Time _delta)
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
		if (collideables.at(i)->getBounds().intersects(m_Vertex.getBounds()))
		{
			valid = false;
			break;
		}
	}

	//~ Check terrain stuff here
	if (valid)
	{
		Tile tile = sWorld.getTileFromCoords(sf::Vector2f(m_WorldObjectPosition.x,
														  m_WorldObjectPosition.y));

		if (!tile.m_TileUnitPassValues.at(m_Type))
		{
			valid = false;
		}

	}


	changeColour(valid ? sf::Color::White : sf::Color::Red);

	if (valid && !sInput.getButtonState(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		unsigned int x = (unsigned int)(m_Vertex.getBounds().left + m_Vertex.getBounds().width  / 2.0f);
		unsigned int y = (unsigned int)(m_Vertex.getBounds().top  + m_Vertex.getBounds().height / 2.0f);

		notifyReceivers(MessageData::UNIT_PLACE_DATA, 0.0f, std::to_string(x) + "x" + std::to_string(y));
		kill();
	}
}
void WorldUnitFootprint::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_states.texture = sTexture.getTexture(0);

	_target.draw(m_Vertex,					_states);
}

void WorldUnitFootprint::relocateOnPosition(void)
{
	m_Vertex[0] = sf::Vertex(sf::Vector2f(m_WorldObjectPosition.x,
										  m_WorldObjectPosition.y),
							 sf::Color(255, 255, 255, 255),
							 sf::Vector2f(0.0f,
										  384.0f));
	m_Vertex[1] = sf::Vertex(sf::Vector2f(m_WorldObjectPosition.x + TILESIZE_f,
										  m_WorldObjectPosition.y),
							 sf::Color(255, 255, 255, 255),
							 sf::Vector2f(0.0f + TILESIZE_f,
										  384.0f));
	m_Vertex[2] = sf::Vertex(sf::Vector2f(m_WorldObjectPosition.x + TILESIZE_f,
										  m_WorldObjectPosition.y + TILESIZE_f),
							 sf::Color(255, 255, 255, 255),
							 sf::Vector2f(0.0f + TILESIZE_f,
										  384.0f + TILESIZE_f));
	m_Vertex[3] = sf::Vertex(sf::Vector2f(m_WorldObjectPosition.x,
										  m_WorldObjectPosition.y + TILESIZE_f),
							 sf::Color(255, 255, 255, 255),
							 sf::Vector2f(0.0f,
										  384.0f + TILESIZE_f));
}

void WorldUnitFootprint::changeColour(sf::Color _colour)
{
	for (unsigned int i = 0; i < m_Vertex.getVertexCount(); i += 1)
	{
		m_Vertex[i].color = _colour;
	}
}