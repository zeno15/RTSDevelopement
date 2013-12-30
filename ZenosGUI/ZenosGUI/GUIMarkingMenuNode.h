#ifndef INCLUDED_GUIMARKINGMENUNODE_H
#define INCLUDED_GUIMARKINGMENUNODE_H

class GUIMarkingMenuNode
{
public:
	GUIMarkingMenuNode(void);
	~GUIMarkingMenuNode(void);

	void updatePosition(unsigned int _position, unsigned int _totalNodes);
};

#endif //~ INCLUDED_GUIMARKINGMENU_H