#ifndef INCLUDED_GUISLIDER_H
#define INCLUDED_GUISLIDER_H

#include "GUIObject.h"

class GUISlider : public GUIObject
{
public:
	GUISlider(bool _horizontal, sf::Vector2f _position, float _size, float *_value, unsigned int _gradiated = 0);
	~GUISlider(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void setSlidePosition(sf::Vector2f _position);

	enum slideColourState {NORMAL,
						   HOVERED,
					       CLICKED
					      };

	void setSlideColour(slideColourState _state);

	void setNormalColour(void);
	void setHoverColour(void);
	void setClickedColour(void);

private:
	float *											m_Value;

	sf::VertexArray									m_Lines;
	sf::VertexArray									m_Slide;

	slideColourState								m_State;

	bool											m_Gradiated;
	bool											m_Horizontal;

	sf::Vector2f									m_Position;
	float											m_Size;
	float											m_Offset;
};

#endif //~ INCLUDED_GUISLIDER_H