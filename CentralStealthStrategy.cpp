#include"CentralStealthStrategy.h"
//行动策略的实现
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
				//std::cout << "round: " << sight.round << " start to wait." << std::endl << std::endl;
			}
			activeRound = sight.round + Randomizer::getInstance()->randWaitTime();
		}
		else if (status == ssStandby && sight.round >= activeRound)
		{
			status = ssWalking;
			if (DEBUG)
			{
				//std::cout << "round: " << sight.round << " start to walk." << std::endl << std::endl;
			}
			activeRound = 0;
			Vec2 des = Router::getInstance()->availablePosition();
			while ((des.x < 19 || des.x > 28) || (des.y < 45 || des.y > 55))
				des = Router::getInstance()->availablePosition();
			actions->emplace(SelectDestination, sight.id, des);
		}
	}
}
