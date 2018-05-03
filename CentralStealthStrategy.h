//***********************************�ж����ԵĶ��弰ʵ��*******************************
//by wxs
//2018/5/3

#include "FunctionWidget.h"
#include "Constant.h"
#pragma once

class CentralStealthStrategy : public Strategy
{
public:
	CentralStealthStrategy() : Strategy(), status(ssStandby), activeRound(0) { }
	virtual ~CentralStealthStrategy() = default;

	virtual void generateActions(const PlayerSight&, Actions*);
	virtual StrategyType getStrategyType() { return Defensive; }

private:
	enum StealthStatus { ssStandby, ssWalking } status;
	int activeRound;
};