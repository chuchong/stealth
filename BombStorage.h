#include "Storage.h"
#include "BombAppearMessage.h"
#pragma once

//用来存储炸弹信息，其中flyRound2中存储的是第一次出现的炸弹（可以认为行走了三分之一的路程，但是位置依然在出发点）
//flyRound3中存储了第二次出现的炸弹
//temp1,temp2是中间变量
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