#pragma once
#include "EngineSystem.h"

class AudioSystem : public EngineSystem
{
public:
	AudioSystem(MessageBus& msgBus);
	virtual ~AudioSystem();
};

