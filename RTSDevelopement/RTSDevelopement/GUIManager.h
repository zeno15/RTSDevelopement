#ifndef INCLUDED_GUIMANAGER_H
#define INCLUDED_GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "GUIFrame.h"

class GUIManager : public sf::Drawable
{
public:
	GUIManager(void);
	~GUIManager(void);

	void addFrame(GUIFrame *_frame);

	void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	std::vector<GUIFrame *>										m_Frames;
};

#endif //~ INCLUDED_GUIMANAGER_H