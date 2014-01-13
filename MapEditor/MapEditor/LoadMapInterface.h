#ifndef INCLUDED_LOADMAPINTERFACE_H
#define INCLUDED_LOADMAPINTERFACE_H

#include "../../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"

class LoadMapInterface : public GUIFrame, public Publisher, public Receiver
{
public:
	LoadMapInterface(sf::Vector2f _screenSize);
	~LoadMapInterface(void);

	virtual void update(sf::Time _delta);

	virtual void onReceiverRegistered(Receiver *_receiver);

private:
	bool checkValidity(std::string _filename);
};

#endif //~ INCLUDED_LOADMAPINTERFACE_H