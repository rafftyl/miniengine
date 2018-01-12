#pragma once
#include "MessageBus.h"
#include <memory>
#include <ctime>

class EngineSystem
{
private:
	clock_t prevTimestamp;
protected:
	MessageBus& msgBus;
	float deltaTime;
public:
	EngineSystem(MessageBus& msgBus);
	virtual ~EngineSystem();

	virtual void update();
};

