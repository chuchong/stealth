#include <vector>
#include <algorithm>
#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#include "Constant.h"
#include "FunctionWidget.h"
#include "PlayerKilledMessage.h"
#include "BombAppearMessage.h"
#include "IdentityStorage.h"
#include "BombStorage.h"
#include "MessageMonitor.h"

#include "SpendMoneyStrategy.h"
#include "SuckAttackStrategy.h"
#include "CentralStealthStrategy.h"
#include "BombStrategy.h"
extern "C"
{

//Standard AI interface (called once per round in 'invokeAI')
AI_API void playerAI(const PlayerSight sight, Actions* actions)
{
	static bool initialized = false;
	static IdentityStorage * identity = new IdentityStorage;
	static BombStorage * bombappear = new BombStorage;
	static MessageMonitor monitor;
	if (!initialized)
	{
		monitor.addStorage(identity);
		monitor.addStorage(bombappear);
		initialized = true;
	}
	for (auto bomb : sight.bombInSight)
	{
		monitor.getMessage(new BombAppearMessage(bomb));
	}
	monitor.update(&sight);

    static CentralStealthStrategy stealth;
    static SpendMoneyStrategy item;
	static SuckAttackStrategy suck(identity);
	static BombStrategy bombstrategy(identity, bombappear, 4);

	item.generateActions(sight, actions);
	suck.generateActions(sight, actions);
	bombstrategy.generateActions(sight, actions);
	stealth.generateActions(sight, actions);
}

}
