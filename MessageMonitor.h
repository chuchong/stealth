/*监视更新类*/
/*5/4更新日志
增加了addStorage函数，用来添加记忆类
update函数增加sight参数，供记忆类更新
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