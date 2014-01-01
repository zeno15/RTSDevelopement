#ifndef INCLUDED_MINIMAP_H
#define INCLUDED_MINIMAP_H

#include <SFML/Graphics.hpp>

class Minimap : public sf::Drawable
{
public:
	Minimap(void);
	~Minimap(void);

	void initialise(sf::FloatRect _bounds, sf::Vector2u _mapSize);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void updateColour(unsigned int _x, unsigned int _y, sf::Color _colour);
	sf::Color getColour(unsigned int _x, unsigned int _y);

private:
	void updateViewPortOutlinePosition(void);

private:
	sf::Image													m_MapImage;
	sf::Texture													m_MapTexture;
	sf::Sprite													m_MapSprite;

	sf::RectangleShape											m_ViewportOutline;

	unsigned int												m_MapStartY;
	unsigned int												m_MapStartX;

	bool														m_RefreshMap;
};

#endif //~ INCLUDED_MINIMAP_H