#include <vector>
#include <algorithm>
#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#define DEBUG false

/*һЩ�����õ������Ҫ����ʵ�ֵĺ���*/

bool isNight(const PlayerSight & sight)
{
	if (((sight.round - 1) % 110) + 1< 81)
		return false;
	return true;
}

bool oneStrikeToWin(const PlayerSight & sight)
{
	int personalScore = sight.scoreBoard[sight.id];
	return (sight.continuousKill + personalScore >= 15);
}

bool canSuckAttack(const PlayerSight & sight)
{
	for (auto unit : sight.unitInSight)
	{
		if ((unit.pos - sight.pos).length() < SuckRange)
			return true;
	}
	return false;
}

float DisOtherUnit(const std::vector<PUnitInfo> & units, int id, int * idOther = NULL)
{
	int dis = FINF;
	PUnitInfo unitid;
	for (auto unit : units)
	{
		if (unit.id == id)
			unitid = unit;
	}
	if (unitid.id == -1)
		return FINF;
	for (auto unit : units)
	{
		if (unit.id == id)
			continue;
		if ((unit.pos - unitid.pos).length() < dis)
		{
			dis = (unit.pos - unitid.pos).length();
			if (idOther != NULL)
				*idOther = unit.id;
		}
	}
	return dis;
}
//����units�о���id��λ����ĵ�λ�ľ���,���û���ҵ�id��λ������ֵΪFINF�����ޣ�
//�����Ҫ֪�������λ��id���������������

/*һЩ�����õ������Ҫ����ʵ�ֵĺ�������*/

/*����װ�����ԵĶ��弰ʵ��*/
//by wxs
//2018/5/2

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
		}
		bought = true;
    }
    if (DEBUG && bought)
	{
		std::cout << "ward num(before bought): " << sight.wardCount << std::endl 
			<< "bomb num(before bought): " << sight.bombCount << std::endl << std::endl;
	}
}

/*����װ�����ԵĶ��弰ʵ�ֽ���*/

/*�ж����ԵĶ��弰ʵ��*/
//by wxs
//2018/5/3

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
        if (status == ssWalking)    //��ʼ�ȴ�
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
			while ((des.x < 19 || des.x > 28) || (des.y < 45 || des.y > 55))
				des = Router::getInstance()->availablePosition();
            actions->emplace(SelectDestination, sight.id, des);
        }
    }
}

/*�ж����ԵĶ��弰ʵ�ֽ���*/

/*�Զ���������ݽṹ*/
//by wyb
//5/3
enum MessageType
{
	PLAYER_KILLED,
	PLAYER_OCCUR
};

/*��Ϣ��*/
class Message
{
private:
	MessageType _msgtp;
public:	
	Message() = default;
	Message(MessageType msgtp): _msgtp(msgtp){}
	MessageType getMessageType();
	virtual ~Message() = default;
	//virtual void sendMessage() = 0;
};

MessageType Message::getMessageType()
{
	return _msgtp;
}

class PlayerKilledMessage: public Message
{
private:
	PUnitInfo _deadPlayer;
public:	
	PlayerKilledMessage() = default;
	PlayerKilledMessage(PUnitInfo dp): Message(PLAYER_KILLED), _deadPlayer(dp){}
	virtual ~PlayerKilledMessage() = default;
	PUnitInfo getdeadPlayer();
	//void sendMessage();
};

PUnitInfo PlayerKilledMessage::getdeadPlayer()
{
	return _deadPlayer;
}

/*��Ϣ�����*/

/*����洢��*/
class Storage
{
public:
	Storage() = default;
	virtual ~Storage() = default;
	virtual void executeMessage(Message* msg) = 0;
};

class IdentityStorage: public Storage
{
private:
	//vector<IdUnit> _identityMemory;
	std::vector<int> _identityMemory;

public:
	IdentityStorage() = default;
	virtual ~IdentityStorage() = default;
	void setUnitAsPlayer(int newplayer);
	void removeUnitAsPlayer(int delplayer);
	bool checkUnitForPlayer(int unitid)const;
	void clear() { _identityMemory.clear(); }
	virtual void executeMessage(Message* msg);
};

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


/*���Ӹ�����*/
class MessageMonitor
{
private:
	std::vector<Storage*> _storages;
	std::vector<Message*> _messages;

public:
	MessageMonitor() = default;
	void getMessage(Message* msg);
	void update();
};

void MessageMonitor::getMessage(Message* msg)
{
	_messages.push_back(msg);
}

void MessageMonitor::update()
{
	for (auto m: _messages)
	{
		for (auto s: _storages)
		{
			s->executeMessage(m);
		}
		delete m;
		m = NULL;
	}
	_messages.clear();
}
/*���Ӹ��������*/

/*�Զ������ݽṹ����*/

/*�չ����ԵĶ��弰ʵ��*/
//by wxs
//2018/5/3

class SuckAttackStrategy : public Strategy
{
public:
    SuckAttackStrategy(const IdentityStorage * _memory) :
		Strategy(), memory(_memory) { }
    virtual ~SuckAttackStrategy() = default;

    virtual void generateActions(const PlayerSight&, Actions*);
    virtual StrategyType getStrategyType() { return Offensive; }

private:
    const IdentityStorage * memory;
};

void SuckAttackStrategy::generateActions(const PlayerSight &sight, Actions *actions)
{
    CHECK_DISABLED
	if (!sight.canSuckAttack)
		return;
	if (isNight(sight))
	{
		if (sight.unitInSightCount != 0)
		{
			for (auto unit : sight.unitInSight)
			{
				if ((unit.pos - sight.pos).length() <= SuckRange)
				{
					if (sight.hp < 90)
					{
						actions->emplace(SuckAttack, unit.id);
						break;
					}
					else if (memory->checkUnitForPlayer(unit.id))
					{
						actions->emplace(SuckAttack, unit.id);
					}
				}
				//�����Ż������ȹ���ֻ������һ�εĵ�λ
			}
		}
	}
	else if (canSuckAttack(sight))
	{
		std::vector<PUnitInfo> units;
		if (sight.hp > 75)
		{
			for (auto unit : sight.unitInSight)
			{
				if (memory->checkUnitForPlayer(unit.id) && (unit.pos - sight.pos).length() <= SuckRange)
					units.push_back(unit);
			}//�����в²�����ҵĵ�λװ��units
		}
		else if (sight.hp <= 35)
		{
			for (auto unit : sight.unitInSight)
			{
				if (!memory->checkUnitForPlayer(unit.id) && (unit.pos - sight.pos).length() <= SuckRange)
					units.push_back(unit);
			}//�����в²��Ǵ���ĵ�λװ��units
		}
		
		float dis;
		float smallest = FINF;
		int finalid = -1;
		for (auto unit : units)
		{
			dis = DisOtherUnit(sight.unitInSight, unit.id);
			if (dis > smallest)
				continue;
			smallest = dis;
			finalid = unit.id;
		}
		if (finalid != -1)
		{
			actions->emplace(SuckAttack, finalid);
		}
	}
}

/*�չ����ԵĶ��弰ʵ��*/
extern "C"
{

//Standard AI interface (called once per round in 'invokeAI')
AI_API void playerAI(const PlayerSight sight, Actions* actions)
{
	static IdentityStorage * identity = NULL;
	while (identity == NULL)
	{
		identity = new IdentityStorage;
	}
	
    static CentralStealthStrategy stealth;
    static WasteMoneyStrategy item;
	static SuckAttackStrategy suck(identity);

	item.generateActions(sight, actions);
	suck.generateActions(sight, actions);
	stealth.generateActions(sight, actions);
}

}
