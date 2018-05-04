#include "BombStorage.h"

void BombStorage::executeMessage(Message* msg)
{
	switch (msg->getMessageType())
	{
		case BOMB_APPEAR:
		{
			PBombInfo Bomb = static_cast<BombAppearMessage*>(msg)->getBombInfo();
			for (auto iter : flyRound3)
			{
				if ((iter - Bomb.pos).len2() < EPS)
					return;
			}
			for (auto iter : flyRound2)
			{
				if ((iter - Bomb.pos).len2() < EPS)
				{
					temp2.push_back(Bomb.pos + Bomb.velocity);
					return;
				}
			}
			temp1.push_back(Bomb.pos + Bomb.velocity);
			lastRound = _sight->round;
			if (DEBUG)
			{
				std::cout << "round: " << _sight->round << "bomb first appear at: " << Bomb.pos << std::endl;
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void BombStorage::endRound()
{
	flyRound3 = temp2;
	flyRound2 = temp1;
	temp1.clear();
	temp2.clear();
}