#include "MessageMonitor.h"
//������Ϣ������ĩ��
void MessageMonitor::getMessage(Message* msg)
{
	_messages.push_back(msg);
}

//����Ϣ���͵���ǰ��
void MessageMonitor::update(const PlayerSight * sight)
{
	for (auto s: _storages)
	{
		s->setSight(sight);
	}
	//���¸����������sight
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
	//ִ�лغϽ�������
	_messages.clear();
}