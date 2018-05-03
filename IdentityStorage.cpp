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
//����һ������id�����Ƿ���player
bool IdentityStorage::checkUnitForPlayer(const int unitid)const
{
	//int len = _identityMemory.size();
	return (std::find(_identityMemory.begin(), _identityMemory.end(), unitid) != _identityMemory.end());
}
//������Ϣ����
void IdentityStorage::executeMessage(Message* msg)
{
	switch (msg->getMessageType())
	{
	case PLAYER_KILLED:
	{
		removeUnitAsPlayer(((static_cast<PlayerKilledMessage*>(msg))->getdeadPlayer()).id);
		break;
	}
	default:
	{
		break;
	}
	}
}
/*��ݼ���洢�����*/