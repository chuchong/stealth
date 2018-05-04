#include "MessageMonitor.h"
//接受信息队列最末的
void MessageMonitor::getMessage(Message* msg)
{
	_messages.push_back(msg);
}

//将信息发送到最前的
void MessageMonitor::update(const PlayerSight * sight)
{
	for (auto s: _storages)
	{
		s->setSight(sight);
	}
	//更新各个记忆类的sight
	for (auto m: _messages)
	{
		for (auto s: _storages)
		{
			s->executeMessage(m);
		}
		delete m;
		m = NULL;
	}
	for (auto s: _storages)
	{
		s->endRound();
	}
	//执行回合结束操作
	_messages.clear();
}