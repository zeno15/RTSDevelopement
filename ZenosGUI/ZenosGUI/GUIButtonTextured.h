#ifndef INCLUDED_GUIBUTTONTEXTURED_H
#define INCLUDED_GUIBUTTONTEXTURED_H

#include <string>

#include "GUIObject.h"

class GUIButtonTextured : public GUIObject
{
public:
	GUIButtonTextured(sf::Vector2f _position, sf::Vector2f _size, sf::Texture *_texture, sf::FloatRect _textureBounds);
	~GUIButtonTextured(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	enum colourState {NORMAL, HOVER, CLICK, NUMSTATES};

	void changeColourState(colourState _state);

	void setDefaultColours(void);
	void setHoverColours(void);
	void setPressedColours(void);

private:
	sf::VertexArray									m_Vertices;

	sf::Texture *									m_Texture;

	bool											m_Unactivate;
	
	colourState										m_CurrentState;
};

#endif //~ INCLUDED_GUIBUTTONTEXTURED_H