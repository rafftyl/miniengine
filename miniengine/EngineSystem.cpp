#include "EngineSystem.h"

EngineSystem::EngineSystem(MessageBus& msgBus) : msgBus(msgBus)
{
	prevTimestamp = clock();
}


EngineSystem::~EngineSystem()
{
}

void EngineSystem::update()
{
	clock_t currentTimestamp = clock();
	deltaTime = static_cast<float>(currentTimestamp - prevTimestamp) / CLOCKS_PER_SEC;
}
