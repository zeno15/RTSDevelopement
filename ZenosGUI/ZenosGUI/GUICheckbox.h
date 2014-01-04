#ifndef INCLUDED_GUICHECKBOX_HPP
#define INCLUDED_GUICHECKBOX_HPP

#include "GUIObject.h"

#include <string>

class GUICheckbox : public GUIObject
{
public:
	GUICheckbox(sf::Vector2f _position, std::string _string = std::string());
	~GUICheckbox(void);

	virtual void update(sf::Time _delta);

	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

private:
	void setCheckbox(void);

private:
	sf::Vector2f						m_Position;
	
	bool 								m_Selected;
	bool								m_HasDescription;
	bool								m_SelectedCheckbox;

	sf::Text							m_Description;

	sf::VertexArray						m_Vertices;

};

#endif //~ INCLUDED_GUICHECKBOX_HPP