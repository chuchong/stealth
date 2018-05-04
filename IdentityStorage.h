//储存场上角色是否是玩家的信息
#include "Storage.h"
#include "PlayerKilledMessage.h"
#include "BombAppearMessage.h"

/*
5/4更新日志
增加了lastUnitInSight变量，用于存储上一回合的单位信息
增加了endRound函数
*/

#pragma once
class IdentityStorage : public Storage
{
private:
	//vector<IdUnit> _identityMemory;
	std::vector<int> _identityMemory;
	std::vector<PUnitInfo> lastUnitInSight;

public:
	IdentityStorage() = default;
	virtual ~IdentityStorage() = default;
	void setUnitAsPlayer(int newplayer);
	void removeUnitAsPlayer(int delplayer);
	bool checkUnitForPlayer(int unitid)const;
	void clear() { _identityMemory.clear(); }
	virtual void executeMessage(Message* msg);
	virtual void endRound();
};
