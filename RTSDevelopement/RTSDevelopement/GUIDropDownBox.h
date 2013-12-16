#ifndef INCLUDED_GUIDROPDOWNBOX_H
#define INCLUDED_GUIDROPDOWNBOX_H

#include "GUIObject.h"

class GUIDropDownBox : GUIObject
{
public:
	GUIDropDownBox(void);
	~GUIDropDownBox(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;
};

#endif //~ INCLUDED_GUIDROPDOWNBOX_H