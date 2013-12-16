#ifndef INCLUDED_DEBUGMANAGER_H
#define INCLUDED_DEBUGMANAGER_H

#include <iostream>
#include <string>
#include <vector>

#define mDebugNew(X) sGame.m_DebugManager.calledNew(X, __FILE__, __LINE__);
#define mDebugDelete(X) sGame.m_DebugManager.calledDelete(X);

class DebugManager
{
public:
	DebugManager(void);
	~DebugManager(void);

	void calledNew(void * _object, std::string _file, int _line);
	void calledDelete(void *_object);
	void printPointers(void);
	void analysePointers(void);
	
	void log(std::string _text);
	void logError(std::string _text);

private:
	std::vector<std::pair<unsigned int, std::string>>						m_InitialisedPointers;
	std::vector<unsigned int>												m_DeletedPointers;

};

#endif //~ INCLUDED_DEBUGMANAGER_H