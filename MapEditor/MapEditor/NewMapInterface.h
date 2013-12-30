#ifndef INCLUDED_NEWMAPINTERFACE_H
#define INCLUDED_NEWMAPINTERFACE_H

#include "GUIFrame.h"

class NewMapInterface : public GUIFrame
{
public:
	NewMapInterface(sf::Vector2f _screenSize);
	~NewMapInterface(void);

	void checkValidInputs(void);

private:
	bool									m_OnConfirm;

	unsigned int							m_WidthIndex;
	unsigned int							m_HeightIndex;
};

#endif //~ INCLUDED_NEWMAPINTERFACE_H