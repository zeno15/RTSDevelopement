#include "DebugManager.h"


DebugManager::DebugManager(void)
{
}


DebugManager::~DebugManager(void)
{
}

void DebugManager::calledNew(void * _object, std::string _file, int _line)
{
	m_InitialisedPointers.push_back(std::pair<unsigned int, std::string>((unsigned int)(_object), "[" + std::to_string(_line) + "] " + _file));
}
void DebugManager::calledDelete(void *_object)
{
	m_DeletedPointers.push_back((unsigned int)(_object));
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
}