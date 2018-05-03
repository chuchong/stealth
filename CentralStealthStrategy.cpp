//***********************************行动策略的定义及实现*******************************
//by wxs
//2018/5/3

#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include "sdk/router.h"
#include <iostream>

#ifndef DEBUG
#define DEBUG false
//此处更改为true进入调试模式，控制台将输出调试信息
#endif

class CentralStealthStrategy : public Strategy
{
public:
    CentralStealthStrategy() : Strategy(), status(ssStandby), activeRound(0) { }
    virtual ~CentralStealthStrategy() = default;

    virtual void generateActions(const PlayerSight&, Actions*);
    virtual StrategyType getStrategyType() { return Defensive; }

private:
    enum StealthStatus {ssStandby, ssWalking} status;
    int activeRound;
};

void CentralStealthStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
    CHECK_DISABLED

    if (sight.velocity == Vec2())
    {
        if (status == ssWalking)    //开始等待
        {
            status = ssStandby;
			if (DEBUG)
			{
				std::cout << "round: " << sight.round << " start to wait." << std::endl << std::endl;
			}
            activeRound = sight.round + Randomizer::getInstance()->randWaitTime();
        }
        else if (status == ssStandby && sight.round >= activeRound)
        {
            status = ssWalking;
			if (DEBUG)
			{
				std::cout << "round: " << sight.round << " start to walk." << std::endl << std::endl;
			}
            activeRound = 0;
			Vec2 des = Router::getInstance()->availablePosition();
			while ((des.x < 19 || des.x > 42) || (des.y < 45 || des.y > 55))
				des = Router::getInstance()->availablePosition();
            actions->emplace(SelectDestination, sight.id, des);
        }
    }
}
//***********************************行动策略的定义及实现结束*******************************