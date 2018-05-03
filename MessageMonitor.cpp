#include "MessageMonitor.h"
//接受信息队列最末的
void MessageMonitor::getMessage(Message* msg)
{
	_messages.push_back(msg);
}

//将信息发送到最前的
void MessageMonitor::update()
{
	for (auto m : _messages)
	{
		for (auto s : _storages)
		{
			s->executeMessage(m);
		}
		delete m;
		m = NULL;
	}
	_messages.clear();
}