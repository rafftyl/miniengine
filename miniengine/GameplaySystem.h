#pragma once
#include "EngineSystem.h"

namespace mini
{
	class GameplaySystem : public EngineSystem
	{
	public:
		GameplaySystem(MessageBus& msgBus);
		virtual ~GameplaySystem();
	};
}
