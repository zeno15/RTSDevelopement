#ifndef INCLUDED_GUIBUTTON_H
#define INCLUDED_GUIBUTTON_H

#include <string>

#include "GUIObject.h"

class GUIButton : public GUIObject
{
public:
	GUIButton(std::string _text, sf::Vector2f _position, sf::Vector2f _size = sf::Vector2f());
	~GUIButton(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	enum colourState {NORMAL, HOVER, CLICK, NUMSTATES};

	void changeColourState(colourState _state);

	void setDefaultColours(void);
	void setHoverColours(void);
	void setPressedColours(void);


private:
	sf::Text										m_Text;
	sf::VertexArray									m_Vertices;

	bool											m_DisplayText;
	bool											m_Unactivate;
	
	colourState										m_CurrentState;
};

#endif //~ INCLUDED_GUIBUTTON_H