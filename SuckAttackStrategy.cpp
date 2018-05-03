#include"SuckAttackStrategy.h"
#include "FunctionWidget.h"
//����
void SuckAttackStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
	CHECK_DISABLED
		if (!sight.canSuckAttack)
			return;
	if (isNight(sight))
	{
		if (sight.unitInSightCount != 0)
		{
			for (auto unit : sight.unitInSight)
			{
				if ((unit.pos - sight.pos).length() <= SuckRange)
				{
					if (sight.hp < 90)
					{
						actions->emplace(SuckAttack, unit.id);
						break;
					}
					else if (memory->checkUnitForPlayer(unit.id))
					{
						actions->emplace(SuckAttack, unit.id);
					}
				}
				//�����Ż������ȹ���ֻ������һ�εĵ�λ
			}
		}
	}
	else if (canSuckAttack(sight))
	{
		std::vector<PUnitInfo> units;
		if (sight.hp > 75)
		{
			for (auto unit : sight.unitInSight)
			{
				if (memory->checkUnitForPlayer(unit.id) && (unit.pos - sight.pos).length() <= SuckRange)
					units.push_back(unit);
			}//�����в²�����ҵĵ�λװ��units
		}
		else if (sight.hp <= 35)
		{
			for (auto unit : sight.unitInSight)
			{
				if (!memory->checkUnitForPlayer(unit.id) && (unit.pos - sight.pos).length() <= SuckRange)
					units.push_back(unit);
			}//�����в²��Ǵ���ĵ�λװ��units
		}

		float dis;
		float smallest = FINF;
		int finalid = -1;
		for (auto unit : units)
		{
			dis = DisOtherUnit(sight.unitInSight, unit.id);
			if (dis > smallest)
				continue;
			smallest = dis;
			finalid = unit.id;
		}
		if (finalid != -1)
		{
			actions->emplace(SuckAttack, finalid);
		}
	}
}