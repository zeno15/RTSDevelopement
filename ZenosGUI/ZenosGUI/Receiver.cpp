#include "Receiver.h"

#include <iostream>

Receiver::Receiver(void)
{
}

Receiver::~Receiver(void)
{
	m_Messages.clear();
}


void Receiver::notify(MessageData _message)
{
	m_Messages.push_back(_message);
}