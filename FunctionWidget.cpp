#include "FunctionWidget.h"
//�ж��Ƿ��Ǻ�ҹ 110/80ʲô
bool isNight(const PlayerSight & sight)
{
	if (((sight.round - 1) % 110) + 1< 81)
		return false;
	return true;
}
//�ж��Ƿ�ֻ��һ�λ�ɱ??�Ϳ��Ի�ʤ
bool oneStrikeToWin(const PlayerSight & sight)
{
	int personalScore = sight.scoreBoard[sight.id];
	return (sight.continuousKill + personalScore >= 15);
}
//�ж϶�Ŀ���Ƿ��ܽ�����Ѫ����
bool canSuckAttack(const PlayerSight & sight)
{
	for (auto unit : sight.unitInSight)
	{
		if ((unit.pos - sight.pos).length() < SuckRange)
			return true;
	}
	return false;
}
//����units�о���id��λ����ĵ�λ�ľ���,���û���ҵ�id��λ������ֵΪFINF�����ޣ�
//�����Ҫ֪�������λ��id���������������
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

