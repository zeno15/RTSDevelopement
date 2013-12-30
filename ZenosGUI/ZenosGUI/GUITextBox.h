#ifndef INCLUDED_GUITEXTBOX_H
#define INCLUDED_GUITEXTBOX_H

#include "GUIObject.h"

#include <vector>
#include <string>

///////////////////////////////////////
//
// Will only implement backspace and entering characters
//
///////////////////////////////////////

class GUITextBox : public GUIObject
{
public:
	enum TextBoxType {REGULAR, NUMERICAL};
	enum LabelPosition {ABOVE, LEFT, BELOW, RIGHT};

	GUITextBox(sf::Vector2f _position, sf::Vector2f _size, TextBoxType _type, bool _scrolls = false);
	~GUITextBox(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

	bool active(void);

	void appendTextInput(char _character);

	std::string getString(void);

	void setLabel(std::string _text, LabelPosition _position);

private:
	void updateCursorPosition(void);

private:
	bool													m_Active;
	bool													m_Scrolls;

	std::vector<char>										m_PendingChars;

	std::string												m_DisplayedString;

	sf::VertexArray											m_Box;

	sf::Text												m_Text;
	sf::Text												m_Label;

	TextBoxType												m_Type;

};

#endif //~ INCLUDED_GUITEXTBOX_H