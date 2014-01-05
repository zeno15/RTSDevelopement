#ifndef INCLUDED_NEWMAPINTERFACE_H
#define INCLUDED_NEWMAPINTERFACE_H

#include "GUIFrame.h"

class NewMapInterface : public GUIFrame, public Receiver, public Publisher
{
public:
	NewMapInterface(sf::Vector2f _screenSize);
	~NewMapInterface(void);

	virtual void update(sf::Time _delta);

	virtual void onReceiverRegistered(Receiver *_receiver);

	bool checkInputs(void);

private:
	bool										m_Checking;
	bool										m_WidthReceived;
	bool										m_HeightReceived;

	unsigned int								m_WidthTextId;
	unsigned int								m_HeightTextId;

	unsigned int								m_Width;
	unsigned int								m_Height;
	unsigned int								m_DefaultTerrain;

};

#endif //~ INCLUDED_NEWMAPINTERFACE_H