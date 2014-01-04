#ifndef INCLUDED_RECEIVER_H
#define INCLUDED_RECEIVER_H

#include <vector>

#include "MessageData.h"

class Receiver
{
public:
	Receiver(void);
	~Receiver(void);

	void notify(MessageData _message);

protected:
	std::vector<MessageData>						m_Messages;

};

#endif //~ INCLUDED_RECEIVER_H