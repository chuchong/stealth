//***********************************����װ�����ԵĶ��弰ʵ��*******************************
//by wxs
//2018/5/2

#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>

#ifndef DEBUG
#define DEBUG false
//�˴�����Ϊtrue�������ģʽ������̨�����������Ϣ
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
			std::cout << "here" << std::endl;
		}
		bought = true;
    }
    if (DEBUG && bought)
	{
		std::cout << "ward num(before bought): " << sight.wardCount << std::endl 
			<< "bomb num(before bought): " << sight.bombCount << std::endl << std::endl;
	}
}
//***********************************����װ�����ԵĶ��弰ʵ�ֽ���*******************************
