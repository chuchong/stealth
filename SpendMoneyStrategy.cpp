#include "SpendMoneyStrategy.h"
//购买装备策略的定义及实现
void SpendMoneyStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
	CHECK_DISABLED

		int gold = sight.gold;
	bool bought = false;
	//如果在本函数执行过程中向actions中添加了购买操作，则bought为true，主要为调试用
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
