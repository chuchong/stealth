//���泡�Ͻ�ɫ�Ƿ�����ҵ���Ϣ
#include "Storage.h"
#include "PlayerKilledMessage.h"

#pragma once
class IdentityStorage : public Storage
{
private:
	//vector<IdUnit> _identityMemory;
	std::vector<int> _identityMemory;

public:
	IdentityStorage() = default;
	virtual ~IdentityStorage() = default;
	void setUnitAsPlayer(int newplayer);
	void removeUnitAsPlayer(int delplayer);
	bool checkUnitForPlayer(int unitid)const;
	void clear() { _identityMemory.clear(); }
	virtual void executeMessage(Message* msg);
};
