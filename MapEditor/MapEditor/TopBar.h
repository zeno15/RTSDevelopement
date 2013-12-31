#ifndef INCLUDED_TOPBAR_H
#define INCLUDED_TOPBAR_H

#include <SFML/Graphics.hpp>

class TopBar : public sf::Drawable
{
public:
	TopBar(void);
	~TopBar(void);

	void initialise(sf::FloatRect _bounds);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::VertexArray													m_BackgroundQuads;
};

#endif //~ INCLUDED_TOPBAR_H