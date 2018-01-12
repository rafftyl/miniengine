#pragma once
#include "Event.h"

typedef Event<int, int> BasicEvent;
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

	void sendEngineShutdownRequest(int arg1, int arg2)
	{
		engineShutdownRequestEvent.broadcast(arg1, arg2);
	}
};

