//函数组件类，负责为策略类提供具体实现方法，之后可以考虑根据不同用途分成不同类
#include <vector>
#include <algorithm>
#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>

#include "sdk/literals.h"

#include "Constant.h"
#pragma once
	bool isNight(const PlayerSight & sight);
	bool oneStrikeToWin(const PlayerSight & sight);
	bool canSuckAttack(const PlayerSight & sight);

	float DisOtherUnit(const std::vector<PUnitInfo> & units, int id, int * idOther = NULL);

