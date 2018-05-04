//����洢�࣬��Ҫ�洢��ս����֪����Ϣ

#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#include "Message.h"
#include "Constant.h"

#pragma once
/*
5/4������־
������setSight�����������ڴ洢����������Ұ��ָ�룬����洢��ֱ�ӷ��ʵ�ǰ��Ұ��ս��
������endRound�������غϽ���������˵�ڼ�����µ����ʱִ��
*/
class Storage
{
public:
	Storage() = default;
	virtual ~Storage() = default;
	virtual void executeMessage(Message* msg) = 0;
	setSight(const PlayerSight * sight) { _sight = sight; }
	const PlayerSight * _sight;
	virtual void endRound() = 0;
};