#ifndef INCLUDED_CURSORMANAGER_H
#define INCLUDED_CURSORMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class CursorManager : public sf::Drawable
{
public:
	enum CursorType {DEFAULT,
					 SELECT,
					 PAINT,
					 ERASE,
					 FILL,
					 NUM_CURSORS};

	CursorManager(void);
	~CursorManager(void);

	void initialise(void);

	void changeCursor(CursorType _cursorType);

	void update(sf::Time _delta);
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	sf::Sprite												m_Cursor;
	
	std::vector<sf::IntRect>								m_TextureRects;

	bool													m_DrawCursor;

};

#endif //~ INCLUDED_CURSORMANAGER_H