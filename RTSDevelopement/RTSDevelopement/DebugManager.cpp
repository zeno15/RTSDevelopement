#include "DebugManager.h"

#include "Game.h"

#define DEBUGMANAGER_FRAME_RECALL		250

DebugManager::DebugManager(void) :
	m_FrameIndex(0),
	m_FrameTimes(DEBUGMANAGER_FRAME_RECALL, 0.0f)
{
}

DebugManager::~DebugManager(void)
{
}


void DebugManager::initialise(void)
{
	m_FPSText = sf::Text("00 FPS", *sGame.m_FontManager.getFont(7), 20);
	m_WorldObjectCountText = sf::Text("00 World Objects", *sGame.m_FontManager.getFont(7), 20);
	m_WorldObjectCountText.setPosition(0.0f, 20.0f);
}

void DebugManager::calledNew(void * _object, std::string _file, int _line)
{
	#ifdef _DEBUG
	m_InitialisedPointers.push_back(std::pair<unsigned int, std::string>((unsigned int)(_object), "[" + std::to_string(_line) + "] " + _file));
	#endif //~ _DEBUG
}
void DebugManager::calledDelete(void *_object)
{
	#ifdef _DEBUG
	m_DeletedPointers.push_back((unsigned int)(_object));
	#endif //~ _DEBUG
}
void DebugManager::printPointers(void)
{
	for (std::pair<unsigned int, std::string> pair : m_InitialisedPointers)
	{
		std::cout << "Pointer: " << pair.first << ", " << pair.second << std::endl;
	}
}
void DebugManager::analysePointers(void)
{
	#ifdef _DEBUG
	std::vector<std::pair<unsigned int, std::string>> unDeletedPointers = std::vector<std::pair<unsigned int, std::string>>();

	for (unsigned int i = 0; i < m_InitialisedPointers.size(); i += 1)
	{
		bool found = false;
		for (unsigned int j = 0; j < m_DeletedPointers.size(); j += 1)
		{
			if (m_DeletedPointers.at(j) == m_InitialisedPointers.at(i).first)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			unDeletedPointers.push_back(m_InitialisedPointers.at(i));
		}
	}

	std::cout << "============ DEBUG INFO ============" << std::endl;
	std::cout << "There are " << unDeletedPointers.size() << " undeleted pointers" << std::endl;

	for (std::pair<unsigned int, std::string> pair : unDeletedPointers)
	{
		std::cout << "Undeleted pointer: " << pair.first << ", " << pair.second << std::endl;
	}

	if (unDeletedPointers.size() > 0)
	{
		getchar();
	}
	#endif //~ _DEBUG
}

void DebugManager::update(sf::Time _delta)
{
	m_FrameTimes.at(m_FrameIndex) = _delta.asSeconds();

	m_FrameIndex += 1;
	if (m_FrameIndex >= DEBUGMANAGER_FRAME_RECALL) 
	{
		m_FrameIndex = 0;
		float total = 0.0f;
		for (unsigned int i = 0; i < m_FrameTimes.size(); i += 1)
		{
			total += m_FrameTimes.at(i);
		}
		m_FPSText.setString(std::to_string(1.0f / (total / (float)DEBUGMANAGER_FRAME_RECALL)) + " FPS");

		m_WorldObjectCountText.setString(std::to_string(sGame.m_WorldObjectManager.getWorldObjectCount()) + " World Objects");
	}
}
void DebugManager::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
	_target.setView(sGame.m_Window.getDefaultView());

	_target.draw(m_FPSText,			_states);
	_target.draw(m_WorldObjectCountText,			_states);
	
	_target.setView(sGame.m_View);
}