#include"IdentityStorage.h"
//�趨һ����ɫ�����
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
//�趨һ����ɫ�������
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

//����һ������id�����Ƿ���player
bool IdentityStorage::checkUnitForPlayer(const int unitid)const
{
	return (std::find(_identityMemory.begin(), _identityMemory.end(), unitid) != _identityMemory.end());
}
//����Ϣ������Ӧ
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
/*��ݼ���洢�����*/