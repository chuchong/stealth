//抽象存储类，主要存储从战场已知的信息

#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#include "Message.h"
#include "Constant.h"

#pragma once
class Storage
{
public:
	Storage() = default;
	virtual ~Storage() = default;
	virtual void executeMessage(Message* msg) = 0;
};