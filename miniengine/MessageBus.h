#pragma once
#include "Event.h"

typedef Event<> BasicEvent;
class MessageBus
{
private:
	BasicEvent engineShutdownRequestEvent;
public:
	MessageBus();
	~MessageBus();

	BasicEvent& onEngineShutdownRequest()
	{
		return engineShutdownRequestEvent;
	}

	void sendEngineShutdownRequest()
	{
		engineShutdownRequestEvent.broadcast();
	}
};

