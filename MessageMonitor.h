/*监视更新类*/

#include "Message.h"
#include "Storage.h"
#pragma once

class MessageMonitor
{
private:
	std::vector<Storage*> _storages;
	std::vector<Message*> _messages;

public:
	MessageMonitor() = default;
	void getMessage(Message* msg);
	void update();
};