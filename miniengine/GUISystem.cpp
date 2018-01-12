#include "GUISystem.h"

GUISystem::GUISystem(MessageBus& msgBus, sf::RenderWindow& window) : 
	EngineSystem(msgBus), window(window)
{
}

GUISystem::~GUISystem()
{
}
