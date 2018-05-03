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
#include "IdentityStorage.h"
#include "MessageMonitor.h"

#include "SpendMoneyStrategy.h"
#include "SuckAttackStrategy.h"
#include "CentralStealthStrategy.h"
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

	static CentralStealthStrategy* stealth = new CentralStealthStrategy;
	static SpendMoneyStrategy* item = new SpendMoneyStrategy;
	static SuckAttackStrategy* suck = new SuckAttackStrategy(identity);

	item->generateActions(sight, actions);
	suck->generateActions(sight, actions);
	stealth->generateActions(sight, actions);
}

}
