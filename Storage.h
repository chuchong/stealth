//抽象存储类，主要存储从战场已知的信息

#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#include "Message.h"
#include "Constant.h"

#pragma once
/*
5/4更新日志
增加了setSight函数，用来在存储类中增加视野类指针，方便存储类直接访问当前视野内战况
增加了endRound函数，回合结束（或者说在记忆更新的最后）时执行
*/
class Storage
{
public:
	Storage() = default;
	virtual ~Storage() = default;
	virtual void executeMessage(Message* msg) = 0;
	setSight(const PlayerSight * sight) { _sight = sight; }
	const PlayerSight * _sight;
	virtual void endRound() = 0;
};