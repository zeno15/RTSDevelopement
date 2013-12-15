#include "GUIManager.h"


GUIManager::GUIManager(void)
{
}

GUIManager::~GUIManager(void)
{
}


void GUIManager::addFrame(GUIFrame *_frame)
{
	m_Frames.push_back(_frame);
}

void GUIManager::update(sf::Time _delta)
{
	for (unsigned int i = 0; i < m_Frames.size(); i += 1)
	{
		m_Frames.at(i)->update(_delta);
		
		if (m_Frames.at(i)->toRemove())
		{
			delete m_Frames.at(i);
			m_Frames.erase(m_Frames.begin() + i);
		}
	}
}
	
void GUIManager::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	for (unsigned int i = 0; i < m_Frames.size(); i += 1)
	{
		_target.draw(*m_Frames.at(i),		_states);
	}
}