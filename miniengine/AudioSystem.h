#pragma once
#include "EngineSystem.h"

namespace mini
{
	class AudioSystem : public EngineSystem
	{
	public:
		AudioSystem(MessageBus& msgBus);
		virtual ~AudioSystem();
	};
}
