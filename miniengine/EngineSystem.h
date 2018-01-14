#pragma once
#include "MessageBus.h"

namespace mini
{
	class EngineSystem
	{
	protected:
		MessageBus& msgBus;		
	public:
		EngineSystem(MessageBus& msgBus);
		virtual ~EngineSystem();
		virtual void update();
		virtual void init();
	};
}