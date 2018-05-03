#include "MessageMonitor.h"
//������Ϣ������ĩ��
void MessageMonitor::getMessage(Message* msg)
{
	_messages.push_back(msg);
}

//����Ϣ���͵���ǰ��
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