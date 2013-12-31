#ifndef INCLUDED_SIDEBAR_H
#define INCLUDED_SIDEBAR_H

#include <SFML/Graphics.hpp>

class Sidebar : public sf::Drawable
{
public:
	Sidebar(void);
	~Sidebar(void);

	void initialise(sf::FloatRect _bounds);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::VertexArray													m_BackgroundQuads;

	bool															m_SelectButtonActive;
};

#endif //~ INCLUDED_SIDEBAR_H