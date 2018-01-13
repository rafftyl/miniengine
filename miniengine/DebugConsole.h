#pragma once
#include "EngineSystem.h"
namespace mini
{
	class DebugConsole : public EngineSystem
	{
	public:
		DebugConsole(MessageBus& msgBus);
		~DebugConsole();
	};
}
