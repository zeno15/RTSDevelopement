#ifndef INCLUDED_GUIDROPDOWNMENU_H
#define INCLUDED_GUIDROPDOWNMENU_H

#include "GUIObject.h"

#include <vector>
#include <string>

class GUIDropDownMenu : public GUIObject
{
public:
	GUIDropDownMenu(sf::Vector2f _position, float _length, std::string _menuName, std::vector<std::vector<std::string>> _menuNames);
	~GUIDropDownMenu(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void setMenuDraws(unsigned int _menu);

private:
	sf::VertexArray										m_BackgroundQuads;

	std::vector<std::vector<std::string>>				m_MenuNames;
	std::vector<bool>									m_MenuDraws;
	bool												m_Extended;
	bool												m_DoubleExtended;
	unsigned int										m_MenuExtended;

	std::vector<sf::Text>								m_Texts;

};

#endif //~ INCLUDED_GUIDROPDOWNMENU_H