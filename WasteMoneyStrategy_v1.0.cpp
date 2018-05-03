//***********************************购买装备策略的定义及实现*******************************
//by wxs
//2018/5/2

#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>

#ifndef DEBUG
#define DEBUG false
//此处更改为true进入调试模式，控制台将输出调试信息
#endif

class WasteMoneyStrategy : public Strategy
{
public:
    WasteMoneyStrategy(int _wardNum = 2) : 
		Strategy(), wardNum(_wardNum) { }
    virtual ~WasteMoneyStrategy() = default;

    virtual void generateActions(const PlayerSight&, Actions*);
    virtual StrategyType getStrategyType() { return Neutral; }

private:
	int wardNum;
};

void WasteMoneyStrategy::generateActions(const PlayerSight &sight, Actions *actions)
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
//***********************************购买装备策略的定义及实现结束*******************************
