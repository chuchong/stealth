//��������࣬����Ϊ�������ṩ����ʵ�ַ�����֮����Կ��Ǹ��ݲ�ͬ��;�ֳɲ�ͬ��
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

