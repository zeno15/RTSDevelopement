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

private:
	sf::Image													m_MapImage;
	sf::Texture													m_MapTexture;
	sf::Sprite													m_MapSprite;

	unsigned int												m_MapStartY;
	unsigned int												m_MapStartX;

	bool														m_RefreshMap;
};

#endif //~ INCLUDED_MINIMAP_H