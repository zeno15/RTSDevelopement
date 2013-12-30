#ifndef INCLUDED_GUIOBJECT_H
#define INCLUDED_GUIOBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>



class GUIObject : public sf::Drawable
{
public:
	GUIObject(void);
	~GUIObject(void);

	virtual void update(sf::Time _delta) = 0;
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const = 0;

	bool toDisplay(void);

protected:
	bool								m_Display;
	bool								m_Update;
};

#endif //~ INCLUDED_GUIOBJECT_H