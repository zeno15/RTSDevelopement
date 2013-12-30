#ifndef INCLUDED_GUIRADIOBUTTON_H
#define INCLUDED_GUIRADIOBUTTON_H

#include "GUIObject.h"

class GUIRadioButton : public GUIObject
{
public:
	GUIRadioButton(sf::Vector2f _position, std::string _text, bool _active = false);
	~GUIRadioButton(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	std::string getStringRepresentation(void);

	bool isActive(void);
	void reset(void);

private:
	sf::VertexArray								m_Outline;
	sf::VertexArray								m_Background;
	sf::VertexArray								m_Selection;

	sf::Vector2f								m_Position;

	sf::Text									m_Description;

	bool										m_Selected;
	bool										m_SelectedRadioButton;

};

#endif //~ INCLUDED_GUIRADIOBUTTON_H