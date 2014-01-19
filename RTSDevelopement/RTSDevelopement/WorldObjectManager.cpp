#include "WorldObjectManager.h"

#include "Game.h"
#include "WorldUnit.h"
#include "SteeringBehaviourUnitBase.h"

WorldObjectManager::WorldObjectManager(void)
{
}

WorldObjectManager::~WorldObjectManager(void)
{
	for (unsigned int i = 0; i < m_WorldObjects.size(); i += 1)
	{
		mDebugDelete(m_WorldObjects.at(i))
		delete m_WorldObjects.at(i);
	}
}


void WorldObjectManager::update(sf::Time _delta)
{
	for (unsigned int i = 0; i < m_WorldObjects.size(); i += 1)
	{
		m_WorldObjects.at(i)->update(_delta);

		if (!m_WorldObjects.at(i)->isAlive())
		{
			mDebugDelete(m_WorldObjects.at(i))
			delete m_WorldObjects.at(i);
			m_WorldObjects.erase(m_WorldObjects.begin() + i);
		}
	}
}
void WorldObjectManager::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	for (unsigned int i = 0; i < m_WorldObjects.size(); i += 1)
	{
		_target.draw(*m_WorldObjects.at(i),			_states);
	}
}

void WorldObjectManager::addWorldObject(WorldObject *_worldObject)
{
	m_WorldObjects.push_back(_worldObject);
}

WorldObject *WorldObjectManager::getObject(unsigned int _index)
{
	return m_WorldObjects.at(_index);
}
unsigned int WorldObjectManager::getWorldObjectCount(void)
{
	return m_WorldObjects.size();
}