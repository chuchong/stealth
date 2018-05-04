/*���Ӹ�����*/
/*5/4������־
������addStorage������������Ӽ�����
update��������sight�����������������
*/

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
	void addStorage(Storage* storage) { _storages.push_back(storage); }
	void update(const PlayerSight * sight);
};