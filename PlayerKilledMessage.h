#include "Message.h"
#pragma once

class PlayerKilledMessage : public Message
{
private:
	PUnitInfo _deadPlayer;
public:
	PlayerKilledMessage() = default;
	PlayerKilledMessage(PUnitInfo dp) : Message(PLAYER_KILLED), _deadPlayer(dp) {}
	virtual ~PlayerKilledMessage() = default;
	PUnitInfo getdeadPlayer();
	//void sendMessage();
};
