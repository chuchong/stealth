//如何花钱的策略
#include "FunctionWidget.h"
#include "Constant.h"
#pragma once
class SpendMoneyStrategy : public Strategy
{
public:
	SpendMoneyStrategy(int _wardNum = 2) :
		Strategy(), wardNum(_wardNum) { }
	virtual ~SpendMoneyStrategy() = default;

	virtual void generateActions(const PlayerSight&, Actions*) override;
	virtual StrategyType getStrategyType() { return Neutral; }

private:
	int wardNum;
};