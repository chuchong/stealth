//储存场上角色是否是玩家的信息
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
