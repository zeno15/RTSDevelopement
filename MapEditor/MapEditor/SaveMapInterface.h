#ifndef INCLUDED_SAVEMAPINTERFACE_H
#define INCLUDED_SAVEMAPINTERFACE_H

#include "../../../ZenosGUI/ZenosGUI/ZenosGUIGlobalInclude.h"

class SaveMapInterface : public GUIFrame, public Publisher, public Receiver
{
public:
	SaveMapInterface(sf::Vector2f _screenSize);
	~SaveMapInterface(void);

	virtual void update(sf::Time _delta);

	virtual void onReceiverRegistered(Receiver *_receiver);

private:
	bool checkValidity(std::string _filename);

};

#endif //~ INCLUDED_SAVEMAPINTERFACE_H