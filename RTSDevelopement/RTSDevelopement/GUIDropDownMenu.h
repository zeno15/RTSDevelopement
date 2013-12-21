#ifndef INCLUDED_GUIDROPDOWNMENU_H
#define INCLUDED_GUIDROPDOWNMENU_H

#include "GUIObject.h"

#include <vector>
#include <string>

class GUIDropDownMenu : public GUIObject
{
public:
	GUIDropDownMenu(std::string _text, sf::Vector2f _position, float _length);
	~GUIDropDownMenu(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addSubMenu(GUIDropDownMenu *_subMenu);

	void activate(void);

private:
	enum mouseState {NORMAL,
					 HOVER};

	void setState(mouseState _state);

	void setNormalColour(void);
	void setHoverColour(void);

private:
	std::vector<GUIDropDownMenu *>				m_SubMenus;

	sf::Vector2f								m_Position;
	sf::VertexArray								m_BackgroundQuads;
	sf::VertexArray								m_SubMenuArrows;
	sf::VertexArray								m_SubMenuBackground;
	sf::Text									m_Description;

	bool										m_Activated;
	bool										m_IsChild;

	mouseState									m_State;
};

#endif //~ INCLUDED_GUIDROPDOWNMENU_H