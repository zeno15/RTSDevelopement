#ifndef INCLUDED_DEBUGMANAGER_H
#define INCLUDED_DEBUGMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#define mDebugNew(X) sGame.m_DebugManager.calledNew(X, __FILE__, __LINE__);
#define mDebugDelete(X) sGame.m_DebugManager.calledDelete(X);

class DebugManager : public sf::Drawable
{
public:
	DebugManager(void);
	~DebugManager(void);

	void initialise(void);

	void calledNew(void * _object, std::string _file, int _line);
	void calledDelete(void *_object);
	void printPointers(void);
	void analysePointers(void);
	
	void log(std::string _text);
	void logError(std::string _text);

	virtual void update(sf::Time _delta);	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	std::vector<std::pair<unsigned int, std::string>>						m_InitialisedPointers;
	std::vector<unsigned int>												m_DeletedPointers;

	std::vector<float>														m_FrameTimes;
	unsigned int															m_FrameIndex;
	sf::Text																m_FPSText;

};

#endif //~ INCLUDED_DEBUGMANAGER_H