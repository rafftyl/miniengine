#pragma once
#include "EngineSystem.h"

class GameplaySystem : public EngineSystem
{
public:
	GameplaySystem(MessageBus& msgBus);
	virtual ~GameplaySystem();
};

