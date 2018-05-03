//ÆÕÍ¨¹¥»÷ÎüÑªµÄ²ßÂÔ


#include "Constant.h"
#include "PlayerKilledMessage.h"
#include "IdentityStorage.h"
#include "MessageMonitor.h"
#include "FunctionWidget.h"
#pragma once

class SuckAttackStrategy : public Strategy
{
public:
	SuckAttackStrategy(const IdentityStorage * _memory) :
		Strategy(), memory(_memory) { }
	virtual ~SuckAttackStrategy() = default;

	virtual void generateActions(const PlayerSight&, Actions*);
	virtual StrategyType getStrategyType() { return Offensive; }

private:
	const IdentityStorage * memory;
};