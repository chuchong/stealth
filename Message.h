/*�Զ���������ݽṹ*/
//by wyb
//5/3
/*��Ϣ��*/
#include <vector>
#include <algorithm>
#include "sdk/router.h"
#include "sdk/sdk.h"
#include "sdk/strategy/strategy.h"
#include "sdk/randomizer.h"
#include <iostream>
#include "sdk/literals.h"

#include "Constant.h"

#pragma once
class Message
{
private:
	MessageType _messagetype;
public:
	Message() = default;
	Message(MessageType msgtp) : _messagetype(msgtp) {}
	//������Ϣ����
	MessageType getMessageType() {
		return _messagetype;
		}

	virtual ~Message() = default;
	//virtual void sendMessage() = 0;
};