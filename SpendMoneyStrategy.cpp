#include "SpendMoneyStrategy.h"
//����װ�����ԵĶ��弰ʵ��
void SpendMoneyStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
	CHECK_DISABLED

		int gold = sight.gold;
	bool bought = false;
	//����ڱ�����ִ�й�������actions������˹����������boughtΪtrue����ҪΪ������
	if (gold >= WardPrice && sight.wardCount < wardNum && sight.bombCount != 0)
	{
		actions->emplace(BuyItem, WardItem);
		if (DEBUG)
		{
			std::cout << "round: " << sight.round << " buy ward" << std::endl;
		}
		bought = true;
		gold -= WardPrice;
	}

	if (gold >= BombPrice)
	{
		actions->emplace(BuyItem, BombItem);
		if (DEBUG)
		{
			std::cout << "round: " << sight.round << " buy bomb" << std::endl;
		}
		bought = true;
	}
	if (DEBUG && bought)
	{
		std::cout << "ward num(before bought): " << sight.wardCount << std::endl
			<< "bomb num(before bought): " << sight.bombCount << std::endl << std::endl;
	}
}
