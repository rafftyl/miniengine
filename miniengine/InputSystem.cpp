#include "InputSystem.h"
#include <SFML/Graphics.hpp>

InputSystem::InputSystem(MessageBus& msgBus, sf::RenderWindow& window) : 
	EngineSystem(msgBus), window(window)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			msgBus.sendEngineShutdownRequest(1, 1);
		}
	}
}
