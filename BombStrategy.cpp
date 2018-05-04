#include "BombStrategy.h"

void BombStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
	CHECK_DISABLED
	if (sight.round % 110 == 80)
	{
		bool flag;
		for (auto unit : sight.unitInSight)
		{
			if (_memory->checkUnitForPlayer(unit.id))
			{
				aimForNight = unit.pos;
				flag = true;
			}
			if (flag)
				break;
		}
	}//太阳落山前的最后一刻，记住一个玩家的位置
	if (!sight.canUseBomb || sight.bombCount == 0)
	{
		prevHP = sight.hp;
		return;
	}
	if (isNight(sight))
	{
		if (sight.round % 110 - 81 < 2)
		{
			if ((aimForNight - Vec2()).length() > EPS)
			{
				actions->emplace(UseItem, BombItem, aimForNight);
				aimForNight = Vec2();
			}
		}
		if (prevHP - sight.hp >= 35)
		{
			actions->emplace(UseItem, BombItem, sight.pos);
			if (DEBUG)
			{
				std::cout << "Round: " << sight.round << " Attacked, use bomb" << std::endl;
			}
		}
	}
	else if (_bomb->getPeaceTime() > waitTime && _bomb->getPeaceTime() < waitTime + 5)
	{
		bool flag = false;
		for (auto unit : sight.unitInSight)
		{
			if (_memory->checkUnitForPlayer(unit.id))
			{
				if (sight.wardCount != 0)
				{
					actions->emplace(UseItem, WardItem, sight.pos);
				}
				actions->emplace(UseItem, BombItem, unit.pos);
				flag = true;
			}
			if (flag)
				break;
		}
	}
	prevHP = sight.hp;
	return;
}