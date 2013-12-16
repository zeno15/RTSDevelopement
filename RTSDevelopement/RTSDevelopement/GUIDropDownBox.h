#ifndef INCLUDED_GUIDROPDOWNBOX_H
#define INCLUDED_GUIDROPDOWNBOX_H

#include "GUIObject.h"

#include <string>

class GUIDropDownBox : public GUIObject
{
public:
	GUIDropDownBox(sf::Vector2f _position, sf::Vector2f _size);
	~GUIDropDownBox(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addOption(std::string _option);
	std::string getActiveOption(void);

private:
	void extend(void);

private:
	sf::Text							m_SelectedOption;

	sf::VertexArray						m_BackgroundQuads;

	bool								m_Extended;

	std::vector<sf::Text *>				m_ExtendedOptions;

};

#endif //~ INCLUDED_GUIDROPDOWNBOX_H