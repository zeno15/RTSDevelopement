#ifndef INCLUDED_GUIDROPDOWNMENU_H
#define INCLUDED_GUIDROPDOWNMENU_H

#include "GUIObject.h"

#include <vector>
#include <string>

class GUIDropDownMenu : public GUIObject
{
public:
	GUIDropDownMenu(std::string _text, sf::Vector2f _position, float _length, bool _isRoot = false);
	~GUIDropDownMenu(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addSubMenu(GUIDropDownMenu *_subMenu);

	void rootFinaliseMenuPositions(void);

private:
	void extend(void);

	enum menuState {NORMAL,
					HOVER,
					EXTEND};

	void setState(menuState _state);

	void findExtensionPosition(void);


private:
	std::vector<GUIDropDownMenu *>				m_SubMenus;

	sf::VertexArray								m_MenuBackground;
	sf::Text									m_Text;

	sf::Vector2f								m_Position;
	sf::Vector2f								m_ExtendPosition;

	menuState									m_State;

	float										m_Length;

	bool										m_Extended;
	bool										m_IsRoot;
};

#endif //~ INCLUDED_GUIDROPDOWNMENU_H