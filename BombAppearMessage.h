#include "Message.h"
#pragma once

class BombAppearMessage: public Message
{
private:
	PBombInfo _bomb;
public:	
	BombAppearMessage() = default;
	BombAppearMessage(PBombInfo dp): Message(BOMB_APPEAR), _bomb(dp){}
	virtual ~BombAppearMessage() = default;
	PBombInfo getBombInfo() { return _bomb; }
};