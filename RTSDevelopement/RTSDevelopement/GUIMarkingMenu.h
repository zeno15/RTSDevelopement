#ifndef INCLUDED_GUIMARKINGMENU_H
#define INCLUDED_GUIMARKINGMENU_H

#include "GUIObject.h"
#include "GUIMarkingMenuNode.h"

#include <vector>

class GUIMarkingMenu : public GUIObject
{
public:
	GUIMarkingMenu(void);
	~GUIMarkingMenu(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addNode(GUIMarkingMenuNode *_node);

private:
	void calculateTurningPointLine(void);

	void repositionNodes(void);

private:
	std::vector<sf::Vector2f>						m_RawPoints;

	sf::VertexArray									m_RawLine;
	sf::VertexArray									m_TurnPointLine;

	bool											m_ActiveState;
};

#endif //~ INCLUDED_GUIMARKINGMENU_H