#ifndef INCLUDED_PUBLISHER_H
#define INCLUDED_PUBLISHER_H

#include <vector>
#include <string>

#include "MessageData.h"

class Receiver;

class Publisher
{
public:
	Publisher(void);
	~Publisher(void);

	unsigned int registerReceiver(Receiver *_receiver);
	unsigned int unregisterReceiver(Receiver *_receiver);

	void notifyReceivers(MessageData::MessageType _messageType, float _floatData = 0.0f, std::string _stringData = std::string());

protected:
	std::vector<Receiver *>								m_Receivers;

};

#endif //~ INCLUDED_PUBLISHER_H