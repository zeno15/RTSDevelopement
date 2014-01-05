#include "Publisher.h"

#include "Receiver.h"

Publisher::Publisher(void)
{
}

Publisher::~Publisher(void)
{
	m_Receivers.clear();
}


unsigned int Publisher::registerReceiver(Receiver *_receiver)
{
	m_Receivers.push_back(_receiver);

	onReceiverRegistered(_receiver);

	return (unsigned int)(this);
}
unsigned int Publisher::unregisterReceiver(Receiver *_receiver)
{
	for (unsigned int i = 0; i < m_Receivers.size(); i += 1)
	{
		if (m_Receivers.at(i) == _receiver)
		{
			m_Receivers.erase(m_Receivers.begin() + i);

			break;
		}
	}

	return (unsigned int)(this);
}

void Publisher::onReceiverRegistered(Receiver *_receiver)
{
}

void Publisher::notifyReceivers(MessageData::MessageType _messageType, float _floatData/* = 0.0f*/, std::string _stringData/* = std::string()*/)
{
	MessageData message = MessageData();
	message.s_Id = (unsigned int)(this);
	message.s_MessageType = _messageType;
	message.s_FloatData = _floatData;
	message.s_StringData = _stringData;

	for (Receiver *receiver : m_Receivers)
	{
		receiver->notify(message);
	}
}