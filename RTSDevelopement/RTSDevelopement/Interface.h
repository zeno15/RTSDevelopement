#ifndef INCLUDED_INTERFACE_H
#define INCLUDED_INTERFACE_H

#include <SFML/Graphics.hpp>

#include "TempBuildBar.h"

class Interface : public sf::Drawable
{
public:
	Interface(sf::FloatRect _topBarBounds, sf::FloatRect _sideBarBounds);
	~Interface(void);
	
	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	TempBuildBar *						DEBUG_BuildBar;

	sf::VertexArray						DEBUG_InterfaceBackground;
};

#endif //~ INCLUDED_INTERFACE_H