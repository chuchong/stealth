#include "Constant.h"
#include "PlayerKilledMessage.h"
#include "IdentityStorage.h"
#include "MessageMonitor.h"
#include "FunctionWidget.h"
#include "BombStorage.h"
#include "sdk/vec2.h"
#pragma once

class BombStrategy : public Strategy
{
public:
    BombStrategy(const IdentityStorage * memory, const BombStorage * bomb, int waitTime) :
		Strategy(), _memory(memory), _bomb(bomb), waitTime(waitTime) { }
    virtual ~BombStrategy() = default;

    virtual void generateActions(const PlayerSight&, Actions*);
    virtual StrategyType getStrategyType() { return Offensive; }

private:
    const IdentityStorage * _memory;
	const BombStorage * _bomb;
	int prevHP;
	const int waitTime;
	Vec2 aimForNight;
};