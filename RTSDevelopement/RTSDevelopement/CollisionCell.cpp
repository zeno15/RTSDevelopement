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
		//~ Also check of the output collisions contains the current object

		if (objectBounds.intersects(m_TouchingWorldObjects.at(i)->getBounds()))
		{
			collision = true;
			_outputCollisions->push_back(m_TouchingWorldObjects.at(i));
		}
	}

	return collision;
}
bool CollisionCell::checkCollisionsWithin(std::vector<WorldObject *> *_outputCollisions, sf::Vector2f _position)
{
	bool collision = false;

	for (unsigned int i = 0; i < m_TouchingWorldObjects.size(); i += 1)
	{
		//~ Also check of the output collisions contains the current object

		if (m_TouchingWorldObjects.at(i)->getBounds().contains(_position))
		{
			collision = true;
			_outputCollisions->push_back(m_TouchingWorldObjects.at(i));
		}
	}

	return collision;
}
bool CollisionCell::checkCollisionsWithin(std::vector<WorldObject *> *_outputCollisions, sf::FloatRect _bounds)
{
	bool collision = false;

	for (unsigned int i = 0; i < m_TouchingWorldObjects.size(); i += 1)
	{
		if (_bounds.intersects(m_TouchingWorldObjects.at(i)->getBounds()))
		{
			bool present = false;

			for (unsigned int j = 0; j < _outputCollisions->size(); j += 1)
			{
				if (_outputCollisions->at(j) == m_TouchingWorldObjects.at(i))
				{
					present = true;
					break;
				}
			}

			if (!present)
			{
				collision = true;
				_outputCollisions->push_back(m_TouchingWorldObjects.at(i));
			}
		}
	}

	return collision;
}