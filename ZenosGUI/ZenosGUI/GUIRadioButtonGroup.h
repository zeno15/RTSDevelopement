#ifndef INCLUDED_RADIOBUTTONGROUP_H
#define INCLUDED_RADIOBUTTONGROUP_H

#include "GUIObject.h"
#include "GUIRadioButton.h"

#include <vector>
#include <string>

class GUIRadioButtonGroup : public GUIObject
{
public:
	GUIRadioButtonGroup(sf::Vector2f _position, float _separation, bool _horizontal = false);
	~GUIRadioButtonGroup(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	void addRadioButton(std::string _text);

	std::string  getActiveString(void);
	unsigned int getActiveIndex(void);

private:
	std::vector<GUIRadioButton *>					m_RadioButtons;

	sf::Vector2f									m_Position;

	float											m_Separation;

	bool											m_Horizontal;

	unsigned int									m_ActiveButton;


};

#endif //~ INCLUDED_RADIOBUTTONGROUP_H