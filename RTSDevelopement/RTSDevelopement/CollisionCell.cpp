#include "CollisionCell.h"


CollisionCell::CollisionCell(sf::FloatRect _bounds) :
	m_Bounds(_bounds),
	m_Rectangle(sf::Vector2f(_bounds.width, _bounds.height))
{
	m_Rectangle.setPosition(_bounds.left, _bounds.top);
	m_Rectangle.setFillColor(sf::Color::Transparent);
	m_Rectangle.setOutlineThickness(1.0f);
}

CollisionCell::~CollisionCell(void)
{
}


void CollisionCell::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.draw(m_Rectangle,			_states);
}

sf::FloatRect CollisionCell::getBounds(void)
{
	return m_Bounds;
}

void CollisionCell::addWorldObject(WorldObject *_wObj)
{
	m_TouchingWorldObjects.push_back(_wObj);
	m_Rectangle.setOutlineColor(sf::Color::Red);
}
void CollisionCell::removeWorldObject(WorldObject *_wObj)
{
	for (unsigned int i = 0; i < m_TouchingWorldObjects.size(); i += 1)
	{
		if (m_TouchingWorldObjects.at(i) == _wObj)
		{
			m_TouchingWorldObjects.erase(m_TouchingWorldObjects.begin() + i);
			break;
		}
	}

	if (m_TouchingWorldObjects.size() == 0)
	{
		m_Rectangle.setOutlineColor(sf::Color::White);
	}
}

bool CollisionCell::checkCollisionsWithin(std::vector<WorldObject *> *_outputCollisions, WorldObject *_wObj)
{
	sf::FloatRect objectBounds = _wObj->getBounds();

	bool collision = false;

	for (unsigned int i = 0; i < m_TouchingWorldObjects.size(); i += 1)
	{
		if (m_TouchingWorldObjects.at(i) == _wObj) continue;

		if (objectBounds.intersects(m_TouchingWorldObjects.at(i)->getBounds()))
		{
			collision = true;
			_outputCollisions->push_back(m_TouchingWorldObjects.at(i));
		}
	}

	return collision;
}