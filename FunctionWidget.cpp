#include "FunctionWidget.h"

//判断是否是黑夜 110/80什么
//110是一个昼夜的长度，80是白天的长度
bool isNight(const PlayerSight & sight)
{
	if (((sight.round - 1) % 110) + 1< 81)
		return false;
	return true;
}
//判断是否只需一次击杀就可以获胜
//如果当前分数+连杀数>15,那么只需一次击杀即可获胜
bool oneStrikeToWin(const PlayerSight & sight)
{
	int personalScore = sight.scoreBoard[sight.id];
	return (sight.continuousKill + personalScore >= 15);
}
//判断对目标是否能进行吸血攻击
bool canSuckAttack(const PlayerSight & sight)
{
	for (auto unit : sight.unitInSight)
	{
		if ((unit.pos - sight.pos).length() <= SuckRange)
			return true;
	}
	return false;
}
//返回units中距离id单位最近的单位的距离,如果没有找到id单位，返回值为FINF（无限）
//如果需要知道最近单位的id，传入第三个参数
float DisOtherUnit(const std::vector<PUnitInfo> & units, int id, int * idOther)
{
	int dis = FINF;
	PUnitInfo unitid;
	for (auto unit : units)
	{
		if (unit.id == id)
			unitid = unit;
	}
	if (unitid.id == -1)
		return FINF;
	for (auto unit : units)
	{
		if (unit.id == id)
			continue;
		if ((unit.pos - unitid.pos).length() < dis)
		{
			dis = (unit.pos - unitid.pos).length();
			if (idOther != NULL)
				*idOther = unit.id;
		}
	}
	return dis;
}

