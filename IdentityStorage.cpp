#include"IdentityStorage.h"
//设定一个角色是玩家
void IdentityStorage::setUnitAsPlayer(int newplayer)
{
	if (!checkUnitForPlayer(newplayer))
	{
		_identityMemory.push_back(newplayer);
	}
	if (DEBUG)
	{
		std::cout << "set " << newplayer << " as player." << std::endl;
	}
}
//设定一个角色不是玩家
void IdentityStorage::removeUnitAsPlayer(int delplayer)
{
	auto pos = std::find(_identityMemory.begin(), _identityMemory.end(), delplayer);
	if (checkUnitForPlayer(delplayer))
	{
		_identityMemory.erase(pos);
	}
	if (DEBUG)
	{
		std::cout << "remove " << delplayer << " as player." << std::endl;
	}
}

void IdentityStorage::endRound()
{
	lastUnitInSight = _sight->unitInSight;
}

//查找一个给定id的人是否是player
bool IdentityStorage::checkUnitForPlayer(const int unitid)const
{
	return (std::find(_identityMemory.begin(), _identityMemory.end(), unitid) != _identityMemory.end());
}
//对消息做出响应
void IdentityStorage::executeMessage(Message* msg)
{
	switch (msg->getMessageType())
	{
		case PLAYER_KILLED:
			{
				removeUnitAsPlayer(((static_cast<PlayerKilledMessage*>(msg))->getdeadPlayer()).id);
				break;
			}
		case BOMB_APPEAR:
			{
				PBombInfo bomb = static_cast<BombAppearMessage*>(msg)->getBombInfo();
				std::vector<PUnitInfo> units;
				for (auto unit : lastUnitInSight)
				{
					if ((unit.pos - bomb.pos).length() < EPS)
					{
						units.push_back(unit);
					}
				}
				if (units.size() == 1)
				{
					setUnitAsPlayer(units[0].id);
					return;
				}
				if (units.size() > 1)
				{
					for (auto unit : units)
					{
						if (unit.velocity.length() < EPS)
							continue;
						setUnitAsPlayer(unit.id);
						return;
					}
				}
				return;
			}
		default:
			break;
	}
}
/*身份记忆存储类结束*/