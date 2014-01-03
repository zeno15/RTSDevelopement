#ifndef INCLUDED_GUITHROWAWAYNOTIFICATION_H
#define INCLUDED_GUITHROWAWAYNOTIFICATION_H

#include "GUIObject.h"
#include "GUIButton.h"

#include <string>

class GUIThrowawayNotification : public GUIObject
{
public:
	GUIThrowawayNotification(sf::Vector2f _position, sf::Vector2f _size, std::string _message);
	~GUIThrowawayNotification(void);

	virtual void update(sf::Time _delta);
	
	virtual void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;
		
private:
	sf::VertexArray											m_BackgroundQuads;

	sf::Text												m_Message;

	//GUIButton												m_OkButton;
};

#endif //~ INCLUDED_GUITHROWAWAYNOTIFICATION_H