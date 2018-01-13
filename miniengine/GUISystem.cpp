#include "GUISystem.h"

namespace mini
{
	GUISystem::GUISystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{
	}

	GUISystem::~GUISystem()
	{
	}
}