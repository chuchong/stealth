#include "Storage.h"
#include "BombAppearMessage.h"
#pragma once

//�����洢ը����Ϣ������flyRound2�д洢���ǵ�һ�γ��ֵ�ը����������Ϊ����������֮һ��·�̣�����λ����Ȼ�ڳ����㣩
//flyRound3�д洢�˵ڶ��γ��ֵ�ը��
//temp1,temp2���м����
class BombStorage: public Storage
{
private:
	int lastRound;
	std::vector<Vec2> flyRound2;
	std::vector<Vec2> flyRound3;
	std::vector<Vec2> temp1;
	std::vector<Vec2> temp2;

public:
	BombStorage() = default;
	virtual ~BombStorage() = default;
	virtual void executeMessage(Message* msg);
	int getPeaceTime()const { return _sight->round - lastRound; }
	virtual void endRound();
};